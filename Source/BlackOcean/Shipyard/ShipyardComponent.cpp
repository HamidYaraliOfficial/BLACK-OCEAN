#include "ShipyardComponent.h"

UShipyardComponent::UShipyardComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FConstructionOrder UShipyardComponent::QueueConstruction(const FShipClassDefinition& ClassDefinition)
{
	FConstructionOrder Order;
	Order.OrderId = *FString::Printf(TEXT("ConstructionOrder_%d"), ++OrderCounter);
	Order.ShipClassToBuild = ClassDefinition.ShipClass;
	Order.TotalCost = ClassDefinition.ConstructionCost;

	// Higher tech/industrial capacity shortens build time, within reason.
	const float TimeMultiplier = FMath::Clamp(1.0f / FMath::Max(0.1f, (TechnologyLevel + IndustrialCapacity) / 2.0f), 0.4f, 2.0f);
	Order.DaysRemaining = FMath::Max(1, FMath::RoundToInt(ClassDefinition.ConstructionDays * TimeMultiplier));

	ActiveOrders.Add(Order);
	return Order;
}

TArray<FName> UShipyardComponent::AdvanceConstructionByOneDay()
{
	TArray<FName> CompletedOrderIds;
	for (int32 i = ActiveOrders.Num() - 1; i >= 0; --i)
	{
		if (!ActiveOrders[i].bIsPaidFor)
		{
			continue; // Unpaid orders sit in queue without progressing.
		}
		ActiveOrders[i].DaysRemaining--;
		if (ActiveOrders[i].DaysRemaining <= 0)
		{
			CompletedOrderIds.Add(ActiveOrders[i].OrderId);
			ActiveOrders.RemoveAt(i);
		}
	}
	return CompletedOrderIds;
}
