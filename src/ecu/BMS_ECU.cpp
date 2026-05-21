#include "../../include/ecu/BMS_ECU.hpp"

#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

BMS_ECU::BMS_ECU(CANManager& manager)
    : canManager(manager)
{
    srand(time(0));

    batteryTemperature = 40;
    stateOfCharge = 80;
}

void BMS_ECU::simulateBatteryData()
{
    while (true)
    {
        batteryTemperature =
            40 + (rand() % 10);

        stateOfCharge =
            60 + (rand() % 40);

        std::string telemetry =
            std::to_string(batteryTemperature)
            + ","
            + std::to_string(stateOfCharge);

        canManager.sendMessage(
            0x200,
            telemetry
        );

        std::this_thread::sleep_for(
            std::chrono::seconds(3)
        );
    }
}