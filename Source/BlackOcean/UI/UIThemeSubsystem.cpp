#include "UIThemeSubsystem.h"

void UUIThemeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	BuildDefaultPalettes();
}

void UUIThemeSubsystem::BuildDefaultPalettes()
{
	// Windows 11-inspired default: soft rounded dark surface with a Windows
	// accent blue - the palette every other theme is compared against.
	FUIThemePalette Win11;
	Win11.BackgroundPrimary = FLinearColor(0.086f, 0.086f, 0.086f, 1.0f);
	Win11.BackgroundSecondary = FLinearColor(0.14f, 0.14f, 0.14f, 1.0f);
	Win11.AccentPrimary = FLinearColor(0.0f, 0.47f, 0.84f, 1.0f);
	Win11.TextPrimary = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Palettes.Add(EUITheme::Windows11Default, Win11);

	FUIThemePalette DarkNavy;
	DarkNavy.BackgroundPrimary = FLinearColor(0.03f, 0.06f, 0.11f, 1.0f);
	DarkNavy.BackgroundSecondary = FLinearColor(0.05f, 0.10f, 0.17f, 1.0f);
	DarkNavy.AccentPrimary = FLinearColor(0.15f, 0.55f, 0.95f, 1.0f);
	DarkNavy.TextPrimary = FLinearColor(0.90f, 0.94f, 1.0f, 1.0f);
	Palettes.Add(EUITheme::DarkNavy, DarkNavy);

	FUIThemePalette Light;
	Light.BackgroundPrimary = FLinearColor(0.96f, 0.97f, 0.98f, 1.0f);
	Light.BackgroundSecondary = FLinearColor(0.90f, 0.91f, 0.93f, 1.0f);
	Light.AccentPrimary = FLinearColor(0.0f, 0.40f, 0.75f, 1.0f);
	Light.TextPrimary = FLinearColor(0.05f, 0.06f, 0.07f, 1.0f);
	Light.TextSecondary = FLinearColor(0.35f, 0.37f, 0.40f, 1.0f);
	Light.BorderColor = FLinearColor(0.80f, 0.81f, 0.83f, 1.0f);
	Palettes.Add(EUITheme::Light, Light);

	FUIThemePalette OceanBlueCyan;
	OceanBlueCyan.BackgroundPrimary = FLinearColor(0.02f, 0.10f, 0.14f, 1.0f);
	OceanBlueCyan.BackgroundSecondary = FLinearColor(0.03f, 0.15f, 0.20f, 1.0f);
	OceanBlueCyan.AccentPrimary = FLinearColor(0.0f, 0.85f, 0.90f, 1.0f);
	OceanBlueCyan.TextPrimary = FLinearColor(0.88f, 0.98f, 1.0f, 1.0f);
	Palettes.Add(EUITheme::OceanBlueCyan, OceanBlueCyan);

	FUIThemePalette RedAlert;
	RedAlert.BackgroundPrimary = FLinearColor(0.08f, 0.02f, 0.02f, 1.0f);
	RedAlert.BackgroundSecondary = FLinearColor(0.14f, 0.03f, 0.03f, 1.0f);
	RedAlert.AccentPrimary = FLinearColor(0.90f, 0.12f, 0.12f, 1.0f);
	RedAlert.AccentAlert = FLinearColor(1.0f, 0.75f, 0.0f, 1.0f);
	RedAlert.TextPrimary = FLinearColor(1.0f, 0.92f, 0.92f, 1.0f);
	Palettes.Add(EUITheme::RedAlert, RedAlert);

	FUIThemePalette HighContrast;
	HighContrast.BackgroundPrimary = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	HighContrast.BackgroundSecondary = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	HighContrast.AccentPrimary = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
	HighContrast.AccentAlert = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
	HighContrast.TextPrimary = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	HighContrast.BorderColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Palettes.Add(EUITheme::HighContrast, HighContrast);
}

void UUIThemeSubsystem::SetTheme(EUITheme NewTheme)
{
	CurrentTheme = NewTheme;
}

FUIThemePalette UUIThemeSubsystem::GetCurrentPalette() const
{
	if (const FUIThemePalette* Found = Palettes.Find(CurrentTheme))
	{
		return *Found;
	}
	return FUIThemePalette();
}
