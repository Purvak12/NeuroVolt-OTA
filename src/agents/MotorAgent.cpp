#include "../../include/agents/MotorAgent.hpp"

#include <iostream>

void MotorAgent::analyzeMotorTelemetry(
    int motorTemperature
)
{
    std::cout
        << "[MOTOR AGENT] Analyzing Motor Telemetry..."
        << std::endl;

    if (motorTemperature > 70)
    {
        std::cout
            << "[MOTOR ALERT] High Motor Temperature!"
            << std::endl;
    }
    else
    {
        std::cout
            << "[MOTOR STATUS] Motor Stable"
            << std::endl;
    }
}