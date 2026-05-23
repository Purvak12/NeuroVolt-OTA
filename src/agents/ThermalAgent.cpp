#include "../../include/agents/ThermalAgent.hpp"
#include "../../include/ota/OTAManager.hpp"
#include "../../include/analytics/TelemetryStore.hpp"
#include "../../include/events/EventManager.hpp"

#include <iostream>

TelemetryStore telemetryStore;

void ThermalAgent::analyzeTemperature(
    int temperature
)
{
    telemetryStore.storeBatteryTemperature(
        temperature
    );

    double averageTemperature =
        telemetryStore.calculateAverageTemperature();

    std::cout
        << "[AI AGENT] Analyzing Battery Temperature..."
        << std::endl;

    std::cout
        << "[AI ANALYTICS] Average Battery Temperature: "
        << averageTemperature
        << std::endl;

    OTAManager otaManager;

    EventManager eventManager;

    if (temperature > 42)
    {
        std::cout
            << "[THERMAL ALERT] High Battery Temperature Detected!"
            << std::endl;

        eventManager.publishEvent(
            "THERMAL_CRITICAL",
            "HIGH"
        );

        std::cout
            << "[AI DECISION] Recommend OTA Safety Rollback"
            << std::endl;

        otaManager.rollbackFirmware();
    }
    else
    {
        std::cout
            << "[AI STATUS] Battery Operating Normally"
            << std::endl;
    }

    if (averageTemperature > 43)
    {
        std::cout
            << "[PREDICTIVE ALERT] Vehicle Battery Risk Increasing!"
            << std::endl;

        eventManager.publishEvent(
            "PREDICTIVE_BATTERY_RISK",
            "MEDIUM"
        );
    }
}