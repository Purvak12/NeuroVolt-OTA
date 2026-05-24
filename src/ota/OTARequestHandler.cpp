#include "../../include/ota/OTARequestHandler.hpp"

#include <fstream>
#include <string>
#include <cstdio>

bool OTARequestHandler::isOTARequested()
{
    std::ifstream file(
        "../ota_request.json"
    );

    if (!file.is_open())
    {
        return false;
    }

    std::string content(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    file.close();

    if (
        content.find("\"requested\"") != std::string::npos
        &&
        content.find("true") != std::string::npos
    )
    {
        return true;
    }

    return false;
}

void OTARequestHandler::clearOTARequest()
{
    std::remove(
        "../ota_request.json"
    );
}