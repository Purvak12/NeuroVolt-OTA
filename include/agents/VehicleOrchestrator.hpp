#ifndef VEHICLE_ORCHESTRATOR_HPP
#define VEHICLE_ORCHESTRATOR_HPP

class VehicleOrchestrator
{
public:
    void evaluateVehicleRisk(
        int batteryTemp,
        int motorTemp,
        int motorRPM
    );
};

#endif