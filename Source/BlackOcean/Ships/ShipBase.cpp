#include "ShipBase.h"
#include "ShipComponentBase.h"
#include "ShipDamageComponent.h"

AShipBase::AShipBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DamageComponent = CreateDefaultSubobject<UShipDamageComponent>(TEXT("DamageComponent"));

	// One component per independently-failable system, per the design spec.
	const EShipSystemType AllSystems[] = {
		EShipSystemType::Hull, EShipSystemType::Engine, EShipSystemType::PowerGeneration,
		EShipSystemType::Propulsion, EShipSystemType::Sensors, EShipSystemType::Communications,
		EShipSystemType::Navigation, EShipSystemType::FlightDeck, EShipSystemType::InternalSystems,
		EShipSystemType::Cooling, EShipSystemType::CargoCompartments, EShipSystemType::MissionModules
	};

	for (EShipSystemType SystemType : AllSystems)
	{
		const FName ComponentName = *FString::Printf(TEXT("System_%d"), static_cast<int32>(SystemType));
		UShipComponentBase* NewSystem = CreateDefaultSubobject<UShipComponentBase>(ComponentName);
		NewSystem->SystemType = SystemType;
		ShipSystems.Add(NewSystem);
	}
}

void AShipBase::BeginPlay()
{
	Super::BeginPlay();
}

UShipComponentBase* AShipBase::GetSystem(EShipSystemType SystemType) const
{
	for (UShipComponentBase* System : ShipSystems)
	{
		if (System && System->SystemType == SystemType)
		{
			return System;
		}
	}
	return nullptr;
}

void AShipBase::ConsumeFuel(float PercentToConsume)
{
	FuelPercent = FMath::Clamp(FuelPercent - PercentToConsume, 0.0f, 1.0f);
}

void AShipBase::RecordMissionResult(FName MissionId, const FGameTimestamp& CompletedAt, const FString& Outcome)
{
	FShipMissionRecord Record;
	Record.MissionId = MissionId;
	Record.CompletedAt = CompletedAt;
	Record.Outcome = Outcome;
	MissionHistory.Add(Record);
}

float AShipBase::GetOverallReadiness() const
{
	float SystemAverage = 0.0f;
	int32 Count = 0;
	for (const UShipComponentBase* System : ShipSystems)
	{
		if (System)
		{
			SystemAverage += System->GetEfficiencyMultiplier();
			++Count;
		}
	}
	SystemAverage = (Count > 0) ? (SystemAverage / Count) : 0.0f;

	// Weighted blend: crew and fuel matter most for whether a ship can sail
	// at all; maintenance/equipment/systems matter for how well it performs.
	return FMath::Clamp(
		CrewReadinessPercent * 0.30f +
		FuelPercent * 0.15f +
		MaintenanceLevelPercent * 0.20f +
		EquipmentConditionPercent * 0.15f +
		SystemAverage * 0.20f,
		0.0f, 1.0f);
}
