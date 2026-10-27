#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortOperatingHours.h"
#include "PortActor.generated.h"

USTRUCT(BlueprintType)
struct FPortStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	int32 DockCapacity = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	int32 OccupiedDocks = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	float RepairCapacityPerDay = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	float FuelReserveUnits = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	float StorageCapacityUnits = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	bool bHasShipyard = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	float TradeVolumePerDay = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port", meta=(ClampMin="0.0", ClampMax="1.0"))
	float SecurityLevel = 0.6f;
};

// A fictional port. Exposes a player-configurable operating schedule so the
// UI can always show current status and a countdown to the next change,
// alongside the standard capacity/repair/fuel/storage/trade/security stats.
UCLASS()
class APortActor : public AActor
{
	GENERATED_BODY()

public:
	APortActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	FName PortId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	FText PortDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	FPortStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	FFacilityOperatingHours OperatingHours;

	// Lets the player type in/edit the schedule from the Port Management
	// Dashboard rather than it being hard-coded per port.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Port")
	void SetOperatingWindows(const TArray<FOperatingWindow>& NewWindows, bool bNewOpen24Hours);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Port")
	bool IsCurrentlyOpen(const FGameTimestamp& Now) const { return OperatingHours.IsOpenAt(Now.MinuteOfDay); }

	// Human-readable status string, e.g. "Open - closes in 3h 20m" or
	// "Closed - opens in 0h 45m", for direct display in the Port dashboard.
	UFUNCTION(BlueprintPure, Category="BlackOcean|Port")
	FString GetStatusDisplayString(const FGameTimestamp& Now) const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Port")
	bool RequestDock();

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Port")
	void ReleaseDock();

protected:
	virtual void BeginPlay() override;
};
