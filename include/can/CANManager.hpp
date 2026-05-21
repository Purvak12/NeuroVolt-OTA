#ifndef CAN_MANAGER_HPP
#define CAN_MANAGER_HPP

#include <string>

class CANManager
{
private:
    int socketFD;

public:
    CANManager();

    bool initialize(const std::string& interfaceName);

    bool sendMessage(
        int canId,
        const std::string& data
    );

    void receiveMessages();

    ~CANManager();
};

#endif