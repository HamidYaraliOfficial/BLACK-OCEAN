#include "EconomySubsystem.h"

void UEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UEconomySubsystem::SetAnnualBudget(float TotalBudget)
{
	AnnualBudget = FMath::Max(0.0f, TotalBudget);
}

bool UEconomySubsystem::AllocateBudget(EBudgetCategory Category, float Amount)
{
	if (Amount < 0.0f || (TotalAllocated + Amount) > AnnualBudget)
	{
		return false;
	}
	float& Balance = CategoryBalances.FindOrAdd(Category, 0.0f);
	Balance += Amount;
	TotalAllocated += Amount;
	return true;
}

bool UEconomySubsystem::SpendFromCategory(EBudgetCategory Category, float Amount)
{
	float* Balance = CategoryBalances.Find(Category);
	if (!Balance || *Balance < Amount)
	{
		return false;
	}
	*Balance -= Amount;
	return true;
}

float UEconomySubsystem::GetCategoryBalance(EBudgetCategory Category) const
{
	const float* Balance = CategoryBalances.Find(Category);
	return Balance ? *Balance : 0.0f;
}

void UEconomySubsystem::SetResourceAmount(EStrategicResource Resource, float Amount)
{
	Resources.Add(Resource, FMath::Max(0.0f, Amount));
}

float UEconomySubsystem::GetResourceAmount(EStrategicResource Resource) const
{
	const float* Amount = Resources.Find(Resource);
	return Amount ? *Amount : 0.0f;
}

float UEconomySubsystem::GetFinancialPressure() const
{
	if (AnnualBudget <= 0.0f)
	{
		return 1.0f;
	}
	const float EmergencyReserve = GetCategoryBalance(EBudgetCategory::EmergencyReserve);
	const float ReserveRatio = FMath::Clamp(EmergencyReserve / FMath::Max(1.0f, AnnualBudget * 0.1f), 0.0f, 1.0f);
	const float AllocationRatio = FMath::Clamp(TotalAllocated / AnnualBudget, 0.0f, 1.0f);
	return FMath::Clamp(AllocationRatio - ReserveRatio * 0.3f, 0.0f, 1.0f);
}
