#ifndef OTA_SAFETY_VALIDATOR_HPP
#define OTA_SAFETY_VALIDATOR_HPP

class OTASafetyValidator
{
public:
    bool validateUpdate(
        int batteryTemp,
        int motorTemp,
        int motorRPM,
        int stateOfCharge,
        int maxBatteryTemp,
        int maxMotorTemp,
        int minSOC,
        int maxAllowedRiskScore
    );
};

#endif