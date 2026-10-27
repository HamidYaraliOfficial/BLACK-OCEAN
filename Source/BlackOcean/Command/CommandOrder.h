#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "CommandOrder.generated.h"

// A single order issued from Fleet level down to an individual vessel/group.
// Orders can be Immediate or Scheduled, and execution is gated on comms
// status, distance and weather via UCommandQueueComponent::TickQueue.
USTRUCT(BlueprintType)
struct FCommandOrder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Command")
	FName OrderId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Command")
	ECommandOrderType OrderType = ECommandOrderType::Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Command")
	FName TargetVesselOrGroupId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Command")
	FMaritimeCoordinates TargetPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Command")
	bool bIsScheduled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Command")
	FGameTimestamp ScheduledExecutionTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Command")
	bool bHasBeenDelivered = false;

	// Set by UCommandQueueComponent based on comm reliability at issue time.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Command")
	FGameTimestamp EstimatedDeliveryTime;
};
