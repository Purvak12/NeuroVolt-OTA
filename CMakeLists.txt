cmake_minimum_required(VERSION 3.10)

project(NeuroVoltOTA)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    NeuroVoltOTA

    src/main.cpp

    src/can/CANManager.cpp

    src/ecu/BMS_ECU.cpp
    src/ecu/MotorECU.cpp

    src/agents/ThermalAgent.cpp
    src/agents/MotorAgent.cpp
    src/agents/VehicleOrchestrator.cpp

    src/analytics/TelemetryStore.cpp
    src/analytics/TelemetryLogger.cpp
    src/analytics/RiskScorer.cpp

    src/events/EventManager.cpp

    src/ota/OTAManager.cpp
    src/ota/OTASafetyValidator.cpp
    src/ota/OTARequestHandler.cpp
    src/ota/OTAHistoryLogger.cpp
    src/ota/FirmwarePackage.cpp
)