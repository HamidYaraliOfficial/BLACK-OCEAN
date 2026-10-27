#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackOceanTypes.h"
#include "TimeControlSubsystem.generated.h"

// Deterministic campaign clock. All gameplay systems read time from here rather
// than from wall-clock/world time so that Replay and the Scenario Simulation
// Harness can reproduce runs exactly.
UCLASS()
class UTimeControlSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Time")
	void SetSpeed(ESimulationSpeed NewSpeed);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Time")
	void TogglePause();

	// Advances the deterministic clock by RealDeltaSeconds scaled by the
	// current speed multiplier. Call once per frame from a driver actor.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Time")
	void AdvanceClock(float RealDeltaSeconds);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Time")
	FGameTimestamp GetCurrentTimestamp() const { return CurrentTimestamp; }

	UFUNCTION(BlueprintPure, Category="BlackOcean|Time")
	float GetSpeedMultiplier() const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Time")
	ESimulationSpeed GetSpeed() const { return CurrentSpeed; }

private:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Time")
	FGameTimestamp CurrentTimestamp;

	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Time")
	ESimulationSpeed CurrentSpeed = ESimulationSpeed::Speed1x;

	// Minutes of campaign time simulated per real second at 1x.
	static constexpr float MinutesPerRealSecondAt1x = 1.0f;

	float FractionalMinuteAccumulator = 0.0f;
};
