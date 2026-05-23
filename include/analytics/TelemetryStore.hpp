#ifndef TELEMETRY_STORE_HPP
#define TELEMETRY_STORE_HPP

#include <vector>

class TelemetryStore
{
private:
    std::vector<int> batteryTemperatureHistory;

public:
    void storeBatteryTemperature(
        int temperature
    );

    double calculateAverageTemperature();

    int getLatestTemperature();
};

#endif