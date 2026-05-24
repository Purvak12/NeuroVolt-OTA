#include "../../include/ota/FirmwarePackage.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

FirmwarePackage::FirmwarePackage()
{
    ecu = "BMS";

    currentVersion = "1.0.0";

    targetVersion = "1.1.0";

    requiredBatteryTempMax = 42;

    requiredMotorTempMax = 70;

    minSOC = 40;

    maxAllowedRiskScore = 40;
}

static std::string extractStringValue(
    const std::string& content,
    const std::string& key,
    const std::string& defaultValue
)
{
    std::string searchKey =
        "\"" + key + "\"";

    size_t keyPos =
        content.find(
            searchKey
        );

    if (keyPos == std::string::npos)
    {
        return defaultValue;
    }

    size_t colonPos =
        content.find(
            ":",
            keyPos
        );

    size_t firstQuote =
        content.find(
            "\"",
            colonPos + 1
        );

    size_t secondQuote =
        content.find(
            "\"",
            firstQuote + 1
        );

    if (
        firstQuote == std::string::npos
        ||
        secondQuote == std::string::npos
    )
    {
        return defaultValue;
    }

    return content.substr(
        firstQuote + 1,
        secondQuote - firstQuote - 1
    );
}

static int extractIntValue(
    const std::string& content,
    const std::string& key,
    int defaultValue
)
{
    std::string searchKey =
        "\"" + key + "\"";

    size_t keyPos =
        content.find(
            searchKey
        );

    if (keyPos == std::string::npos)
    {
        return defaultValue;
    }

    size_t colonPos =
        content.find(
            ":",
            keyPos
        );

    size_t valueStart =
        content.find_first_of(
            "0123456789",
            colonPos + 1
        );

    size_t valueEnd =
        content.find_first_not_of(
            "0123456789",
            valueStart
        );

    if (valueStart == std::string::npos)
    {
        return defaultValue;
    }

    return std::stoi(
        content.substr(
            valueStart,
            valueEnd - valueStart
        )
    );
}

bool FirmwarePackage::loadFromConfig()
{
    std::ifstream file(
        "../configs/firmware_package.json"
    );

    if (!file.is_open())
    {
        std::cout
            << "[FIRMWARE PACKAGE] Config not found. Using default OTA package."
            << std::endl;

        return false;
    }

    std::stringstream buffer;

    buffer
        << file.rdbuf();

    std::string content =
        buffer.str();

    file.close();

    ecu =
        extractStringValue(
            content,
            "ecu",
            ecu
        );

    currentVersion =
        extractStringValue(
            content,
            "currentVersion",
            currentVersion
        );

    targetVersion =
        extractStringValue(
            content,
            "targetVersion",
            targetVersion
        );

    requiredBatteryTempMax =
        extractIntValue(
            content,
            "requiredBatteryTempMax",
            requiredBatteryTempMax
        );

    requiredMotorTempMax =
        extractIntValue(
            content,
            "requiredMotorTempMax",
            requiredMotorTempMax
        );

    minSOC =
        extractIntValue(
            content,
            "minSOC",
            minSOC
        );

    maxAllowedRiskScore =
        extractIntValue(
            content,
            "maxAllowedRiskScore",
            maxAllowedRiskScore
        );

    std::cout
        << "[FIRMWARE PACKAGE] Loaded package for ECU: "
        << ecu
        << " Target Version: "
        << targetVersion
        << std::endl;

    return true;
}