#ifndef BMS_ECU_HPP
#define BMS_ECU_HPP

#include "../can/CANManager.hpp"

class BMS_ECU
{
private:
    CANManager& canManager;

    int batteryTemperature;
    int stateOfCharge;

public:
    BMS_ECU(CANManager& manager);

    void simulateBatteryData();
};

#endif