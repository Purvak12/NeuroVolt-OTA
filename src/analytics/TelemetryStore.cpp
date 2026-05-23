#include "../../include/analytics/TelemetryStore.hpp"

void TelemetryStore::storeBatteryTemperature(
    int temperature
)
{
    batteryTemperatureHistory.push_back(
        temperature
    );
}

double TelemetryStore::calculateAverageTemperature()
{
    if (batteryTemperatureHistory.empty())
    {
        return 0;
    }

    int sum = 0;

    for (int temp : batteryTemperatureHistory)
    {
        sum += temp;
    }

    return static_cast<double>(sum)
        / batteryTemperatureHistory.size();
}

int TelemetryStore::getLatestTemperature()
{
    if (batteryTemperatureHistory.empty())
    {
        return 0;
    }

    return batteryTemperatureHistory.back();
}