#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EconomySubsystem.generated.h"

UENUM(BlueprintType)
enum class EBudgetCategory : uint8
{
	Navy, Research, Infrastructure, Logistics, Industry, Environment, EmergencyReserve
};

UENUM(BlueprintType)
enum class EStrategicResource : uint8
{
	IndustrialMaterials, Energy, RareComponents, Food, Electronics, StrategicMaterials
};

// Fictional national/organizational budget and resource ledger. AllocateBudget
// lets the player (or Economic AI) split the annual budget across categories;
// financial pressure here should visibly constrain Fleet Size and Readiness.
UCLASS()
class UEconomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Economy")
	void SetAnnualBudget(float TotalBudget);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Economy")
	bool AllocateBudget(EBudgetCategory Category, float Amount);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Economy")
	bool SpendFromCategory(EBudgetCategory Category, float Amount);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Economy")
	float GetRemainingUnallocated() const { return AnnualBudget - TotalAllocated; }

	UFUNCTION(BlueprintPure, Category="BlackOcean|Economy")
	float GetCategoryBalance(EBudgetCategory Category) const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Economy")
	void SetResourceAmount(EStrategicResource Resource, float Amount);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Economy")
	float GetResourceAmount(EStrategicResource Resource) const;

	// 0 = no financial pressure, 1 = severe. Fleet/Readiness systems can scale
	// maintenance quality and construction speed down as this rises.
	UFUNCTION(BlueprintPure, Category="BlackOcean|Economy")
	float GetFinancialPressure() const;

private:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Economy")
	float AnnualBudget = 10000.0f;

	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Economy")
	float TotalAllocated = 0.0f;

	TMap<EBudgetCategory, float> CategoryBalances;
	TMap<EStrategicResource, float> Resources;
};
