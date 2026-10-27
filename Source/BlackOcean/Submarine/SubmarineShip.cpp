#include "SubmarineShip.h"

ASubmarineShip::ASubmarineShip()
{
	ClassDefinition.ShipClass = EShipClass::Submarine;
}

bool ASubmarineShip::RequestDive(float TargetDepthMeters)
{
	if (TargetDepthMeters < 0.0f || TargetDepthMeters > MaxDepthMeters)
	{
		return false;
	}
	if (HullIntegrityPercent < 0.2f && TargetDepthMeters > CurrentDepthMeters)
	{
		return false; // Too damaged to safely dive deeper.
	}
	CurrentDepthMeters = TargetDepthMeters;
	CurrentMode = (TargetDepthMeters <= 0.0f) ? ESubmarineMode::Surfaced
		: (TargetDepthMeters < 20.0f) ? ESubmarineMode::PeriscopeDepth
		: ESubmarineMode::DeepDive;
	return true;
}

void ASubmarineShip::SetMode(ESubmarineMode NewMode)
{
	CurrentMode = NewMode;
	NoiseSignature = (NewMode == ESubmarineMode::SilentTravel) ? 0.15f
		: (NewMode == ESubmarineMode::Surfaced) ? 0.7f : 0.4f;
}

void ASubmarineShip::TickLifeSupport(float DeltaMinutes)
{
	const float Scale = DeltaMinutes / 60.0f;

	if (CurrentMode != ESubmarineMode::Surfaced)
	{
		const float BatteryDrain = (CurrentMode == ESubmarineMode::SilentTravel) ? 0.03f : 0.06f;
		BatteryPercent = FMath::Clamp(BatteryPercent - BatteryDrain * Scale, 0.0f, 1.0f);
		OxygenPercent = FMath::Clamp(OxygenPercent - 0.02f * Scale, 0.0f, 1.0f);
	}
	else
	{
		// Surfaced: recharge batteries and replenish oxygen.
		BatteryPercent = FMath::Clamp(BatteryPercent + 0.10f * Scale, 0.0f, 1.0f);
		OxygenPercent = FMath::Clamp(OxygenPercent + 0.10f * Scale, 0.0f, 1.0f);
	}
}

bool ASubmarineShip::IsInDistress() const
{
	return OxygenPercent < 0.15f || BatteryPercent < 0.05f || HullIntegrityPercent < 0.1f;
}
