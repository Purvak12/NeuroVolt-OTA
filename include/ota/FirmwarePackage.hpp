#ifndef FIRMWARE_PACKAGE_HPP
#define FIRMWARE_PACKAGE_HPP

#include <string>

class FirmwarePackage
{
public:
    std::string ecu;

    std::string currentVersion;

    std::string targetVersion;

    int requiredBatteryTempMax;

    int requiredMotorTempMax;

    int minSOC;

    int maxAllowedRiskScore;

    FirmwarePackage();

    bool loadFromConfig();
};

#endif