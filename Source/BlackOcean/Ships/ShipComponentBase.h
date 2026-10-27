#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackOceanTypes.h"
#include "ShipComponentBase.generated.h"

// Base for every independently-stateful ship system (Hull, Engine, Sensors,
// Comms, ...). Each instance tracks its own condition so a single hit or
// failure can degrade one system without silently affecting the rest.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UShipComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UShipComponentBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipSystem")
	EShipSystemType SystemType = EShipSystemType::Hull;

	// 0 = fully destroyed/offline, 1 = fully operational.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|ShipSystem", meta=(ClampMin="0.0", ClampMax="1.0"))
	float ConditionPercent = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|ShipSystem")
	bool bIsIsolated = false;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|ShipSystem")
	virtual void ApplyDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|ShipSystem")
	virtual void ApplyRepair(float RepairAmount);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|ShipSystem")
	void SetIsolated(bool bNewIsolated) { bIsIsolated = bNewIsolated; }

	UFUNCTION(BlueprintPure, Category="BlackOcean|ShipSystem")
	bool IsOperational() const { return !bIsIsolated && ConditionPercent > 0.05f; }

	// Efficiency multiplier this system contributes to the ship (non-linear:
	// a badly damaged system degrades faster than it visually implies).
	UFUNCTION(BlueprintPure, Category="BlackOcean|ShipSystem")
	float GetEfficiencyMultiplier() const;
};
