#include "PortActor.h"

APortActor::APortActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APortActor::BeginPlay()
{
	Super::BeginPlay();
}

void APortActor::SetOperatingWindows(const TArray<FOperatingWindow>& NewWindows, bool bNewOpen24Hours)
{
	OperatingHours.Windows = NewWindows;
	OperatingHours.bOpen24Hours = bNewOpen24Hours;
}

FString APortActor::GetStatusDisplayString(const FGameTimestamp& Now) const
{
	if (OperatingHours.bOpen24Hours)
	{
		return TEXT("Open 24 hours");
	}

	const bool bOpen = IsCurrentlyOpen(Now);
	const int32 MinutesUntilChange = OperatingHours.GetMinutesUntilNextChange(Now);

	if (MinutesUntilChange < 0)
	{
		return bOpen ? TEXT("Open") : TEXT("Closed");
	}

	const int32 Hours = MinutesUntilChange / 60;
	const int32 Minutes = MinutesUntilChange % 60;

	return bOpen
		? FString::Printf(TEXT("Open - closes in %dh %dm"), Hours, Minutes)
		: FString::Printf(TEXT("Closed - opens in %dh %dm"), Hours, Minutes);
}

bool APortActor::RequestDock()
{
	if (Stats.OccupiedDocks >= Stats.DockCapacity)
	{
		return false;
	}
	Stats.OccupiedDocks++;
	return true;
}

void APortActor::ReleaseDock()
{
	Stats.OccupiedDocks = FMath::Max(0, Stats.OccupiedDocks - 1);
}
