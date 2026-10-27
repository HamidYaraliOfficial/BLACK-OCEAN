#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ContactTrack.h"
#include "SensorFusionComponent.generated.h"

// Combines readings from multiple sensor sources into a single confidence-
// weighted contact classification, and lets tracks decay to Uncertain when
// no sensor has refreshed them for a while.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class USensorFusionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USensorFusionComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Sensors")
	TArray<FContactTrack> Tracks;

	// Merges a new sensor reading into an existing track (by proximity) or
	// creates a new one. ReliabilityOfSource in [0,1] weights how much this
	// reading shifts the fused classification/confidence.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Sensors")
	void IngestReading(FName ApproxTrackId, ESensorSourceType Source, float ReliabilityOfSource,
		EContactClassification ObservedClassification, const FMaritimeCoordinates& ObservedPosition,
		const FGameTimestamp& Now);

	// Ages out tracks: confidence decays when no source has refreshed them;
	// very stale/low-confidence tracks are dropped entirely.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Sensors")
	void DecayTracks(const FGameTimestamp& Now, float MinutesPerConfidenceStep);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Sensors")
	const TArray<FContactTrack>& GetAllTracks() const { return Tracks; }

private:
	FContactTrack* FindTrack(FName TrackId);
};
