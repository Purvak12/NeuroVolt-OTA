# NeuroVolt AI OTA System Architecture

## High-Level Architecture

```text
BMS ECU Simulator
        |
        | CAN ID: 0x200
        v
Virtual CAN Bus - vcan0
        ^
        | CAN ID: 0x300
        |
Motor ECU Simulator

        |
        v

C++ SocketCAN Middleware
        |
        | Parses CAN telemetry
        v

AI Agent Layer
        |
        |-- ThermalAgent
        |-- MotorAgent
        |-- VehicleOrchestrator
        |
        v

Risk Scoring Engine
        |
        v

OTA Safety Validator
        |
        |-- Battery temperature validation
        |-- Motor temperature validation
        |-- SOC validation
        |-- Risk score validation
        |-- Firmware package rule validation
        |
        v

OTA Manager
        |
        |-- Deploy update
        |-- Block update
        |-- Delay update
        |-- Rollback firmware
        |
        v

Telemetry Logger + Event Logger + OTA History Logger
        |
        v

FastAPI Backend
        |
        |-- GET /telemetry
        |-- POST /start-ota
        |-- GET /events
        |-- GET /ota-history
        |-- GET /firmware-package
        |
        v

Real-Time Web Dashboard
