#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipClasses.h"
#include "ShipyardComponent.generated.h"

USTRUCT(BlueprintType)
struct FConstructionOrder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Shipyard")
	FName OrderId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Shipyard")
	EShipClass ShipClassToBuild = EShipClass::FrigateLike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Shipyard")
	int32 DaysRemaining = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Shipyard")
	int32 TotalCost = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Shipyard")
	bool bIsPaidFor = false;
};

// Handles new-construction orders, major refits and upgrades for a port with
// a shipyard. Time/cost scale with TechnologyLevel and IndustrialCapacity.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UShipyardComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShipyardComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Shipyard", meta=(ClampMin="0.1", ClampMax="3.0"))
	float TechnologyLevel = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Shipyard", meta=(ClampMin="0.1", ClampMax="3.0"))
	float IndustrialCapacity = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Shipyard")
	TArray<FConstructionOrder> ActiveOrders;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Shipyard")
	FConstructionOrder QueueConstruction(const FShipClassDefinition& ClassDefinition);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Shipyard")
	TArray<FName> AdvanceConstructionByOneDay();

private:
	int32 OrderCounter = 0;
};
