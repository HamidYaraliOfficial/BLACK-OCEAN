#pragma once

#include "CoreMinimal.h"
#include "CrewRelationship.generated.h"

// Officer-to-officer relationship used by the Branching Narrative System:
// affects group task efficiency and appears in dialogue conditions.
USTRUCT(BlueprintType)
struct FCrewRelationship
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew")
	FName CrewIdA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew")
	FName CrewIdB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Trust = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Cooperation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Rivalry = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Loyalty = 0.5f;

	// Combined multiplier applied to shared-task efficiency when both crew
	// members are assigned to the same system.
	float GetTeamworkMultiplier() const
	{
		return FMath::Clamp(0.5f + Trust * 0.2f + Cooperation * 0.2f + Loyalty * 0.1f - Rivalry * 0.3f, 0.2f, 1.3f);
	}
};
