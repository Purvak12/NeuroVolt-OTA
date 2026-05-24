#ifndef RISK_SCORER_HPP
#define RISK_SCORER_HPP

class RiskScorer
{
public:
    int calculateRiskScore(
        int batteryTemp,
        int motorTemp,
        int motorRPM
    );
};

#endif