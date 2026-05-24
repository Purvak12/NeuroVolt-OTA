#!/bin/bash

echo "Stopping NeuroVolt AI OTA System..."

pkill NeuroVoltOTA
pkill -f uvicorn
pkill -f "python3 -m http.server"

echo "All NeuroVolt services stopped."