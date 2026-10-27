#include "FleetManagerSubsystem.h"

void UFleetManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFleetManagerSubsystem::RegisterFleet(const FFleet& NewFleet)
{
	Fleets.Add(NewFleet.FleetId, NewFleet);
}

bool UFleetManagerSubsystem::AssignVesselToTaskForce(FName FleetId, FName TaskForceId, FName VesselId)
{
	FFleet* Fleet = Fleets.Find(FleetId);
	if (!Fleet)
	{
		return false;
	}

	Fleet->UnassignedVesselIds.Remove(VesselId);

	for (FTaskForce& TaskForce : Fleet->TaskForces)
	{
		if (TaskForce.TaskForceId == TaskForceId)
		{
			if (TaskForce.Squadrons.Num() == 0)
			{
				FFleetSquadron DefaultSquadron;
				DefaultSquadron.SquadronId = *(TaskForceId.ToString() + TEXT("_DefaultSquadron"));
				TaskForce.Squadrons.Add(DefaultSquadron);
			}
			if (TaskForce.Squadrons[0].Groups.Num() == 0)
			{
				FFleetGroup DefaultGroup;
				DefaultGroup.GroupId = *(TaskForceId.ToString() + TEXT("_DefaultGroup"));
				TaskForce.Squadrons[0].Groups.Add(DefaultGroup);
			}
			TaskForce.Squadrons[0].Groups[0].VesselIds.AddUnique(VesselId);
			return true;
		}
	}
	return false;
}

bool UFleetManagerSubsystem::GetFleet(FName FleetId, FFleet& OutFleet) const
{
	if (const FFleet* Found = Fleets.Find(FleetId))
	{
		OutFleet = *Found;
		return true;
	}
	return false;
}

TArray<FName> UFleetManagerSubsystem::GetAllVesselsInFleet(FName FleetId) const
{
	TArray<FName> Result;
	const FFleet* Fleet = Fleets.Find(FleetId);
	if (!Fleet)
	{
		return Result;
	}

	Result.Append(Fleet->UnassignedVesselIds);
	for (const FTaskForce& TaskForce : Fleet->TaskForces)
	{
		for (const FFleetSquadron& Squadron : TaskForce.Squadrons)
		{
			for (const FFleetGroup& Group : Squadron.Groups)
			{
				Result.Append(Group.VesselIds);
			}
		}
	}
	return Result;
}
