#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FactionAIController.generated.h"

UENUM(BlueprintType)
enum class ERiskTolerance : uint8
{
	Cautious, Balanced, Aggressive
};

// Behavioural profile for a fictional faction's high-level AI commander.
// Faction AI must only ever act on information it could plausibly have
// (its own sensor tracks) - never on hidden/ground-truth player state.
USTRUCT(BlueprintType)
struct FFactionDoctrine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI")
	ERiskTolerance RiskTolerance = ERiskTolerance::Balanced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI", meta=(ClampMin="0.0", ClampMax="1.0"))
	float EconomicPriority = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI", meta=(ClampMin="0.0", ClampMax="1.0"))
	float MilitaryPriority = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI", meta=(ClampMin="0.0", ClampMax="1.0"))
	float ReconPreference = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI")
	TArray<FName> PreferredFleetComposition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI")
	FString StrategicGoalSummary;
};

// Nation/organization-level AI: decides economic and fleet-composition
// priorities. Delegates individual-ship and task-force execution to
// UFleetAIController instances that only ever see what has been detected.
UCLASS(BlueprintType)
class UFactionAIController : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI")
	FName FactionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|AI")
	FFactionDoctrine Doctrine;

	// Returns a normalized decision: how much of the next budget cycle to
	// allocate toward military buildup vs economic/infrastructure growth.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|AI")
	float DecideMilitaryBudgetShare(float CurrentThreatPerception) const;
};
