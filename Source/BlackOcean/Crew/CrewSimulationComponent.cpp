#include "CrewSimulationComponent.h"

UCrewSimulationComponent::UCrewSimulationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCrewSimulationComponent::AddCrewMember(const FCrewMember& NewMember)
{
	Roster.Add(NewMember);
}

void UCrewSimulationComponent::TickCrew(float DeltaMinutes, bool bInCombatOrEmergency)
{
	const float Scale = DeltaMinutes / 60.0f;
	const float FatigueRate = bInCombatOrEmergency ? 0.06f : 0.02f;
	const float MoraleDrift = bInCombatOrEmergency ? -0.02f : 0.005f;

	for (FCrewMember& Member : Roster)
	{
		Member.Fatigue = FMath::Clamp(Member.Fatigue + FatigueRate * Scale * (0.5f + Member.Workload), 0.0f, 1.0f);
		Member.Morale = FMath::Clamp(Member.Morale + MoraleDrift * Scale, 0.0f, 1.0f);
		// Experience creeps up slowly through active duty.
		Member.Experience = FMath::Clamp(Member.Experience + 0.001f * Scale, 0.0f, 1.0f);
	}
}

void UCrewSimulationComponent::RestCrew(float DeltaMinutes)
{
	const float Scale = DeltaMinutes / 60.0f;
	for (FCrewMember& Member : Roster)
	{
		Member.Fatigue = FMath::Clamp(Member.Fatigue - 0.10f * Scale, 0.0f, 1.0f);
		Member.Morale = FMath::Clamp(Member.Morale + 0.03f * Scale, 0.0f, 1.0f);
	}
}

float UCrewSimulationComponent::GetAverageReadinessForRole(ECrewRole Role) const
{
	float Total = 0.0f;
	int32 Count = 0;
	for (const FCrewMember& Member : Roster)
	{
		if (Member.Role == Role)
		{
			Total += Member.GetReadiness();
			++Count;
		}
	}
	return (Count > 0) ? (Total / Count) : 0.0f;
}

float UCrewSimulationComponent::GetCrewReadinessPercent() const
{
	if (Roster.Num() == 0)
	{
		return 0.0f;
	}
	float Total = 0.0f;
	for (const FCrewMember& Member : Roster)
	{
		Total += Member.GetReadiness();
	}
	return Total / Roster.Num();
}
