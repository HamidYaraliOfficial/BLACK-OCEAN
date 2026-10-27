#include "OceanSimulationSubsystem.h"

void UOceanSimulationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UOceanSimulationSubsystem::RegisterRegion(const FOceanRegionState& InitialState)
{
	Regions.Add(InitialState.RegionId, InitialState);
}

bool UOceanSimulationSubsystem::GetRegionState(FName RegionId, FOceanRegionState& OutState) const
{
	if (const FOceanRegionState* Found = Regions.Find(RegionId))
	{
		OutState = *Found;
		return true;
	}
	return false;
}

void UOceanSimulationSubsystem::DriftRegion(FOceanRegionState& Region, float DeltaMinutes) const
{
	const float DriftScale = DeltaMinutes / 60.0f;

	Region.WaveHeightMeters = FMath::Clamp(
		Region.WaveHeightMeters + FMath::FRandRange(-0.1f, 0.1f) * DriftScale, 0.1f, 15.0f);

	Region.VisibilityKm = FMath::Clamp(
		Region.VisibilityKm + FMath::FRandRange(-0.5f, 0.5f) * DriftScale, 0.2f, 40.0f);

	// Storms slowly decay back toward clear conditions unless re-seeded.
	if (Region.Weather == EWeatherState::Storm && FMath::FRand() < 0.02f * DriftScale)
	{
		Region.Weather = EWeatherState::Overcast;
	}

	Region.TrafficDensity = FMath::Clamp(
		Region.TrafficDensity + FMath::FRandRange(-0.02f, 0.02f) * DriftScale, 0.0f, 1.0f);
}

void UOceanSimulationSubsystem::TickOcean(float DeltaMinutes)
{
	for (auto& Pair : Regions)
	{
		DriftRegion(Pair.Value, DeltaMinutes);
	}
}

void UOceanSimulationSubsystem::ApplyStormToRegion(FName RegionId, float IntensityDelta)
{
	if (FOceanRegionState* Region = Regions.Find(RegionId))
	{
		Region->ThreatLevel = FMath::Clamp(Region->ThreatLevel + IntensityDelta, 0.0f, 1.0f);
		Region->WaveHeightMeters = FMath::Clamp(Region->WaveHeightMeters + IntensityDelta * 6.0f, 0.1f, 15.0f);
		Region->VisibilityKm = FMath::Clamp(Region->VisibilityKm - IntensityDelta * 15.0f, 0.2f, 40.0f);
		if (IntensityDelta > 0.2f)
		{
			Region->Weather = EWeatherState::Storm;
		}
	}
}

TArray<FName> UOceanSimulationSubsystem::GetAllRegionIds() const
{
	TArray<FName> Ids;
	Regions.GetKeys(Ids);
	return Ids;
}
