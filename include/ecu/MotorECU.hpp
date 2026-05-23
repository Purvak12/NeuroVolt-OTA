#ifndef MOTOR_ECU_HPP
#define MOTOR_ECU_HPP

#include "../can/CANManager.hpp"

class MotorECU
{
private:
    CANManager& canManager;

    int motorRPM;
    int motorTemperature;

public:
    MotorECU(CANManager& manager);

    void simulateMotorData();
};

#endif