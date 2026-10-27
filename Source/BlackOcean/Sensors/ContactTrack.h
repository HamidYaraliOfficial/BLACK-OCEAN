#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "ContactTrack.generated.h"

UENUM(BlueprintType)
enum class ESensorSourceType : uint8
{
	RadarLike, Sonar, OpticalCamera, InfraredLike, PassiveAcoustic,
	ReconDrone, SatelliteStyleFeed, HumanReport
};

// A tracked, possibly-uncertain contact. AI and UI must only ever read this
// struct (never ground-truth actor state) so the game never "cheats" by
// reacting to information the player/AI has not actually sensed.
USTRUCT(BlueprintType)
struct FContactTrack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors")
	FName TrackId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors")
	FMaritimeCoordinates LastKnownPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors")
	FGameTimestamp LastUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors")
	float EstimatedSpeedKnots = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors")
	float EstimatedHeadingDegrees = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Confidence = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors")
	EContactClassification Classification = EContactClassification::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Sensors")
	TArray<ESensorSourceType> ContributingSources;
};
