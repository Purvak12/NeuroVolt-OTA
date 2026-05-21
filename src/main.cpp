#include "../include/can/CANManager.hpp"
#include "../include/ecu/BMS_ECU.hpp"

#include <thread>
#include <chrono>

int main()
{
    CANManager canManager;

    if (!canManager.initialize("vcan0"))
    {
        return -1;
    }

    BMS_ECU bms(canManager);

    std::thread receiverThread(
        &CANManager::receiveMessages,
        &canManager
    );

    std::thread bmsThread(
        &BMS_ECU::simulateBatteryData,
        &bms
    );

    receiverThread.join();
    bmsThread.join();

    return 0;
}