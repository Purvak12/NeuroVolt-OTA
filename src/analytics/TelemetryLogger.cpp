#include "../../include/analytics/TelemetryLogger.hpp"

#include <fstream>

void TelemetryLogger::logTelemetry(
    int batteryTemp,
    int motorTemp,
    int motorRPM
)
{
    std::string vehicleStatus =
        "Stable";

    if (
        batteryTemp > 42
        ||
        motorTemp > 70
    )
    {
        vehicleStatus =
            "Critical";
    }

    else if (
        batteryTemp > 38
        ||
        motorTemp > 60
    )
    {
        vehicleStatus =
            "Warning";
    }

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
        << "  \"vehicleStatus\": "
        << "\""
        << vehicleStatus
        << "\"\n";

    file
        << "}";

    file.close();
}