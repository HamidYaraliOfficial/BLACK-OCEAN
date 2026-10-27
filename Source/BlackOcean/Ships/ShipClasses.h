#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "ShipClasses.generated.h"

// Design-time stats for a fictional vessel class. Populated from Data Tables
// so designers can add/rebalance classes without touching C++.
USTRUCT(BlueprintType)
struct FShipClassDefinition : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	EShipClass ShipClass = EShipClass::FrigateLike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	float MaxSpeedKnots = 28.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	float SensorCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	int32 CrewCapacity = 120;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	float FuelCapacityUnits = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	float MaintenanceDemand = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	float CargoCapacityUnits = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	float CommunicationsRangeKm = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	FString DefaultMissionRole = TEXT("General Purpose");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	int32 ConstructionCost = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|ShipClass")
	int32 ConstructionDays = 30;
};
