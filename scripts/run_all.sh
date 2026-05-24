#!/bin/bash

echo "Starting NeuroVolt AI OTA System..."

PROJECT_ROOT="$HOME/Desktop/NeuroVolt local repo"

echo "Setting up vCAN interface..."

sudo modprobe vcan

if ip link show vcan0 > /dev/null 2>&1
then
    echo "vcan0 already exists"
else
    sudo ip link add dev vcan0 type vcan
fi

sudo ip link set up vcan0

echo "Building C++ middleware..."

cd "$PROJECT_ROOT/build" || exit

cmake ..
make

echo "Starting C++ middleware..."

sudo ./NeuroVoltOTA > "$PROJECT_ROOT/logs/cpp_middleware.log" 2>&1 &

CPP_PID=$!

echo "C++ middleware started with PID: $CPP_PID"

echo "Starting FastAPI backend..."

cd "$PROJECT_ROOT/backend" || exit

source ../venv/bin/activate

uvicorn main:app --reload > "$PROJECT_ROOT/logs/backend.log" 2>&1 &

BACKEND_PID=$!

echo "FastAPI backend started with PID: $BACKEND_PID"

echo "Starting Dashboard server..."

cd "$PROJECT_ROOT" || exit

python3 -m http.server 8080 > "$PROJECT_ROOT/logs/dashboard.log" 2>&1 &

DASHBOARD_PID=$!

echo "Dashboard server started with PID: $DASHBOARD_PID"

echo ""
echo "System started successfully!"
echo "Open dashboard at:"
echo "http://localhost:8080/dashboard/"
echo ""
echo "Logs:"
echo "C++ Middleware: logs/cpp_middleware.log"
echo "Backend: logs/backend.log"
echo "Dashboard: logs/dashboard.log"
echo ""
echo "To stop all services, run:"
echo "kill $CPP_PID $BACKEND_PID $DASHBOARD_PID"