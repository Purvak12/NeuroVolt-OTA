#include "../../include/ota/OTAManager.hpp"

#include <iostream>

OTAManager::OTAManager()
{
    currentFirmwareVersion = "v1.0.0";
}

void OTAManager::deployUpdate(
    const std::string& newVersion
)
{
    std::cout
        << "[OTA] Deploying Firmware Update: "
        << newVersion
        << std::endl;

    currentFirmwareVersion = newVersion;

    std::cout
        << "[OTA] Firmware Updated Successfully"
        << std::endl;
}

void OTAManager::rollbackFirmware()
{
    std::cout
        << "[OTA ALERT] Unsafe Conditions Detected!"
        << std::endl;

    std::cout
        << "[OTA ACTION] Rolling Back Firmware..."
        << std::endl;

    currentFirmwareVersion = "v1.0.0";

    std::cout
        << "[OTA STATUS] Stable Firmware Restored"
        << std::endl;
}