#ifndef OTA_REQUEST_HANDLER_HPP
#define OTA_REQUEST_HANDLER_HPP

class OTARequestHandler
{
public:
    bool isOTARequested();

    void clearOTARequest();
};

#endif