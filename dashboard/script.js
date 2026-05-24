const labels = [];

const batteryData = [];

const motorData = [];

const rpmData = [];

const riskData = [];

const chartContext =
    document
        .getElementById(
            "telemetryChart"
        )
        .getContext("2d");

const telemetryChart =
    new Chart(
        chartContext,
        {
            type: "line",

            data:
            {
                labels: labels,

                datasets:
                [
                    {
                        label:
                            "Battery Temp",

                        data:
                            batteryData,

                        borderColor:
                            "cyan",

                        backgroundColor:
                            "cyan",

                        yAxisID:
                            "temperatureAxis",

                        tension: 0.4
                    },

                    {
                        label:
                            "Motor Temp",

                        data:
                            motorData,

                        borderColor:
                            "lime",

                        backgroundColor:
                            "lime",

                        yAxisID:
                            "temperatureAxis",

                        tension: 0.4
                    },

                    {
                        label:
                            "Risk Score",

                        data:
                            riskData,

                        borderColor:
                            "red",

                        backgroundColor:
                            "red",

                        yAxisID:
                            "riskAxis",

                        tension: 0.4
                    },

                    {
                        label:
                            "Motor RPM",

                        data:
                            rpmData,

                        borderColor:
                            "orange",

                        backgroundColor:
                            "orange",

                        yAxisID:
                            "rpmAxis",

                        tension: 0.4
                    }
                ]
            },

            options:
            {
                responsive: true,

                interaction:
                {
                    mode: "index",

                    intersect: false
                },

                scales:
                {
                    temperatureAxis:
                    {
                        type: "linear",

                        position: "left",

                        min: 0,

                        max: 100,

                        ticks:
                        {
                            color: "white"
                        },

                        grid:
                        {
                            color:
                                "rgba(255,255,255,0.1)"
                        }
                    },

                    riskAxis:
                    {
                        type: "linear",

                        position: "left",

                        min: 0,

                        max: 100,

                        ticks:
                        {
                            color: "red"
                        },

                        grid:
                        {
                            drawOnChartArea: false
                        }
                    },

                    rpmAxis:
                    {
                        type: "linear",

                        position: "right",

                        min: 0,

                        max: 8000,

                        ticks:
                        {
                            color: "orange"
                        },

                        grid:
                        {
                            drawOnChartArea: false
                        }
                    },

                    x:
                    {
                        ticks:
                        {
                            color: "white"
                        },

                        grid:
                        {
                            color:
                                "rgba(255,255,255,0.1)"
                        }
                    }
                },

                plugins:
                {
                    legend:
                    {
                        labels:
                        {
                            color: "white"
                        }
                    }
                }
            }
        }
    );

async function loadTelemetry()
{
    try
    {
        const response =
            await fetch(
                "http://127.0.0.1:8000/telemetry"
            );

        const data =
            await response.json();

        document.getElementById(
            "batteryTemp"
        ).innerText =
            data.batteryTemp + " °C";

        document.getElementById(
            "motorTemp"
        ).innerText =
            data.motorTemp + " °C";

        document.getElementById(
            "motorRPM"
        ).innerText =
            data.motorRPM;

        document.getElementById(
            "riskScore"
        ).innerText =
            data.riskScore + " / 100";

        document.getElementById(
            "vehicleStatus"
        ).innerText =
            data.vehicleStatus;

        document.getElementById(
            "otaStatus"
        ).innerText =
            data.otaStatus;

        document.getElementById(
            "firmwareVersion"
        ).innerText =
            data.firmwareVersion;

        const currentTime =
            new Date().toLocaleTimeString();

        labels.push(
            currentTime
        );

        batteryData.push(
            data.batteryTemp
        );

        motorData.push(
            data.motorTemp
        );

        rpmData.push(
            data.motorRPM
        );

        riskData.push(
            data.riskScore
        );

        if (labels.length > 10)
        {
            labels.shift();

            batteryData.shift();

            motorData.shift();

            rpmData.shift();

            riskData.shift();
        }

        telemetryChart.update();
    }
    catch(error)
    {
        console.log(
            "Telemetry API Error:",
            error
        );
    }
}

async function loadFirmwarePackage()
{
    try
    {
        const response =
            await fetch(
                "http://127.0.0.1:8000/firmware-package"
            );

        const data =
            await response.json();

        const container =
            document.getElementById(
                "firmwarePackageDetails"
            );

        if (data.error)
        {
            container.innerHTML =
                data.error;

            return;
        }

        container.innerHTML =
            `
            <div class="event-item">ECU: ${data.ecu}</div>
            <div class="event-item">Current Version: ${data.currentVersion}</div>
            <div class="event-item">Target Version: ${data.targetVersion}</div>
            <div class="event-item">Max Battery Temp: ${data.requiredBatteryTempMax} °C</div>
            <div class="event-item">Max Motor Temp: ${data.requiredMotorTempMax} °C</div>
            <div class="event-item">Min SOC: ${data.minSOC}%</div>
            <div class="event-item">Max Risk Score: ${data.maxAllowedRiskScore}</div>
            `;
    }
    catch(error)
    {
        console.log(
            "Firmware Package API Error:",
            error
        );
    }
}

async function loadEvents()
{
    try
    {
        const response =
            await fetch(
                "http://127.0.0.1:8000/events"
            );

        const data =
            await response.json();

        const eventsList =
            document.getElementById(
                "eventsList"
            );

        eventsList.innerHTML =
            "";

        if (
            !data.events
            ||
            data.events.length === 0
        )
        {
            eventsList.innerHTML =
                "No events generated yet";

            return;
        }

        data.events
            .slice()
            .reverse()
            .forEach(event =>
            {
                const div =
                    document.createElement(
                        "div"
                    );

                div.className =
                    "event-item";

                div.innerText =
                    event;

                eventsList.appendChild(
                    div
                );
            });
    }
    catch(error)
    {
        console.log(
            "Events API Error:",
            error
        );
    }
}

async function loadOTAHistory()
{
    try
    {
        const response =
            await fetch(
                "http://127.0.0.1:8000/ota-history"
            );

        const data =
            await response.json();

        const otaHistoryList =
            document.getElementById(
                "otaHistoryList"
            );

        otaHistoryList.innerHTML =
            "";

        if (
            !data.history
            ||
            data.history.length === 0
        )
        {
            otaHistoryList.innerHTML =
                "No OTA decisions recorded yet";

            return;
        }

        data.history
            .slice()
            .reverse()
            .forEach(history =>
            {
                const div =
                    document.createElement(
                        "div"
                    );

                div.className =
                    "event-item";

                div.innerText =
                    history;

                otaHistoryList.appendChild(
                    div
                );
            });
    }
    catch(error)
    {
        console.log(
            "OTA History API Error:",
            error
        );
    }
}

async function startOTAUpdate()
{
    try
    {
        const response =
            await fetch(
                "http://127.0.0.1:8000/start-ota",
                {
                    method: "POST"
                }
            );

        const data =
            await response.json();

        document.getElementById(
            "otaRequestStatus"
        ).innerText =
            data.message
            + " | Target Version: "
            + data.targetVersion;

        setTimeout(
            loadOTAHistory,
            4000
        );
    }
    catch(error)
    {
        document.getElementById(
            "otaRequestStatus"
        ).innerText =
            "Failed to start OTA update";

        console.log(
            "OTA API Error:",
            error
        );
    }
}

setInterval(
    loadTelemetry,
    2000
);

setInterval(
    loadEvents,
    3000
);

setInterval(
    loadOTAHistory,
    3000
);

loadTelemetry();

loadFirmwarePackage();

loadEvents();

loadOTAHistory();