cmake_minimum_required(VERSION 3.10)

project(NeuroVoltOTA)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    NeuroVoltOTA

    src/main.cpp
    src/can/CANManager.cpp
    src/ecu/BMS_ECU.cpp
    src/agents/ThermalAgent.cpp
)