#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MissionObjective.h"
#include "DynamicObjectiveEngine.generated.h"

// Generates and updates mission objectives from current world/fleet/
// diplomacy/resource/weather state rather than a fixed script, so campaigns
// can branch. Also resolves dependency-gated objective activation.
UCLASS()
class UDynamicObjectiveEngine : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Missions")
	void RegisterBriefing(const FMissionBriefing& Briefing);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Missions")
	bool SetObjectiveState(FName MissionId, FName ObjectiveId, EObjectiveState NewState);

	// Activates any Pending objective whose dependencies are all Completed.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Missions")
	void RefreshObjectiveAvailability(FName MissionId);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Missions")
	bool IsMissionComplete(FName MissionId) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Missions")
	bool GetBriefing(FName MissionId, FMissionBriefing& OutBriefing) const;

private:
	UPROPERTY()
	TMap<FName, FMissionBriefing> Briefings;
};
