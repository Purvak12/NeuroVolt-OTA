# NeuroVolt AI OTA System

NeuroVolt AI OTA System is an AI-driven automotive middleware simulation platform built using C++, Linux SocketCAN, FastAPI, and a real-time web dashboard.

The project simulates electric vehicle ECU telemetry, analyzes vehicle health using AI-style risk scoring, validates OTA firmware updates against live vehicle conditions, and provides a dashboard-controlled OTA deployment workflow.

---

## Project Objective

Modern electric vehicles depend heavily on software updates, connected ECUs, battery systems, motor controllers, and safety-critical telemetry.

A firmware update should not be deployed blindly if the vehicle is operating under unsafe thermal or electrical conditions.

This project solves that problem by creating a simulated EV OTA safety platform that:

- Reads live CAN telemetry
- Analyzes battery and motor health
- Calculates vehicle risk score
- Validates OTA updates using firmware package rules
- Allows or blocks OTA deployment
- Maintains OTA audit history
- Displays live telemetry on a dashboard

---

## Key Features

- Linux SocketCAN based virtual CAN communication
- Virtual BMS ECU simulation
- Virtual Motor ECU simulation
- AI thermal analysis agent
- Motor health analysis agent
- Vehicle risk scoring engine
- OTA safety validator
- Firmware package configuration system
- Dashboard-triggered OTA update workflow
- FastAPI backend APIs
- Real-time dashboard with live charts
- OTA decision history and audit trail
- Event logging system
- One-command run script

---

## Tech Stack

### Core Middleware
- C++
- Linux
- SocketCAN
- CMake
- Multithreading

### Backend
- Python
- FastAPI
- Uvicorn

### Dashboard
- HTML
- CSS
- JavaScript
- Chart.js

### AI / Analytics
- Rule-based AI agents
- Risk scoring engine
- Predictive thermal alerting
- ML anomaly detection foundation

---

## System Architecture

```text
BMS ECU Simulator
        |
Motor ECU Simulator
        |
        v
Virtual CAN Bus - vcan0
        |
        v
C++ CAN Middleware
        |
        v
AI Agents
        |
        v
Risk Scoring Engine
        |
        v
OTA Safety Validator
        |
        v
Firmware Package Rules
        |
        v
FastAPI Backend
        |
        v
Real-time Dashboard

Dashboard Start OTA Button
        |
        v
FastAPI creates OTA request
        |
        v
C++ middleware detects OTA request
        |
        v
Firmware package config is loaded
        |
        v
Live vehicle telemetry is evaluated
        |
        v
Risk score is calculated
        |
        v
OTA is allowed, delayed, blocked, or rolled back
        |
        v
Decision is logged in OTA history