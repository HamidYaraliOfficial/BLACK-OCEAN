#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SupplyChainSubsystem.generated.h"

UENUM(BlueprintType)
enum class ESupplyResourceType : uint8
{
	FuelEnergy, SpareParts, Food, MedicalSupplies, AmmunitionEquivalent, Components, MaintenanceMaterials
};

USTRUCT(BlueprintType)
struct FSupplyRoute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics")
	FName RouteId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics")
	FName OriginPortId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics")
	FName DestinationBaseId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics")
	float CapacityUnitsPerDay = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics")
	float DistanceKm = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics", meta=(ClampMin="0.0", ClampMax="1.0"))
	float CongestionLevel = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics", meta=(ClampMin="0.0", ClampMax="1.0"))
	float WeatherRiskLevel = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Logistics")
	bool bIsInterrupted = false;

	float GetEffectiveThroughput() const
	{
		if (bIsInterrupted)
		{
			return 0.0f;
		}
		const float Efficiency = FMath::Clamp(1.0f - CongestionLevel - (WeatherRiskLevel * 0.5f), 0.0f, 1.0f);
		return CapacityUnitsPerDay * Efficiency;
	}
};

// Moves Fuel/Spare Parts/Food/Medical/Ammunition-equivalent/Components/
// Maintenance resources from Ports to Fleet Bases along modeled routes.
// Interruptions here are what the Fleet Readiness Model reads to degrade
// ship readiness over time.
UCLASS()
class USupplyChainSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Logistics")
	void RegisterRoute(const FSupplyRoute& Route);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Logistics")
	void SetRouteInterrupted(FName RouteId, bool bInterrupted);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Logistics")
	void StockResource(FName BaseId, ESupplyResourceType ResourceType, float Amount);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Logistics")
	bool ConsumeResource(FName BaseId, ESupplyResourceType ResourceType, float Amount);

	// Moves throughput from each route's origin stock into its destination
	// stock for one simulated day. Call once per campaign day.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Logistics")
	void TickDailySupplyRun();

	UFUNCTION(BlueprintPure, Category="BlackOcean|Logistics")
	float GetStockLevel(FName BaseId, ESupplyResourceType ResourceType) const;

private:
	UPROPERTY()
	TMap<FName, FSupplyRoute> Routes;

	// Key = BaseId_ResourceTypeIndex
	TMap<FString, float> Stockpiles;

	static FString MakeStockKey(FName BaseId, ESupplyResourceType ResourceType);
};
