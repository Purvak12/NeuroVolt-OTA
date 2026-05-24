#include "../../include/ota/OTAHistoryLogger.hpp"

#include <fstream>
#include <ctime>

void OTAHistoryLogger::logDecision(
    const std::string& decision,
    int riskScore,
    int batteryTemp,
    int motorTemp,
    int motorRPM,
    int stateOfCharge,
    const std::string& firmwareVersion
)
{
    std::time_t now =
        std::time(nullptr);

    std::string timestamp =
        std::ctime(&now);

    if (!timestamp.empty())
    {
        timestamp.pop_back();
    }

    std::ofstream file(
        "../ota_history.log",
        std::ios::app
    );

    file
        << "["
        << timestamp
        << "] "
        << decision
        << " | Risk: "
        << riskScore
        << " | BatteryTemp: "
        << batteryTemp
        << "C | MotorTemp: "
        << motorTemp
        << "C | MotorRPM: "
        << motorRPM
        << " | SOC: "
        << stateOfCharge
        << "% | Firmware: "
        << firmwareVersion
        << std::endl;

    file.close();
}