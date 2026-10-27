#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OceanRegionData.h"
#include "OceanSimulationSubsystem.generated.h"

// Global Maritime Simulation Engine: owns per-region ocean/weather state and
// advances it deterministically each simulation tick. Ship movement, sensor
// range, comms reliability and mission viability all query this subsystem.
UCLASS()
class UOceanSimulationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Ocean")
	void RegisterRegion(const FOceanRegionState& InitialState);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Ocean")
	bool GetRegionState(FName RegionId, FOceanRegionState& OutState) const;

	// Advances weather/current drift for every region. DeltaMinutes should
	// come from UTimeControlSubsystem so weather evolves deterministically.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Ocean")
	void TickOcean(float DeltaMinutes);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Ocean")
	void ApplyStormToRegion(FName RegionId, float IntensityDelta);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Ocean")
	TArray<FName> GetAllRegionIds() const;

private:
	UPROPERTY()
	TMap<FName, FOceanRegionState> Regions;

	// Simple bounded random walk so weather drifts smoothly rather than
	// jumping discontinuously between ticks; storms are seeded externally
	// by the Dynamic Maritime Threat Engine.
	void DriftRegion(FOceanRegionState& Region, float DeltaMinutes) const;
};
