import pandas as pd

from sklearn.ensemble import IsolationForest

data = pd.read_csv(
    "../datasets/vehicle_telemetry.csv"
)

model = IsolationForest(
    contamination=0.2,
    random_state=42
)

model.fit(data)

print(
    "\n[ML ENGINE] Model Trained Successfully"
)

while True:

    battery_temp = int(
        input(
            "\nBattery Temp: "
        )
    )

    motor_temp = int(
        input(
            "Motor Temp: "
        )
    )

    motor_rpm = int(
        input(
            "Motor RPM: "
        )
    )

    sample = pd.DataFrame(
        [[
            battery_temp,
            motor_temp,
            motor_rpm
        ]],
        columns=[
            "battery_temp",
            "motor_temp",
            "motor_rpm"
        ]
    )

    prediction = model.predict(
        sample
    )

    if prediction[0] == -1:

        print(
            "\n[ML ALERT] Anomaly Detected!"
        )

    else:

        print(
            "\n[ML STATUS] Vehicle Operating Normally"
        )