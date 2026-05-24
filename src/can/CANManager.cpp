#include "../../include/can/CANManager.hpp"

#include "../../include/agents/ThermalAgent.hpp"
#include "../../include/agents/MotorAgent.hpp"
#include "../../include/agents/VehicleOrchestrator.hpp"

#include "../../include/ota/OTAManager.hpp"
#include "../../include/ota/OTARequestHandler.hpp"

#include <iostream>
#include <cstring>
#include <string>

#include <unistd.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <net/if.h>
#include <sys/ioctl.h>

int globalBatteryTemp = 0;
int globalSOC = 80;
int globalMotorRPM = 0;
int globalMotorTemp = 0;

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

    int enableLoopback = 1;

    setsockopt(
        socketFD,
        SOL_CAN_RAW,
        CAN_RAW_RECV_OWN_MSGS,
        &enableLoopback,
        sizeof(enableLoopback)
    );

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

    std::cout
        << "Failed to send CAN message"
        << std::endl;

    return false;
}

void CANManager::receiveMessages()
{
    struct can_frame frame;

    ThermalAgent thermalAgent;
    MotorAgent motorAgent;
    VehicleOrchestrator orchestrator;
    OTAManager otaManager;
    OTARequestHandler otaRequestHandler;

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

            size_t commaPos =
                receivedData.find(",");

            if (commaPos == std::string::npos)
            {
                continue;
            }

            int value1 =
                std::stoi(
                    receivedData.substr(
                        0,
                        commaPos
                    )
                );

            int value2 =
                std::stoi(
                    receivedData.substr(
                        commaPos + 1
                    )
                );

            if (frame.can_id == 0x200)
            {
                globalBatteryTemp =
                    value1;

                globalSOC =
                    value2;

                thermalAgent.analyzeTemperature(
                    globalBatteryTemp
                );

                if (
                    otaRequestHandler.isOTARequested()
                )
                {
                    std::cout
                        << "[OTA REQUEST] Update request received from dashboard"
                        << std::endl;

                    otaManager.validateAndDeployUpdate(
                        globalBatteryTemp,
                        globalMotorTemp,
                        globalMotorRPM,
                        globalSOC
                    );

                    otaRequestHandler.clearOTARequest();
                }
            }

            else if (frame.can_id == 0x300)
            {
                globalMotorRPM =
                    value1;

                globalMotorTemp =
                    value2;

                motorAgent.analyzeMotorTelemetry(
                    globalMotorTemp
                );

                orchestrator.evaluateVehicleRisk(
                    globalBatteryTemp,
                    globalMotorTemp,
                    globalMotorRPM
                );
            }
        }
    }
}

CANManager::~CANManager()
{
    close(socketFD);
}