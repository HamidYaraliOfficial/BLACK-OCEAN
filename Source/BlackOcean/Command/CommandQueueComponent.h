#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandOrder.h"
#include "CommandQueueComponent.generated.h"

// Per-vessel/task-force inbox for FCommandOrder. Models the Command Delay
// System: an order issued far away or under poor communications does not
// take effect instantly.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UCommandQueueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCommandQueueComponent();

	// CommReliability in [0,1]: 1 = instant delivery, 0 = order may never
	// arrive until reliability improves. DistanceKm lengthens the delay.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Command")
	void SubmitOrder(FCommandOrder NewOrder, float CommReliability, float DistanceKm, const FGameTimestamp& IssuedAt);

	// Returns orders that have now arrived and should be executed this tick,
	// removing them from the pending queue.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Command")
	TArray<FCommandOrder> PopDeliveredOrders(const FGameTimestamp& Now);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Command")
	int32 GetPendingOrderCount() const { return PendingOrders.Num(); }

private:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Command")
	TArray<FCommandOrder> PendingOrders;
};
