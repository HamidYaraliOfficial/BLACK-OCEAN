#include "CommandQueueComponent.h"

UCommandQueueComponent::UCommandQueueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCommandQueueComponent::SubmitOrder(FCommandOrder NewOrder, float CommReliability, float DistanceKm, const FGameTimestamp& IssuedAt)
{
	CommReliability = FMath::Clamp(CommReliability, 0.01f, 1.0f);

	// Base delay grows with distance and shrinks with reliability; poor comms
	// over long range can delay an order by hours of campaign time.
	const double BaseDelayMinutes = (DistanceKm / 40.0) * (1.0 / CommReliability);

	FCommandOrder OrderCopy = NewOrder;
	OrderCopy.EstimatedDeliveryTime = IssuedAt;
	OrderCopy.EstimatedDeliveryTime.MinuteOfDay += FMath::RoundToInt(BaseDelayMinutes);
	while (OrderCopy.EstimatedDeliveryTime.MinuteOfDay >= 1440)
	{
		OrderCopy.EstimatedDeliveryTime.MinuteOfDay -= 1440;
		OrderCopy.EstimatedDeliveryTime.CampaignDay += 1;
	}

	if (OrderCopy.bIsScheduled && OrderCopy.ScheduledExecutionTime.ToAbsoluteMinutes() > OrderCopy.EstimatedDeliveryTime.ToAbsoluteMinutes())
	{
		OrderCopy.EstimatedDeliveryTime = OrderCopy.ScheduledExecutionTime;
	}

	PendingOrders.Add(OrderCopy);
}

TArray<FCommandOrder> UCommandQueueComponent::PopDeliveredOrders(const FGameTimestamp& Now)
{
	TArray<FCommandOrder> Delivered;
	for (int32 i = PendingOrders.Num() - 1; i >= 0; --i)
	{
		if (PendingOrders[i].EstimatedDeliveryTime.ToAbsoluteMinutes() <= Now.ToAbsoluteMinutes())
		{
			PendingOrders[i].bHasBeenDelivered = true;
			Delivered.Add(PendingOrders[i]);
			PendingOrders.RemoveAt(i);
		}
	}
	return Delivered;
}
