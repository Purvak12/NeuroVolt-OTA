import time

def analyze_vehicle_data(
    battery_temp,
    motor_temp,
    motor_rpm
):
    risk_score = 0

    if battery_temp > 42:
        risk_score += 40

    if motor_temp > 70:
        risk_score += 30

    if motor_rpm > 5000:
        risk_score += 30

    return risk_score

while True:

    try:

        with open(
            "../telemetry.txt",
            "r"
        ) as file:

            lines = file.readlines()

        battery_temp = 0
        motor_temp = 0
        motor_rpm = 0

        for line in lines:

            if line.startswith(
                "BatteryTemp:"
            ):
                battery_temp = int(
                    line.split(":")[1]
                )

            elif line.startswith(
                "MotorTemp:"
            ):
                motor_temp = int(
                    line.split(":")[1]
                )

            elif line.startswith(
                "MotorRPM:"
            ):
                motor_rpm = int(
                    line.split(":")[1]
                )

        risk = analyze_vehicle_data(
            battery_temp,
            motor_temp,
            motor_rpm
        )

        print(
            "\n[AI MODEL] Vehicle Risk Score:",
            risk
        )

        if risk >= 70:

            print(
                "[ML ALERT] Critical Vehicle Condition Predicted!"
            )

        elif risk >= 40:

            print(
                "[ML WARNING] Moderate Vehicle Risk"
            )

        else:

            print(
                "[ML STATUS] Vehicle Stable"
            )

    except Exception as error:

        print(
            "[AI ERROR]",
            error
        )

    time.sleep(3)