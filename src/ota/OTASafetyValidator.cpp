#include "../../include/ota/OTASafetyValidator.hpp"
#include "../../include/analytics/RiskScorer.hpp"

#include <iostream>

bool OTASafetyValidator::validateUpdate(
    int batteryTemp,
    int motorTemp,
    int motorRPM,
    int stateOfCharge,
    int maxBatteryTemp,
    int maxMotorTemp,
    int minSOC,
    int maxAllowedRiskScore
)
{
    std::cout
        << "[OTA VALIDATOR] Checking firmware-package safety rules..."
        << std::endl;

    RiskScorer riskScorer;

    int riskScore =
        riskScorer.calculateRiskScore(
            batteryTemp,
            motorTemp,
            motorRPM
        );

    std::cout
        << "[OTA VALIDATOR] Current Risk Score: "
        << riskScore
        << "/100"
        << std::endl;

    if (batteryTemp > maxBatteryTemp)
    {
        std::cout
            << "[OTA BLOCKED] Battery temperature exceeds firmware package limit"
            << std::endl;

        return false;
    }

    if (motorTemp > maxMotorTemp)
    {
        std::cout
            << "[OTA BLOCKED] Motor temperature exceeds firmware package limit"
            << std::endl;

        return false;
    }

    if (stateOfCharge < minSOC)
    {
        std::cout
            << "[OTA BLOCKED] Battery SOC below firmware package minimum"
            << std::endl;

        return false;
    }

    if (riskScore > maxAllowedRiskScore)
    {
        std::cout
            << "[OTA BLOCKED] Risk score exceeds firmware package limit"
            << std::endl;

        return false;
    }

    std::cout
        << "[OTA VALIDATOR] Firmware package rules satisfied"
        << std::endl;

    return true;
}