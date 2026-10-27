#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "MissionObjective.generated.h"

UENUM(BlueprintType)
enum class EObjectiveState : uint8
{
	Pending, Active, Completed, Failed, RecoveryInProgress, AlternativeSuccess
};

USTRUCT(BlueprintType)
struct FMissionObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	FName ObjectiveId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	bool bIsOptional = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	EObjectiveState State = EObjectiveState::Pending;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	TArray<FName> DependsOnObjectiveIds;
};

USTRUCT(BlueprintType)
struct FMissionBriefing
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	FName MissionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	FText SituationSummary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	TArray<FMissionObjective> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	TArray<FName> AvailableAssetIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Missions")
	TArray<FString> Constraints;
};
