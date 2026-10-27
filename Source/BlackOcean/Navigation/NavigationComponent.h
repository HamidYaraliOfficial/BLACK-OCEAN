#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackOceanTypes.h"
#include "NavigationComponent.generated.h"

USTRUCT(BlueprintType)
struct FRoutePlan
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Navigation")
	TArray<FMaritimeCoordinates> Waypoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Navigation")
	TArray<FName> RestrictedZonesToAvoid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Navigation")
	int32 CurrentWaypointIndex = 0;
};

// Route planning + waypoint following for a single vessel. Restricted/safe
// zone checks and weather-hazard avoidance are evaluated by higher-level
// systems (Ocean, Diplomacy) and passed in as the zones-to-avoid list.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UNavigationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNavigationComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Navigation")
	FRoutePlan ActivePlan;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Navigation")
	void SetRoute(const FRoutePlan& NewPlan);

	// Advances along the route at the given speed; returns true once the
	// final waypoint has been reached.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Navigation")
	bool AdvanceAlongRoute(float SpeedKnots, float DeltaMinutes, FMaritimeCoordinates& OutNewPosition);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Navigation")
	bool HasActiveRoute() const { return ActivePlan.Waypoints.Num() > 0 && ActivePlan.CurrentWaypointIndex < ActivePlan.Waypoints.Num(); }
};
