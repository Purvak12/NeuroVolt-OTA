#ifndef OTA_MANAGER_HPP
#define OTA_MANAGER_HPP

#include <string>

class OTAManager
{
private:
    static std::string currentFirmwareVersion;

    static std::string lastOTAStatus;

public:
    OTAManager();

    void deployUpdate(
        const std::string& targetVersion
    );

    void validateAndDeployUpdate(
        int batteryTemp,
        int motorTemp,
        int motorRPM,
        int stateOfCharge
    );

    void rollbackFirmware();

    static std::string getCurrentFirmwareVersion();

    static std::string getLastOTAStatus();
};

#endif