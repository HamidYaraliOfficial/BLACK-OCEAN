// BLACK OCEAN - Shared Core Types
// All nations, vessels, sensors and organizations described here are entirely fictional
// and are modeled purely for gameplay/simulation purposes.
#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.generated.h"

UENUM(BlueprintType)
enum class EMaritimeRegionType : uint8
{
	OpenSea, DeepOcean, ShallowWaters, Archipelago, Strait, Bay, Island,
	Reef, Harbor, Port, NavalBase, OffshorePlatform, ShippingLane,
	ResearchZone, StormRegion, UnknownRegion
};

UENUM(BlueprintType)
enum class EContactClassification : uint8
{
	Unknown, Civilian, Friendly, Neutral, Suspicious, Hostile
};

UENUM(BlueprintType)
enum class EShipClass : uint8
{
	CommandShip, FrigateLike, DestroyerLike, CruiserLike, CarrierLikePlatform,
	Submarine, Corvette, PatrolCraft, AmphibiousSupport, LogisticsShip,
	ResearchVessel, RescueVessel, DroneCarrier
};

UENUM(BlueprintType)
enum class EShipSystemType : uint8
{
	Hull, Engine, PowerGeneration, Propulsion, Sensors, Communications,
	Navigation, FlightDeck, InternalSystems, Cooling, CargoCompartments,
	MissionModules
};

UENUM(BlueprintType)
enum class ECrewRole : uint8
{
	Captain, Engineer, Navigator, SensorOperator, CommunicationsOfficer,
	FlightCrew, SupportTeam
};

UENUM(BlueprintType)
enum class ECommandOrderType : uint8
{
	Move, Patrol, Escort, Recon, Search, Rescue, Rendezvous, HoldPosition,
	ReturnToPort, Support, Supply, MissionSpecific
};

UENUM(BlueprintType)
enum class EWeatherState : uint8
{
	Clear, Overcast, Rain, Storm, Fog, HeavySeas
};

UENUM(BlueprintType)
enum class EUITheme : uint8
{
	Windows11Default, DarkNavy, Light, OceanBlueCyan, RedAlert, HighContrast
};

UENUM(BlueprintType)
enum class ELanguageCode : uint8
{
	English, Persian, Chinese
};

UENUM(BlueprintType)
enum class ETextFlowDirection : uint8
{
	LeftToRight, RightToLeft
};

UENUM(BlueprintType)
enum class ESimulationSpeed : uint8
{
	Paused, Speed1x, Speed2x, Speed5x, Speed10x, Speed25x
};

UENUM(BlueprintType)
enum class EDifficultyLevel : uint8
{
	Casual, Standard, Veteran, Extreme, Custom
};

USTRUCT(BlueprintType)
struct FMaritimeCoordinates
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean")
	double GridX = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean")
	double GridY = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean")
	double DepthMeters = 0.0;
};

USTRUCT(BlueprintType)
struct FGameTimestamp
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean")
	int32 CampaignDay = 0;

	// Minutes since campaign-day start (0-1439), used by port hours / forecasts / logistics.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean")
	int32 MinuteOfDay = 0;

	double ToAbsoluteMinutes() const { return static_cast<double>(CampaignDay) * 1440.0 + MinuteOfDay; }
};
