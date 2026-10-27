#include "FleetAIController.h"

EFleetAIBehavior UFleetAIController::DecideBehavior(const TArray<FContactTrack>& VisibleTracks, float OwnReadiness,
	float OwnFuelPercent, float AggressionBias) const
{
	if (OwnFuelPercent < 0.15f)
	{
		return EFleetAIBehavior::Resupply;
	}
	if (OwnReadiness < 0.25f)
	{
		return EFleetAIBehavior::Repair;
	}

	int32 HostileCount = 0;
	int32 UnknownCount = 0;
	for (const FContactTrack& Track : VisibleTracks)
	{
		if (Track.Classification == EContactClassification::Hostile) ++HostileCount;
		else if (Track.Classification == EContactClassification::Unknown) ++UnknownCount;
	}

	if (HostileCount > 0)
	{
		return (OwnReadiness > 0.5f && AggressionBias > 0.4f) ? EFleetAIBehavior::Escort : EFleetAIBehavior::Retreat;
	}
	if (UnknownCount > 0)
	{
		return EFleetAIBehavior::Recon;
	}
	return EFleetAIBehavior::Patrol;
}
