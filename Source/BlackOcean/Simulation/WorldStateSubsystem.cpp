#include "WorldStateSubsystem.h"

void UWorldStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UWorldStateSubsystem::MarkRegionDiscovered(FName RegionId)
{
	DiscoveredRegions.Add(RegionId);
}

bool UWorldStateSubsystem::IsRegionDiscovered(FName RegionId) const
{
	return DiscoveredRegions.Contains(RegionId);
}

void UWorldStateSubsystem::RecordCausalEvent(FName EventId, FName SourceSystem, const FString& Description)
{
	CausalLog.Add(FString::Printf(TEXT("[%s] %s -> %s"), *EventId.ToString(), *SourceSystem.ToString(), *Description));
	const int32 MaxLogSize = 500;
	if (CausalLog.Num() > MaxLogSize)
	{
		CausalLog.RemoveAt(0, CausalLog.Num() - MaxLogSize);
	}
}

TArray<FString> UWorldStateSubsystem::GetRecentCausalLog(int32 MaxEntries) const
{
	TArray<FString> Result;
	const int32 Start = FMath::Max(0, CausalLog.Num() - MaxEntries);
	for (int32 i = Start; i < CausalLog.Num(); ++i)
	{
		Result.Add(CausalLog[i]);
	}
	return Result;
}
