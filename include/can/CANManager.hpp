#ifndef CAN_MANAGER_HPP
#define CAN_MANAGER_HPP

#include <string>

class CANManager
{
private:

    int socketFD;

public:

    CANManager();

    bool sendMessage(
        int canID,
        const std::string& message
    );

    void receiveMessages();

    ~CANManager();
};

#endif