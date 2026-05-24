#include "../../include/ota/OTAManager.hpp"
#include "../../include/ota/OTASafetyValidator.hpp"
#include "../../include/ota/OTAHistoryLogger.hpp"
#include "../../include/ota/FirmwarePackage.hpp"
#include "../../include/analytics/RiskScorer.hpp"

#include <iostream>

std::string OTAManager::currentFirmwareVersion =
    "1.0.0";

std::string OTAManager::lastOTAStatus =
    "Idle";

OTAManager::OTAManager()
{
}

void OTAManager::deployUpdate(
    const std::string& targetVersion
)
{
    if (currentFirmwareVersion == targetVersion)
    {
        std::cout
            << "[OTA STATUS] Firmware already up to date"
            << std::endl;

        std::cout
            << "[OTA ACTION] No deployment required"
            << std::endl;

        lastOTAStatus =
            "Already Up To Date";

        return;
    }

    std::cout
        << "[OTA] Deploying firmware update..."
        << std::endl;

    std::cout
        << "[OTA] Current Version: "
        << currentFirmwareVersion
        << std::endl;

    std::cout
        << "[OTA] Target Version: "
        << targetVersion
        << std::endl;

    currentFirmwareVersion =
        targetVersion;

    lastOTAStatus =
        "Updated Successfully";

    std::cout
        << "[OTA STATUS] Firmware updated successfully to version "
        << currentFirmwareVersion
        << std::endl;
}

void OTAManager::validateAndDeployUpdate(
    int batteryTemp,
    int motorTemp,
    int motorRPM,
    int stateOfCharge
)
{
    std::cout
        << "[OTA] Firmware package received for validation"
        << std::endl;

    FirmwarePackage firmwarePackage;

    firmwarePackage.loadFromConfig();

    RiskScorer riskScorer;

    int riskScore =
        riskScorer.calculateRiskScore(
            batteryTemp,
            motorTemp,
            motorRPM
        );

    OTASafetyValidator validator;

    OTAHistoryLogger historyLogger;

    bool isSafe =
        validator.validateUpdate(
            batteryTemp,
            motorTemp,
            motorRPM,
            stateOfCharge,
            firmwarePackage.requiredBatteryTempMax,
            firmwarePackage.requiredMotorTempMax,
            firmwarePackage.minSOC,
            firmwarePackage.maxAllowedRiskScore
        );

    if (isSafe)
    {
        std::string oldVersion =
            currentFirmwareVersion;

        deployUpdate(
            firmwarePackage.targetVersion
        );

        if (oldVersion == currentFirmwareVersion)
        {
            historyLogger.logDecision(
                "OTA_ALREADY_UP_TO_DATE",
                riskScore,
                batteryTemp,
                motorTemp,
                motorRPM,
                stateOfCharge,
                currentFirmwareVersion
            );
        }
        else
        {
            historyLogger.logDecision(
                "OTA_UPDATED_SUCCESSFULLY",
                riskScore,
                batteryTemp,
                motorTemp,
                motorRPM,
                stateOfCharge,
                currentFirmwareVersion
            );
        }
    }
    else
    {
        lastOTAStatus =
            "Blocked / Delayed";

        std::cout
            << "[OTA ACTION] Update delayed due to firmware package safety rules"
            << std::endl;

        historyLogger.logDecision(
            "OTA_BLOCKED_BY_PACKAGE_RULES",
            riskScore,
            batteryTemp,
            motorTemp,
            motorRPM,
            stateOfCharge,
            currentFirmwareVersion
        );
    }
}

void OTAManager::rollbackFirmware()
{
    std::cout
        << "[OTA ALERT] Unsafe Conditions Detected!"
        << std::endl;

    std::cout
        << "[OTA ACTION] Rolling Back Firmware..."
        << std::endl;

    currentFirmwareVersion =
        "1.0.0";

    lastOTAStatus =
        "Rollback Completed";

    std::cout
        << "[OTA STATUS] Stable Firmware Restored"
        << std::endl;
}

std::string OTAManager::getCurrentFirmwareVersion()
{
    return currentFirmwareVersion;
}

std::string OTAManager::getLastOTAStatus()
{
    return lastOTAStatus;
}