#include "ShipDamageComponent.h"

UShipDamageComponent::UShipDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShipDamageComponent::ReportDamageEvent(EDamageEventType EventType, float InitialSeverity)
{
	FActiveDamageEvent NewEvent;
	NewEvent.EventType = EventType;
	NewEvent.Severity = FMath::Clamp(InitialSeverity, 0.0f, 1.0f);
	ActiveEvents.Add(NewEvent);
}

bool UShipDamageComponent::AssignRepairTeam(int32 EventIndex, FName RepairTeamId)
{
	if (!ActiveEvents.IsValidIndex(EventIndex))
	{
		return false;
	}
	ActiveEvents[EventIndex].AssignedRepairTeamId = RepairTeamId;
	ActiveEvents[EventIndex].bIsContained = true;
	return true;
}

void UShipDamageComponent::TickDamage(float DeltaMinutes)
{
	const float Scale = DeltaMinutes / 10.0f;

	for (int32 i = ActiveEvents.Num() - 1; i >= 0; --i)
	{
		FActiveDamageEvent& Event = ActiveEvents[i];

		if (Event.bIsContained && !Event.AssignedRepairTeamId.IsNone())
		{
			Event.Severity = FMath::Clamp(Event.Severity - 0.05f * Scale, 0.0f, 1.0f);
			if (Event.Severity <= 0.0f)
			{
				ActiveEvents.RemoveAt(i);
			}
		}
		else
		{
			// Uncontained casualties worsen; flooding and fire spread fastest.
			const float SpreadRate =
				(Event.EventType == EDamageEventType::Flooding || Event.EventType == EDamageEventType::Fire)
				? 0.08f : 0.03f;
			Event.Severity = FMath::Clamp(Event.Severity + SpreadRate * Scale, 0.0f, 1.0f);
		}
	}
}

bool UShipDamageComponent::HasCriticalFlooding() const
{
	for (const FActiveDamageEvent& Event : ActiveEvents)
	{
		if (Event.EventType == EDamageEventType::Flooding && Event.Severity > 0.75f)
		{
			return true;
		}
	}
	return false;
}
