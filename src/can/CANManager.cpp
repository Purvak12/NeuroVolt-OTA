#include "../../include/can/CANManager.hpp"

#include "../../include/agents/ThermalAgent.hpp"
#include "../../include/agents/MotorAgent.hpp"
#include "../../include/agents/VehicleOrchestrator.hpp"

#include <iostream>
#include <cstring>

#include <unistd.h>

#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <net/if.h>

#include <sys/ioctl.h>

CANManager::CANManager()
{
    socketFD =
        socket(
            PF_CAN,
            SOCK_RAW,
            CAN_RAW
        );

    if (socketFD < 0)
    {
        std::cout
            << "Failed to create CAN socket"
            << std::endl;

        return;
    }

    struct ifreq interfaceRequest;

    std::strcpy(
        interfaceRequest.ifr_name,
        "vcan0"
    );

    if (
        ioctl(
            socketFD,
            SIOCGIFINDEX,
            &interfaceRequest
        ) < 0
    )
    {
        std::cout
            << "Failed to get interface index"
            << std::endl;

        return;
    }

    struct sockaddr_can address;

    address.can_family =
        AF_CAN;

    address.can_ifindex =
        interfaceRequest.ifr_ifindex;

    if (
        bind(
            socketFD,
            (struct sockaddr*)&address,
            sizeof(address)
        ) < 0
    )
    {
        std::cout
            << "Failed to bind CAN socket"
            << std::endl;

        return;
    }

    std::cout
        << "CAN Interface Initialized: vcan0"
        << std::endl;
}

bool CANManager::sendMessage(
    int canID,
    const std::string& message
)
{
    struct can_frame frame;

    frame.can_id =
        canID;

    frame.can_dlc =
        message.length();

    std::memcpy(
        frame.data,
        message.c_str(),
        frame.can_dlc
    );

    int bytesSent =
        write(
            socketFD,
            &frame,
            sizeof(frame)
        );

    if (bytesSent > 0)
    {
        std::cout
            << "CAN Message Sent -> ID: "
            << std::hex
            << canID
            << " Data: "
            << message
            << std::endl;

        return true;
    }
    else
    {
        std::cout
            << "Failed to send CAN message"
            << std::endl;

        return false;
    }
}

void CANManager::receiveMessages()
{
    struct can_frame frame;

    ThermalAgent thermalAgent;

    MotorAgent motorAgent;

    VehicleOrchestrator orchestrator;

    while (true)
    {
        int bytesRead =
            read(
                socketFD,
                &frame,
                sizeof(frame)
            );

        if (bytesRead > 0)
        {
            std::string receivedData = "";

            for (
                int i = 0;
                i < frame.can_dlc;
                i++
            )
            {
                receivedData +=
                    frame.data[i];
            }

            std::cout
                << "Received CAN Message -> ID: "
                << std::hex
                << frame.can_id
                << " Data: "
                << receivedData
                << std::endl;

            if (frame.can_id == 0x200)
            {
                int temperature =
                    std::stoi(
                        receivedData.substr(
                            0,
                            receivedData.find(",")
                        )
                    );

                thermalAgent.analyzeTemperature(
                    temperature
                );

                orchestrator.evaluateVehicleRisk(
                    temperature,
                    60,
                    3000
                );
            }

            else if (frame.can_id == 0x300)
            {
                int motorTemperature =
                    std::stoi(
                        receivedData.substr(
                            0,
                            receivedData.find(",")
                        )
                    );

                motorAgent.analyzeMotorTelemetry(
                    motorTemperature
                );
            }
        }
    }
}

CANManager::~CANManager()
{
    close(socketFD);
}