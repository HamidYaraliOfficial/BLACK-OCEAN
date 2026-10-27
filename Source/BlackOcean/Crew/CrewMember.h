#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "CrewMember.generated.h"

// A single crew member/group serving a fictional vessel. Grouped stats
// (Experience/Fatigue/Readiness/Skill/Morale/Workload) feed directly into
// the efficiency of whatever ship system this crew is assigned to.
USTRUCT(BlueprintType)
struct FCrewMember
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew")
	FName CrewId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew")
	ECrewRole Role = ECrewRole::SupportTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Experience = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Fatigue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Skill = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Morale = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Crew", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Workload = 0.3f;

	// Composite score consumed by ship-system efficiency and task assignment.
	float GetReadiness() const
	{
		const float FatiguePenalty = Fatigue * 0.5f;
		const float MoraleBonus = (Morale - 0.5f) * 0.2f;
		return FMath::Clamp(Skill * 0.5f + Experience * 0.3f - FatiguePenalty + MoraleBonus, 0.0f, 1.0f);
	}
};
