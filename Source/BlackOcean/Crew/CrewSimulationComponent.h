#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CrewMember.h"
#include "CrewSimulationComponent.generated.h"

// Owns the full crew roster for one ship and advances fatigue/morale over
// time. The Task Assignment Engine (Command module) reads GetReadinessFor()
// to decide how well a role can currently perform.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UCrewSimulationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCrewSimulationComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Crew")
	TArray<FCrewMember> Roster;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Crew")
	void AddCrewMember(const FCrewMember& NewMember);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Crew")
	void TickCrew(float DeltaMinutes, bool bInCombatOrEmergency);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Crew")
	float GetAverageReadinessForRole(ECrewRole Role) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Crew")
	float GetCrewReadinessPercent() const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Crew")
	void RestCrew(float DeltaMinutes);
};
