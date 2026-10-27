#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BlackOceanTypes.h"
#include "ShipClasses.h"
#include "ShipBase.generated.h"

class UShipComponentBase;
class UShipDamageComponent;

// Persistent per-mission history entry, kept for the Fleet Chronicle / After
// Action Review even after the ship returns to port.
USTRUCT(BlueprintType)
struct FShipMissionRecord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ship")
	FName MissionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ship")
	FGameTimestamp CompletedAt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ship")
	FString Outcome;
};

// Base actor for every fictional vessel in BLACK OCEAN. Holds the persistent
// state (fuel, crew readiness, maintenance, equipment condition, mission
// history) that must survive between missions, and owns the per-system
// UShipComponentBase instances that make up its internal simulation.
UCLASS()
class AShipBase : public APawn
{
	GENERATED_BODY()

public:
	AShipBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ship")
	FName ShipId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ship")
	FText ShipName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ship")
	FShipClassDefinition ClassDefinition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Ship", meta=(ClampMin="0.0", ClampMax="1.0"))
	float FuelPercent = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Ship", meta=(ClampMin="0.0", ClampMax="1.0"))
	float CrewReadinessPercent = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Ship", meta=(ClampMin="0.0", ClampMax="1.0"))
	float MaintenanceLevelPercent = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Ship", meta=(ClampMin="0.0", ClampMax="1.0"))
	float EquipmentConditionPercent = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Ship")
	TArray<FShipMissionRecord> MissionHistory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Ship")
	TArray<TObjectPtr<UShipComponentBase>> ShipSystems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Ship")
	TObjectPtr<UShipDamageComponent> DamageComponent;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Ship")
	UShipComponentBase* GetSystem(EShipSystemType SystemType) const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Ship")
	void ConsumeFuel(float PercentToConsume);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Ship")
	void RecordMissionResult(FName MissionId, const FGameTimestamp& CompletedAt, const FString& Outcome);

	// Combined 0-1 score used by Fleet Readiness Model, mission eligibility
	// checks, and the Ship Management Screen.
	UFUNCTION(BlueprintPure, Category="BlackOcean|Ship")
	float GetOverallReadiness() const;

protected:
	virtual void BeginPlay() override;
};
