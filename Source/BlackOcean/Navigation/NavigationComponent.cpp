#include "NavigationComponent.h"

UNavigationComponent::UNavigationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNavigationComponent::SetRoute(const FRoutePlan& NewPlan)
{
	ActivePlan = NewPlan;
	ActivePlan.CurrentWaypointIndex = 0;
}

bool UNavigationComponent::AdvanceAlongRoute(float SpeedKnots, float DeltaMinutes, FMaritimeCoordinates& OutNewPosition)
{
	if (!HasActiveRoute())
	{
		return true;
	}

	const FMaritimeCoordinates& CurrentTarget = ActivePlan.Waypoints[ActivePlan.CurrentWaypointIndex];

	// 1 knot = 1 nautical mile/hour; grid units are treated as nautical miles.
	const double DistanceThisTick = (SpeedKnots * DeltaMinutes) / 60.0;

	const double DX = CurrentTarget.GridX - OutNewPosition.GridX;
	const double DY = CurrentTarget.GridY - OutNewPosition.GridY;
	const double RemainingDistance = FMath::Sqrt(DX * DX + DY * DY);

	if (RemainingDistance <= DistanceThisTick || RemainingDistance < KINDA_SMALL_NUMBER)
	{
		OutNewPosition = CurrentTarget;
		ActivePlan.CurrentWaypointIndex++;
		return !HasActiveRoute();
	}

	const double Ratio = DistanceThisTick / RemainingDistance;
	OutNewPosition.GridX += DX * Ratio;
	OutNewPosition.GridY += DY * Ratio;
	return false;
}
