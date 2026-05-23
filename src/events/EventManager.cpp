#include "../../include/events/EventManager.hpp"

#include <iostream>
#include <fstream>
#include <ctime>

void EventManager::publishEvent(
    const std::string& eventName,
    const std::string& severity
)
{
    std::time_t now =
        std::time(nullptr);

    std::string timestamp =
        std::ctime(&now);

    std::ofstream file(
        "events.log",
        std::ios::app
    );

    file
        << "EVENT: "
        << eventName
        << " | Severity: "
        << severity
        << " | Time: "
        << timestamp;

    file.close();

    std::cout
        << "[EVENT MANAGER] Published Event -> "
        << eventName
        << std::endl;
}