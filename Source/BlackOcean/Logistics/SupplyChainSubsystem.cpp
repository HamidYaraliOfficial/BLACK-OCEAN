#include "SupplyChainSubsystem.h"

void USupplyChainSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

FString USupplyChainSubsystem::MakeStockKey(FName BaseId, ESupplyResourceType ResourceType)
{
	return FString::Printf(TEXT("%s_%d"), *BaseId.ToString(), static_cast<int32>(ResourceType));
}

void USupplyChainSubsystem::RegisterRoute(const FSupplyRoute& Route)
{
	Routes.Add(Route.RouteId, Route);
}

void USupplyChainSubsystem::SetRouteInterrupted(FName RouteId, bool bInterrupted)
{
	if (FSupplyRoute* Route = Routes.Find(RouteId))
	{
		Route->bIsInterrupted = bInterrupted;
	}
}

void USupplyChainSubsystem::StockResource(FName BaseId, ESupplyResourceType ResourceType, float Amount)
{
	const FString Key = MakeStockKey(BaseId, ResourceType);
	float& Current = Stockpiles.FindOrAdd(Key, 0.0f);
	Current = FMath::Max(0.0f, Current + Amount);
}

bool USupplyChainSubsystem::ConsumeResource(FName BaseId, ESupplyResourceType ResourceType, float Amount)
{
	const FString Key = MakeStockKey(BaseId, ResourceType);
	float* Current = Stockpiles.Find(Key);
	if (!Current || *Current < Amount)
	{
		return false;
	}
	*Current -= Amount;
	return true;
}

void USupplyChainSubsystem::TickDailySupplyRun()
{
	for (const auto& Pair : Routes)
	{
		const FSupplyRoute& Route = Pair.Value;
		const float Throughput = Route.GetEffectiveThroughput();
		if (Throughput <= 0.0f)
		{
			continue;
		}
		// Simplified: draws generic supply units from origin and adds them to
		// destination as maintenance materials; a fuller build would split
		// this per resource type by port export composition.
		if (ConsumeResource(Route.OriginPortId, ESupplyResourceType::MaintenanceMaterials, Throughput))
		{
			StockResource(Route.DestinationBaseId, ESupplyResourceType::MaintenanceMaterials, Throughput);
		}
	}
}

float USupplyChainSubsystem::GetStockLevel(FName BaseId, ESupplyResourceType ResourceType) const
{
	const FString Key = MakeStockKey(BaseId, ResourceType);
	const float* Current = Stockpiles.Find(Key);
	return Current ? *Current : 0.0f;
}
