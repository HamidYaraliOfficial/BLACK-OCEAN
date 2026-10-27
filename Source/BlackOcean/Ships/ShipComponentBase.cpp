#include "ShipComponentBase.h"

UShipComponentBase::UShipComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShipComponentBase::ApplyDamage(float DamageAmount)
{
	ConditionPercent = FMath::Clamp(ConditionPercent - DamageAmount, 0.0f, 1.0f);
}

void UShipComponentBase::ApplyRepair(float RepairAmount)
{
	if (bIsIsolated)
	{
		return; // Isolated systems must be un-isolated by a repair team first.
	}
	ConditionPercent = FMath::Clamp(ConditionPercent + RepairAmount, 0.0f, 1.0f);
}

float UShipComponentBase::GetEfficiencyMultiplier() const
{
	if (!IsOperational())
	{
		return 0.0f;
	}
	// Quadratic falloff: a system at 50% condition performs at ~25% efficiency.
	return ConditionPercent * ConditionPercent;
}
