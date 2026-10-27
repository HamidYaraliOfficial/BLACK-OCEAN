#include "AirAssetBase.h"

AAirAssetBase::AAirAssetBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AAirAssetBase::LaunchFrom(FName ShipId)
{
	if (FuelOrBatteryPercent < 0.1f)
	{
		return false;
	}
	HostShipId = ShipId;
	return true;
}

void AAirAssetBase::AssignMission(EAirMissionType MissionType)
{
	AssignedMission = MissionType;
}

void AAirAssetBase::TickFlight(float DeltaMinutes)
{
	const float Scale = DeltaMinutes / 60.0f;
	const float ConsumptionRate = (AssetType == EAirAssetType::ReconDrone) ? 0.15f : 0.25f;
	FuelOrBatteryPercent = FMath::Clamp(FuelOrBatteryPercent - ConsumptionRate * Scale, 0.0f, 1.0f);
}
