#ifndef TELEMETRY_LOGGER_HPP
#define TELEMETRY_LOGGER_HPP

#include <string>

class TelemetryLogger
{
public:
    void logTelemetry(
        int batteryTemp,
        int motorTemp,
        int motorRPM
    );
};

#endif