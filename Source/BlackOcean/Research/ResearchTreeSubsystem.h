#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ResearchTreeSubsystem.generated.h"

UENUM(BlueprintType)
enum class EResearchCategory : uint8
{
	Sensors, Propulsion, Communications, Automation, Materials, EnergyStorage,
	UnderwaterSystems, ReconSystems, Drones, ShipDesign, Logistics, DamageControl
};

USTRUCT(BlueprintType)
struct FResearchNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Research")
	FName NodeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Research")
	EResearchCategory Category = EResearchCategory::Sensors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Research")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Research")
	int32 TimeDaysRequired = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Research")
	int32 BudgetCost = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Research")
	TArray<FName> Prerequisites;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Research")
	bool bIsCompleted = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Research")
	int32 DaysInvested = 0;
};

// Tech tree covering Sensors/Propulsion/Comms/Automation/Materials/Energy/
// Underwater/Recon/Drones/ShipDesign/Logistics/DamageControl. Completed
// nodes are queried by Ships/Shipyard/Sensors/etc. to apply real bonuses.
UCLASS()
class UResearchTreeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Research")
	void RegisterNode(const FResearchNode& Node);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Research")
	bool ArePrerequisitesMet(FName NodeId) const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Research")
	bool StartOrContinueResearch(FName NodeId, int32 DaysToApply, int32 AvailableResearchCapacityDays);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Research")
	bool IsCompleted(FName NodeId) const;

private:
	UPROPERTY()
	TMap<FName, FResearchNode> Nodes;
};
