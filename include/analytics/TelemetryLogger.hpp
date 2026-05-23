#ifndef TELEMETRY_LOGGER_HPP
#define TELEMETRY_LOGGER_HPP

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