#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "PortOperatingHours.generated.h"

// One open/close window within a campaign day, in minutes-of-day (0-1439).
// A port can have several windows (e.g. split shifts); player-configurable
// via the Port Management Dashboard.
USTRUCT(BlueprintType)
struct FOperatingWindow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port", meta=(ClampMin="0", ClampMax="1439"))
	int32 OpenMinuteOfDay = 360; // default 06:00

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port", meta=(ClampMin="0", ClampMax="1439"))
	int32 CloseMinuteOfDay = 1320; // default 22:00

	bool Contains(int32 MinuteOfDay) const
	{
		if (OpenMinuteOfDay <= CloseMinuteOfDay)
		{
			return MinuteOfDay >= OpenMinuteOfDay && MinuteOfDay < CloseMinuteOfDay;
		}
		// Window wraps past midnight (e.g. open 22:00, close 04:00).
		return MinuteOfDay >= OpenMinuteOfDay || MinuteOfDay < CloseMinuteOfDay;
	}
};

// Player-configurable operating schedule for a port, shipyard, repair dock or
// other facility. Lets the UI show "Open now / closes in Xh Ym" or
// "Closed - opens in Xh Ym" for whatever schedule the player has set up.
USTRUCT(BlueprintType)
struct FFacilityOperatingHours
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	TArray<FOperatingWindow> Windows;

	// If true, the facility is open 24 hours regardless of Windows.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Port")
	bool bOpen24Hours = false;

	bool IsOpenAt(int32 MinuteOfDay) const
	{
		if (bOpen24Hours)
		{
			return true;
		}
		for (const FOperatingWindow& Window : Windows)
		{
			if (Window.Contains(MinuteOfDay))
			{
				return true;
			}
		}
		return false;
	}

	// Minutes from Now until the facility's status next changes (opens if
	// currently closed, closes if currently open). Returns -1 if bOpen24Hours
	// or if no window is configured at all (treated as permanently closed).
	int32 GetMinutesUntilNextChange(const FGameTimestamp& Now) const
	{
		if (bOpen24Hours)
		{
			return -1;
		}
		if (Windows.Num() == 0)
		{
			return -1;
		}

		const bool bCurrentlyOpen = IsOpenAt(Now.MinuteOfDay);

		// Scan forward minute-by-minute up to 48h (campaign days are short,
		// this keeps the logic simple and fully deterministic for Replay).
		for (int32 Offset = 1; Offset <= 2880; ++Offset)
		{
			const int32 CheckMinute = (Now.MinuteOfDay + Offset) % 1440;
			const bool bOpenThen = IsOpenAt(CheckMinute);
			if (bOpenThen != bCurrentlyOpen)
			{
				return Offset;
			}
		}
		return -1;
	}
};
