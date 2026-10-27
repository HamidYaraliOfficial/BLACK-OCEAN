#include "ReplayRecorderSubsystem.h"

void UReplayRecorderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UReplayRecorderSubsystem::BeginRecording(FName MissionId)
{
	CurrentMissionId = MissionId;
	EventLog.Reset();
	bIsRecording = true;
}

void UReplayRecorderSubsystem::RecordEvent(const FReplayEvent& Event)
{
	if (bIsRecording)
	{
		EventLog.Add(Event);
	}
}

TArray<FReplayEvent> UReplayRecorderSubsystem::StopAndGetRecording()
{
	bIsRecording = false;
	return EventLog;
}
