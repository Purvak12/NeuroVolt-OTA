#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <string>

class EventManager
{
public:
    void publishEvent(
        const std::string& eventName,
        const std::string& severity
    );
};

#endif