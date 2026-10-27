#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipDamageComponent.generated.h"

UENUM(BlueprintType)
enum class EDamageEventType : uint8
{
	Flooding, Fire, PowerFailure, EngineFailure, SensorDamage,
	CommunicationFailure, MobilityReduction, SystemDegradation
};

USTRUCT(BlueprintType)
struct FActiveDamageEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Damage")
	EDamageEventType EventType = EDamageEventType::SystemDegradation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Damage")
	float Severity = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Damage")
	bool bIsContained = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Damage")
	FName AssignedRepairTeamId;
};

// Coordinates active casualties (flooding/fire/etc) on a ship: spreading
// severity while uncontained, and resolving as repair teams are assigned.
// Pairs with UShipComponentBase for per-system condition.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UShipDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShipDamageComponent();

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Damage")
	void ReportDamageEvent(EDamageEventType EventType, float InitialSeverity);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Damage")
	bool AssignRepairTeam(int32 EventIndex, FName RepairTeamId);

	// Called each simulation tick: uncontained events (e.g. flooding, fire)
	// worsen over time; contained events with a repair team steadily heal.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Damage")
	void TickDamage(float DeltaMinutes);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Damage")
	const TArray<FActiveDamageEvent>& GetActiveEvents() const { return ActiveEvents; }

	UFUNCTION(BlueprintPure, Category="BlackOcean|Damage")
	bool HasCriticalFlooding() const;

private:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Damage")
	TArray<FActiveDamageEvent> ActiveEvents;
};
