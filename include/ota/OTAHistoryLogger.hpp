#ifndef OTA_HISTORY_LOGGER_HPP
#define OTA_HISTORY_LOGGER_HPP

#include <string>

class OTAHistoryLogger
{
public:
    void logDecision(
        const std::string& decision,
        int riskScore,
        int batteryTemp,
        int motorTemp,
        int motorRPM,
        int stateOfCharge,
        const std::string& firmwareVersion
    );
};

#endif