#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WorldStateSubsystem.generated.h"

// Aggregates the persistent, campaign-wide world state (which regions are
// discovered, global threat pressure, active world events) that other
// subsystems (Ocean, Economy, Diplomacy, AI) read from and write to.
// This is the backbone the Causal Event Graph and Simulation Inspector query.
UCLASS()
class UWorldStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|World")
	void MarkRegionDiscovered(FName RegionId);

	UFUNCTION(BlueprintPure, Category="BlackOcean|World")
	bool IsRegionDiscovered(FName RegionId) const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|World")
	void RecordCausalEvent(FName EventId, FName SourceSystem, const FString& Description);

	UFUNCTION(BlueprintPure, Category="BlackOcean|World")
	TArray<FString> GetRecentCausalLog(int32 MaxEntries) const;

private:
	UPROPERTY()
	TSet<FName> DiscoveredRegions;

	// Rolling causal log: "[Day X] SourceSystem -> Description". Consumed by
	// the Causal Event Graph / Fleet Chronicle UI.
	TArray<FString> CausalLog;
};
