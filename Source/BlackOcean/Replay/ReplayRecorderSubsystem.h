#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackOceanTypes.h"
#include "ReplayRecorderSubsystem.generated.h"

UENUM(BlueprintType)
enum class EReplayEventCategory : uint8
{
	Movement, SensorDetection, OrderIssued, ObjectiveChange, SupportEvent, DamageEvent
};

USTRUCT(BlueprintType)
struct FReplayEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Replay")
	FGameTimestamp Timestamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Replay")
	EReplayEventCategory Category = EReplayEventCategory::Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Replay")
	FName SubjectId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Replay")
	FString Details;
};

// Records a deterministic event stream for a mission/operation so it can be
// replayed exactly (relying on UTimeControlSubsystem's deterministic clock
// and seeded randomness) and consumed by the After Action Review screen.
UCLASS()
class UReplayRecorderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Replay")
	void BeginRecording(FName MissionId);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Replay")
	void RecordEvent(const FReplayEvent& Event);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Replay")
	TArray<FReplayEvent> StopAndGetRecording();

	UFUNCTION(BlueprintPure, Category="BlackOcean|Replay")
	bool IsRecording() const { return bIsRecording; }

private:
	bool bIsRecording = false;
	FName CurrentMissionId;
	TArray<FReplayEvent> EventLog;
};
