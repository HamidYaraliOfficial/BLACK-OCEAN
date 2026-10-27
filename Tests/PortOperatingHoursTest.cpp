// BLACK OCEAN - Example Automation Test
// Run via Scripts/run-tests.ps1 (Automation RunTests BlackOcean).
#include "Misc/AutomationTest.h"
#include "PortOperatingHours.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlackOceanPortHoursTest, "BlackOcean.Ports.OperatingHours",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FBlackOceanPortHoursTest::RunTest(const FString& Parameters)
{
	FFacilityOperatingHours Hours;
	FOperatingWindow Window;
	Window.OpenMinuteOfDay = 360;  // 06:00
	Window.CloseMinuteOfDay = 1320; // 22:00
	Hours.Windows.Add(Window);

	FGameTimestamp DuringOpen;
	DuringOpen.MinuteOfDay = 600; // 10:00
	TestTrue(TEXT("Port should be open at 10:00 given 06:00-22:00 window"), Hours.IsOpenAt(DuringOpen.MinuteOfDay));

	FGameTimestamp BeforeOpen;
	BeforeOpen.MinuteOfDay = 200; // 03:20
	TestFalse(TEXT("Port should be closed at 03:20 given 06:00-22:00 window"), Hours.IsOpenAt(BeforeOpen.MinuteOfDay));

	const int32 MinutesUntilOpen = Hours.GetMinutesUntilNextChange(BeforeOpen);
	TestEqual(TEXT("Minutes until opening from 03:20 to 06:00 should be 160"), MinutesUntilOpen, 160);

	FFacilityOperatingHours AlwaysOpen;
	AlwaysOpen.bOpen24Hours = true;
	TestTrue(TEXT("24-hour facility should always report open"), AlwaysOpen.IsOpenAt(0));
	TestEqual(TEXT("24-hour facility has no 'next change'"), AlwaysOpen.GetMinutesUntilNextChange(BeforeOpen), -1);

	return true;
}
