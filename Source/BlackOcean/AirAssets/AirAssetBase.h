#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AirAssetBase.generated.h"

UENUM(BlueprintType)
enum class EAirAssetType : uint8
{
	ReconDrone, ScoutAircraft, HelicopterLikeUnit
};

UENUM(BlueprintType)
enum class EAirMissionType : uint8
{
	Recon, Search, Rescue, Mapping, Observation
};

// Fictional launch-and-recover air asset (drone/scout/helicopter-like unit)
// operated from a carrier-capable ship. Feeds live sensor data to the
// Tactical Map while airborne.
UCLASS()
class AAirAssetBase : public APawn
{
	GENERATED_BODY()

public:
	AAirAssetBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Air")
	EAirAssetType AssetType = EAirAssetType::ReconDrone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Air", meta=(ClampMin="0.0", ClampMax="1.0"))
	float FuelOrBatteryPercent = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Air")
	float RangeKm = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Air")
	float SensorPayloadQuality = 0.7f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Air")
	bool bHasCommunicationLink = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Air", meta=(ClampMin="0.0", ClampMax="1.0"))
	float DamageState = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Air")
	EAirMissionType AssignedMission = EAirMissionType::Recon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Air")
	FName HostShipId;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Air")
	bool LaunchFrom(FName ShipId);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Air")
	void AssignMission(EAirMissionType MissionType);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Air")
	void TickFlight(float DeltaMinutes);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Air")
	bool NeedsRecovery() const { return FuelOrBatteryPercent < 0.2f || DamageState > 0.7f; }
};
