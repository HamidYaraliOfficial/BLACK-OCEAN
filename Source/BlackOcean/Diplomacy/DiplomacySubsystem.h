#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DiplomacySubsystem.generated.h"

UENUM(BlueprintType)
enum class ETreatyType : uint8
{
	TradeAgreement, PortAccess, IntelligenceSharing, ResearchCooperation,
	NavigationRights, SearchAndRescueAgreement
};

USTRUCT(BlueprintType)
struct FDiplomaticRelation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Diplomacy")
	FName OtherFactionId;

	// -1 (hostile) to +1 (allied).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Diplomacy", meta=(ClampMin="-1.0", ClampMax="1.0"))
	float RelationScore = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Diplomacy")
	TArray<ETreatyType> ActiveTreaties;
};

// Tracks bilateral relations between fictional factions/nations, driven by
// trade volume, world events, border incidents and explicit player decisions.
UCLASS()
class UDiplomacySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Diplomacy")
	void AdjustRelation(FName OtherFactionId, float Delta);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Diplomacy")
	bool ProposeTreaty(FName OtherFactionId, ETreatyType TreatyType);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Diplomacy")
	bool HasTreaty(FName OtherFactionId, ETreatyType TreatyType) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Diplomacy")
	float GetRelationScore(FName OtherFactionId) const;

private:
	UPROPERTY()
	TMap<FName, FDiplomaticRelation> Relations;

	// Minimum relation score required before a given treaty type can be
	// proposed successfully; sensitive treaties require more trust.
	static float GetMinimumRelationForTreaty(ETreatyType TreatyType);
};
