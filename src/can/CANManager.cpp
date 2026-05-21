#include "../../include/can/CANManager.hpp"
#include "../../include/agents/ThermalAgent.hpp"

#include <iostream>
#include <cstring>
#include <string>

#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

CANManager::CANManager()
{
    socketFD = -1;
}

bool CANManager::initialize(
    const std::string& interfaceName
)
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    socketFD = socket(
        PF_CAN,
        SOCK_RAW,
        CAN_RAW
    );

    if (socketFD < 0)
    {
        std::cerr
            << "Failed to create CAN socket"
            << std::endl;

        return false;
    }

    int enableLoopback = 1;

    setsockopt(
        socketFD,
        SOL_CAN_RAW,
        CAN_RAW_RECV_OWN_MSGS,
        &enableLoopback,
        sizeof(enableLoopback)
    );

    strcpy(
        ifr.ifr_name,
        interfaceName.c_str()
    );

    ioctl(
        socketFD,
        SIOCGIFINDEX,
        &ifr
    );

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(
            socketFD,
            (struct sockaddr *)&addr,
            sizeof(addr)
        ) < 0)
    {
        std::cerr
            << "Failed to bind CAN socket"
            << std::endl;

        return false;
    }

    std::cout
        << "CAN Interface Initialized: "
        << interfaceName
        << std::endl;

    return true;
}

bool CANManager::sendMessage(
    int canId,
    const std::string& data
)
{
    struct can_frame frame;

    frame.can_id = canId;
    frame.can_dlc = data.size();

    memcpy(
        frame.data,
        data.c_str(),
        data.size()
    );

    int bytesSent = write(
        socketFD,
        &frame,
        sizeof(frame)
    );

    if (bytesSent != sizeof(frame))
    {
        std::cerr
            << "Failed to send CAN message"
            << std::endl;

        return false;
    }

    std::cout
        << "CAN Message Sent -> ID: "
        << std::hex
        << canId
        << " Data: "
        << data
        << std::endl;

    return true;
}

void CANManager::receiveMessages()
{
    struct can_frame frame;

    while (true)
    {
        int bytesRead = read(
            socketFD,
            &frame,
            sizeof(frame)
        );

        if (bytesRead > 0)
        {
            std::cout
                << "Received CAN Message -> ID: "
                << std::hex
                << frame.can_id
                << " Data: ";

            std::string receivedData;

            for (int i = 0; i < frame.can_dlc; i++)
            {
                receivedData += frame.data[i];
            }

            std::cout
                << receivedData
                << std::endl;

            size_t commaPos =
                receivedData.find(",");

            if (commaPos != std::string::npos)
            {
                std::string temp =
                    receivedData.substr(
                        0,
                        commaPos
                    );

                int batteryTemp =
                    std::stoi(temp);

                ThermalAgent thermalAgent;

                thermalAgent.analyzeTemperature(
                    batteryTemp
                );
            }
        }
    }
}

CANManager::~CANManager()
{
    close(socketFD);
}