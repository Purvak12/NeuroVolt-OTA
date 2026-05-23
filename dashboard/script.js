async function loadTelemetry()
{
    try
    {
        const response =
            await fetch(
                "../telemetry.json?t=" + new Date().getTime()
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
            "vehicleStatus"
        ).innerText =
            data.vehicleStatus;
    }
    catch(error)
    {
        console.log(error);
    }
}

setInterval(
    loadTelemetry,
    2000
);

loadTelemetry();