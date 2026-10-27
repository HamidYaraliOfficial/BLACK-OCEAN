#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ContactTrack.h"
#include "FleetAIController.generated.h"

UENUM(BlueprintType)
enum class EFleetAIBehavior : uint8
{
	Patrol, Recon, Escort, Search, Retreat, Resupply, Repair, PortManagement, MissionAssignment
};

// Individual-ship / task-force level AI. Chooses a behaviour purely from the
// contact tracks and readiness values it is given - it never queries actor
// ground truth directly, keeping it symmetric with what a human player sees.
UCLASS(BlueprintType)
class UFleetAIController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="BlackOcean|AI")
	EFleetAIBehavior DecideBehavior(const TArray<FContactTrack>& VisibleTracks, float OwnReadiness,
		float OwnFuelPercent, float AggressionBias) const;
};
