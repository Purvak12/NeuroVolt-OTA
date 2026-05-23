#include "../include/can/CANManager.hpp"

#include "../include/ecu/BMS_ECU.hpp"
#include "../include/ecu/MotorECU.hpp"

#include "../include/analytics/TelemetryLogger.hpp"

#include <thread>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(0));

    CANManager canManager;

    BMS_ECU bms(
        canManager
    );

    MotorECU motor(
        canManager
    );

    TelemetryLogger logger;

    std::thread receiverThread(
        &CANManager::receiveMessages,
        &canManager
    );

    std::thread batteryThread(
        &BMS_ECU::simulateBatteryData,
        &bms
    );

    std::thread motorThread(
        &MotorECU::simulateMotorData,
        &motor
    );

    while (true)
    {
        int batteryTemp =
            30 + (rand() % 20);

        int motorTemp =
            50 + (rand() % 30);

        int motorRPM =
            2000 + (rand() % 5000);

        logger.logTelemetry(
            batteryTemp,
            motorTemp,
            motorRPM
        );

        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );
    }

    receiverThread.join();

    batteryThread.join();

    motorThread.join();

    return 0;
}