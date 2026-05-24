from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

import json
import os

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/telemetry")
def getTelemetry():
    with open("../telemetry.json", "r") as file:
        data = json.load(file)

    return data


@app.post("/start-ota")
def startOTA():
    config_path = "../configs/firmware_package.json"

    target_version = "1.1.0"

    if os.path.exists(config_path):
        with open(config_path, "r") as file:
            config = json.load(file)

        target_version = config.get(
            "targetVersion",
            "1.1.0"
        )

    ota_request = {
        "requested": True,
        "targetVersion": target_version
    }

    with open("../ota_request.json", "w") as file:
        json.dump(
            ota_request,
            file,
            indent=4
        )

    return {
        "message": "OTA update request created successfully",
        "targetVersion": target_version
    }


@app.get("/events")
def getEvents():
    events_path = "../events.log"

    if not os.path.exists(events_path):
        return {
            "events": []
        }

    with open(events_path, "r") as file:
        lines = file.readlines()

    latest_events = lines[-10:]

    return {
        "events": latest_events
    }


@app.get("/ota-history")
def getOTAHistory():
    history_path = "../ota_history.log"

    if not os.path.exists(history_path):
        return {
            "history": []
        }

    with open(history_path, "r") as file:
        lines = file.readlines()

    latest_history = lines[-10:]

    return {
        "history": latest_history
    }


@app.get("/firmware-package")
def getFirmwarePackage():
    config_path = "../configs/firmware_package.json"

    if not os.path.exists(config_path):
        return {
            "error": "Firmware package config not found"
        }

    with open(config_path, "r") as file:
        config = json.load(file)

    return config