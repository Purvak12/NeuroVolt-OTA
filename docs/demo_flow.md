# NeuroVolt Demo Flow

This document explains how to demonstrate the NeuroVolt AI OTA System.

---

## Step 1: Run the complete system

```bash
./scripts/run_all.sh
This starts:

vCAN interface
C++ SocketCAN middleware
FastAPI backend
Dashboard server
Step 2: Open dashboard
http://localhost:8080/dashboard/
Step 3: Observe live telemetry

Dashboard displays:

Battery temperature
Motor temperature
Motor RPM
Risk score
Vehicle status
OTA status
Firmware version
Live chart
Vehicle events
OTA decision history
Firmware package rules
Step 4: Trigger OTA update

Click:

Start OTA Update
Step 5: OTA safety validation

The system validates:

Battery temperature
Motor temperature
Motor RPM
Battery SOC
Risk score
Firmware package rules
Step 6: Observe OTA result

If conditions are safe:

OTA_UPDATED_SUCCESSFULLY

If conditions are unsafe:

OTA_BLOCKED_BY_PACKAGE_RULES

If firmware is already updated:

OTA_ALREADY_UP_TO_DATE
Step 7: Check audit trail

Dashboard updates the OTA Decision History panel.

Step 8: Stop system
./scripts/stop_all.sh
