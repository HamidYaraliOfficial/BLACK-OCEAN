#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "OceanRegionData.generated.h"

// Live environmental state for a single maritime region. The Global Maritime
// Simulation Engine keeps one of these per region and feeds it into movement,
// detection, communication and mission-eligibility checks.
USTRUCT(BlueprintType)
struct FOceanRegionState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	FName RegionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	EMaritimeRegionType RegionType = EMaritimeRegionType::OpenSea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	float AverageDepthMeters = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	float WaterTemperatureCelsius = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	float CurrentSpeedKnots = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	float CurrentHeadingDegrees = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	float WaveHeightMeters = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	float VisibilityKm = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean")
	EWeatherState Weather = EWeatherState::Clear;

	// 0 (empty) - 1 (congested): drives Maritime Traffic Simulation density.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean", meta=(ClampMin="0.0", ClampMax="1.0"))
	float TrafficDensity = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean", meta=(ClampMin="0.0", ClampMax="1.0"))
	float ResourceAvailability = 0.5f;

	// 0 (safe) - 1 (severe): consumed by Faction AI, Difficulty scaling, and Forecasts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Ocean", meta=(ClampMin="0.0", ClampMax="1.0"))
	float ThreatLevel = 0.0f;

	// Derived: how much this region currently degrades sensor/communication range.
	float GetEnvironmentalDegradationFactor() const
	{
		float Degradation = 0.0f;
		Degradation += (1.0f - FMath::Clamp(VisibilityKm / 20.0f, 0.0f, 1.0f)) * 0.5f;
		Degradation += FMath::Clamp(WaveHeightMeters / 8.0f, 0.0f, 1.0f) * 0.3f;
		if (Weather == EWeatherState::Storm) Degradation += 0.3f;
		if (Weather == EWeatherState::Fog) Degradation += 0.25f;
		return FMath::Clamp(Degradation, 0.0f, 1.0f);
	}
};
