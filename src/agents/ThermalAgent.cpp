#include "../../include/agents/ThermalAgent.hpp"

#include <iostream>

void ThermalAgent::analyzeTemperature(
    int temperature
)
{
    std::cout
        << "[AI AGENT] Analyzing Battery Temperature..."
        << std::endl;

    if (temperature > 42)
    {
        std::cout
            << "[THERMAL ALERT] High Battery Temperature Detected!"
            << std::endl;

        std::cout
            << "[AI DECISION] Recommend OTA Safety Rollback"
            << std::endl;
    }
    else
    {
        std::cout
            << "[AI STATUS] Battery Operating Normally"
            << std::endl;
    }
}