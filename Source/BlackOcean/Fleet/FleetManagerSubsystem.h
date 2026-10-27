#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FleetHierarchyTypes.h"
#include "FleetManagerSubsystem.generated.h"

// Owns every fleet's command hierarchy and exposes lookups/composition edits
// used by the Fleet Composition Planner and the Command module.
UCLASS()
class UFleetManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Fleet")
	void RegisterFleet(const FFleet& NewFleet);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Fleet")
	bool AssignVesselToTaskForce(FName FleetId, FName TaskForceId, FName VesselId);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Fleet")
	bool GetFleet(FName FleetId, FFleet& OutFleet) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Fleet")
	TArray<FName> GetAllVesselsInFleet(FName FleetId) const;

private:
	UPROPERTY()
	TMap<FName, FFleet> Fleets;
};
