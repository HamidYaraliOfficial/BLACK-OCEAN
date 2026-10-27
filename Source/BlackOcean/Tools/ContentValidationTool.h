#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ContentValidationTool.generated.h"

UENUM(BlueprintType)
enum class EValidationIssueType : uint8
{
	MissingReference, DuplicateId, BrokenScenario, InvalidRoute,
	MissingLocalization, CircularDependency, InvalidShipConfiguration,
	ImpossibleMission, BrokenDialogue
};

USTRUCT(BlueprintType)
struct FValidationIssue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Tools")
	EValidationIssueType IssueType = EValidationIssueType::MissingReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Tools")
	FString Context;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Tools")
	FString Description;
};

// Editor/CI-facing content validator: scans data-driven content (scenarios,
// routes, ship configs, localization tables, dialogue graphs) for problems
// before they reach a build. Designed to be invoked from run-tests.ps1 /
// package.ps1 as part of CI so broken content fails the pipeline early.
UCLASS(BlueprintType)
class UContentValidationTool : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Tools")
	static bool CheckForDuplicateIds(const TArray<FName>& Ids, TArray<FValidationIssue>& OutIssues);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Tools")
	static bool CheckLocalizationCompleteness(const TMap<FString, FString>& ReferenceTable,
		const TMap<FString, FString>& TargetTable, const FString& TargetLanguageLabel,
		TArray<FValidationIssue>& OutIssues);
};
