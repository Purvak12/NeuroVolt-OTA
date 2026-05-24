#include "../../include/analytics/RiskScorer.hpp"

int RiskScorer::calculateRiskScore(
    int batteryTemp,
    int motorTemp,
    int motorRPM
)
{
    int riskScore = 0;

    if (batteryTemp > 42)
    {
        riskScore += 40;
    }
    else if (batteryTemp > 38)
    {
        riskScore += 20;
    }

    if (motorTemp > 70)
    {
        riskScore += 30;
    }
    else if (motorTemp > 60)
    {
        riskScore += 15;
    }

    if (motorRPM > 5000)
    {
        riskScore += 30;
    }
    else if (motorRPM > 4000)
    {
        riskScore += 15;
    }

    if (riskScore > 100)
    {
        riskScore = 100;
    }

    return riskScore;
}