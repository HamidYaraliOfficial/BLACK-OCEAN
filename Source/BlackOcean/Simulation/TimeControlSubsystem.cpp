#include "TimeControlSubsystem.h"

void UTimeControlSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentTimestamp = FGameTimestamp();
	CurrentSpeed = ESimulationSpeed::Speed1x;
}

void UTimeControlSubsystem::SetSpeed(ESimulationSpeed NewSpeed)
{
	CurrentSpeed = NewSpeed;
}

void UTimeControlSubsystem::TogglePause()
{
	CurrentSpeed = (CurrentSpeed == ESimulationSpeed::Paused) ? ESimulationSpeed::Speed1x : ESimulationSpeed::Paused;
}

float UTimeControlSubsystem::GetSpeedMultiplier() const
{
	switch (CurrentSpeed)
	{
		case ESimulationSpeed::Paused:  return 0.0f;
		case ESimulationSpeed::Speed1x:  return 1.0f;
		case ESimulationSpeed::Speed2x:  return 2.0f;
		case ESimulationSpeed::Speed5x:  return 5.0f;
		case ESimulationSpeed::Speed10x: return 10.0f;
		case ESimulationSpeed::Speed25x: return 25.0f;
		default: return 1.0f;
	}
}

void UTimeControlSubsystem::AdvanceClock(float RealDeltaSeconds)
{
	const float Multiplier = GetSpeedMultiplier();
	if (Multiplier <= 0.0f)
	{
		return;
	}

	FractionalMinuteAccumulator += RealDeltaSeconds * MinutesPerRealSecondAt1x * Multiplier;

	while (FractionalMinuteAccumulator >= 1.0f)
	{
		FractionalMinuteAccumulator -= 1.0f;
		CurrentTimestamp.MinuteOfDay += 1;
		if (CurrentTimestamp.MinuteOfDay >= 1440)
		{
			CurrentTimestamp.MinuteOfDay = 0;
			CurrentTimestamp.CampaignDay += 1;
		}
	}
}
