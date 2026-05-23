#include "../../include/ecu/MotorECU.hpp"

#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

MotorECU::MotorECU(CANManager& manager)
    : canManager(manager)
{
    srand(time(0));

    motorRPM = 3000;
    motorTemperature = 50;
}

void MotorECU::simulateMotorData()
{
    while (true)
    {
        motorRPM =
            2000 + (rand() % 4000);

        motorTemperature =
            50 + (rand() % 30);

        std::string telemetry =
            std::to_string(motorRPM)
            + ","
            + std::to_string(motorTemperature);

        canManager.sendMessage(
            0x300,
            telemetry
        );

        std::this_thread::sleep_for(
            std::chrono::seconds(4)
        );
    }
}