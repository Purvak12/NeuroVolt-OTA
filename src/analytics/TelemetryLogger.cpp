#include "../../include/analytics/TelemetryLogger.hpp"
#include "../../include/analytics/RiskScorer.hpp"
#include "../../include/ota/OTAManager.hpp"

#include <fstream>
#include <string>

void TelemetryLogger::logTelemetry(
    int batteryTemp,
    int motorTemp,
    int motorRPM
)
{
    RiskScorer riskScorer;

    int riskScore =
        riskScorer.calculateRiskScore(
            batteryTemp,
            motorTemp,
            motorRPM
        );

    std::string vehicleStatus =
        "Stable";

    if (riskScore >= 70)
    {
        vehicleStatus =
            "Critical";
    }
    else if (riskScore >= 40)
    {
        vehicleStatus =
            "Warning";
    }

    std::string otaStatus =
        OTAManager::getLastOTAStatus();

    std::string firmwareVersion =
        OTAManager::getCurrentFirmwareVersion();

    std::ofstream file(
        "../telemetry.json"
    );

    file
        << "{\n";

    file
        << "  \"batteryTemp\": "
        << batteryTemp
        << ",\n";

    file
        << "  \"motorTemp\": "
        << motorTemp
        << ",\n";

    file
        << "  \"motorRPM\": "
        << motorRPM
        << ",\n";

    file
        << "  \"riskScore\": "
        << riskScore
        << ",\n";

    file
        << "  \"vehicleStatus\": "
        << "\""
        << vehicleStatus
        << "\",\n";

    file
        << "  \"otaStatus\": "
        << "\""
        << otaStatus
        << "\",\n";

    file
        << "  \"firmwareVersion\": "
        << "\""
        << firmwareVersion
        << "\"\n";

    file
        << "}";

    file.close();
}