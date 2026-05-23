#ifndef OTA_MANAGER_HPP
#define OTA_MANAGER_HPP

#include <string>

class OTAManager
{
private:
    std::string currentFirmwareVersion;

public:
    OTAManager();

    void deployUpdate(
        const std::string& newVersion
    );

    void rollbackFirmware();
};

#endif