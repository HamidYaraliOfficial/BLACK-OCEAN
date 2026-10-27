#pragma once

#include "CoreMinimal.h"
#include "ShipBase.h"
#include "SubmarineShip.generated.h"

UENUM(BlueprintType)
enum class ESubmarineMode : uint8
{
	Surfaced, PeriscopeDepth, SilentTravel, DeepDive
};

// Fictional, gameplay-only submarine simulation. No real-world operational
// submarine data or procedures are represented; all values are abstracted
// for strategy-game balance.
UCLASS()
class ASubmarineShip : public AShipBase
{
	GENERATED_BODY()

public:
	ASubmarineShip();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Submarine")
	ESubmarineMode CurrentMode = ESubmarineMode::Surfaced;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Submarine")
	float CurrentDepthMeters = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Submarine")
	float MaxDepthMeters = 400.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Submarine", meta=(ClampMin="0.0", ClampMax="1.0"))
	float BatteryPercent = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Submarine", meta=(ClampMin="0.0", ClampMax="1.0"))
	float OxygenPercent = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Submarine", meta=(ClampMin="0.0", ClampMax="1.0"))
	float HullIntegrityPercent = 1.0f;

	// 0 = silent, 1 = very loud. Feeds the Acoustic Ocean Simulation / passive
	// sonar detection chance for nearby contacts.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Submarine", meta=(ClampMin="0.0", ClampMax="1.0"))
	float NoiseSignature = 0.5f;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Submarine")
	bool RequestDive(float TargetDepthMeters);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Submarine")
	void SetMode(ESubmarineMode NewMode);

	// Consumes battery/oxygen appropriate to the current mode; call once per
	// simulation tick while submerged.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Submarine")
	void TickLifeSupport(float DeltaMinutes);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Submarine")
	bool IsInDistress() const;
};
