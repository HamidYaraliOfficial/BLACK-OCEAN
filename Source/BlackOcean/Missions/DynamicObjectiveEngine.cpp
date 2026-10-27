#include "DynamicObjectiveEngine.h"

void UDynamicObjectiveEngine::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDynamicObjectiveEngine::RegisterBriefing(const FMissionBriefing& Briefing)
{
	Briefings.Add(Briefing.MissionId, Briefing);
}

bool UDynamicObjectiveEngine::SetObjectiveState(FName MissionId, FName ObjectiveId, EObjectiveState NewState)
{
	FMissionBriefing* Briefing = Briefings.Find(MissionId);
	if (!Briefing)
	{
		return false;
	}
	for (FMissionObjective& Objective : Briefing->Objectives)
	{
		if (Objective.ObjectiveId == ObjectiveId)
		{
			Objective.State = NewState;
			return true;
		}
	}
	return false;
}

void UDynamicObjectiveEngine::RefreshObjectiveAvailability(FName MissionId)
{
	FMissionBriefing* Briefing = Briefings.Find(MissionId);
	if (!Briefing)
	{
		return;
	}

	for (FMissionObjective& Objective : Briefing->Objectives)
	{
		if (Objective.State != EObjectiveState::Pending)
		{
			continue;
		}

		bool bDependenciesMet = true;
		for (FName DependencyId : Objective.DependsOnObjectiveIds)
		{
			const FMissionObjective* Dependency = Briefing->Objectives.FindByPredicate(
				[DependencyId](const FMissionObjective& O) { return O.ObjectiveId == DependencyId; });
			if (!Dependency || Dependency->State != EObjectiveState::Completed)
			{
				bDependenciesMet = false;
				break;
			}
		}

		if (bDependenciesMet)
		{
			Objective.State = EObjectiveState::Active;
		}
	}
}

bool UDynamicObjectiveEngine::IsMissionComplete(FName MissionId) const
{
	const FMissionBriefing* Briefing = Briefings.Find(MissionId);
	if (!Briefing)
	{
		return false;
	}
	for (const FMissionObjective& Objective : Briefing->Objectives)
	{
		if (!Objective.bIsOptional &&
			Objective.State != EObjectiveState::Completed &&
			Objective.State != EObjectiveState::AlternativeSuccess)
		{
			return false;
		}
	}
	return true;
}

bool UDynamicObjectiveEngine::GetBriefing(FName MissionId, FMissionBriefing& OutBriefing) const
{
	if (const FMissionBriefing* Found = Briefings.Find(MissionId))
	{
		OutBriefing = *Found;
		return true;
	}
	return false;
}
