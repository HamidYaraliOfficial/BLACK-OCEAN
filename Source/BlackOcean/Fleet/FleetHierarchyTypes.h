#pragma once

#include "CoreMinimal.h"
#include "FleetHierarchyTypes.generated.h"

// Command hierarchy: Fleet -> Task Force -> Squadron -> Group -> Vessel.
// Orders issued at a higher level cascade down; a vessel not currently
// assigned to a group still belongs to a fleet directly.
USTRUCT(BlueprintType)
struct FFleetGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	FName GroupId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	TArray<FName> VesselIds;
};

USTRUCT(BlueprintType)
struct FFleetSquadron
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	FName SquadronId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	TArray<FFleetGroup> Groups;
};

USTRUCT(BlueprintType)
struct FTaskForce
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	FName TaskForceId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	TArray<FFleetSquadron> Squadrons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	FString MissionObjectiveId;
};

USTRUCT(BlueprintType)
struct FFleet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	FName FleetId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	TArray<FTaskForce> TaskForces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Fleet")
	TArray<FName> UnassignedVesselIds;
};
