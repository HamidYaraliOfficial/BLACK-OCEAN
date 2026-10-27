#include "FactionAIController.h"

float UFactionAIController::DecideMilitaryBudgetShare(float CurrentThreatPerception) const
{
	CurrentThreatPerception = FMath::Clamp(CurrentThreatPerception, 0.0f, 1.0f);

	float RiskFactor = 0.0f;
	switch (Doctrine.RiskTolerance)
	{
		case ERiskTolerance::Cautious:   RiskFactor = 0.7f; break;
		case ERiskTolerance::Balanced:   RiskFactor = 1.0f; break;
		case ERiskTolerance::Aggressive: RiskFactor = 1.3f; break;
	}

	const float Base = Doctrine.MilitaryPriority;
	const float ThreatAdjusted = Base + (CurrentThreatPerception * 0.4f * RiskFactor);
	return FMath::Clamp(ThreatAdjusted, 0.0f, 1.0f);
}
