#include "../../include/agents/VehicleOrchestrator.hpp"
#include "../../include/analytics/TelemetryLogger.hpp"

#include <iostream>

void VehicleOrchestrator::evaluateVehicleRisk(
    int batteryTemp,
    int motorTemp,
    int motorRPM
)
{
    std::cout
        << "[ORCHESTRATOR] Evaluating Full Vehicle Health..."
        << std::endl;

    TelemetryLogger logger;

    logger.logTelemetry(
        batteryTemp,
        motorRPM,
        motorTemp
    );

    if (
        batteryTemp > 42 &&
        motorTemp > 70 &&
        motorRPM > 5000
    )
    {
        std::cout
            << "[CRITICAL ALERT] Vehicle Risk HIGH"
            << std::endl;

        std::cout
            << "[ORCHESTRATOR DECISION] Emergency OTA Rollback Recommended"
            << std::endl;
    }
    else
    {
        std::cout
            << "[ORCHESTRATOR STATUS] Vehicle Stable"
            << std::endl;
    }
}