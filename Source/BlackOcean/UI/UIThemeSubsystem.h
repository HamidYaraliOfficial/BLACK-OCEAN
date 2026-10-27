#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackOceanTypes.h"
#include "UIThemeSubsystem.generated.h"

// Color palette for one UI theme. Widgets bind to UUIThemeSubsystem rather
// than hard-coding colors, so switching themes at runtime (Settings menu)
// updates every open widget consistently.
USTRUCT(BlueprintType)
struct FUIThemePalette
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI")
	FLinearColor BackgroundPrimary = FLinearColor(0.06f, 0.08f, 0.11f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI")
	FLinearColor BackgroundSecondary = FLinearColor(0.10f, 0.13f, 0.17f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI")
	FLinearColor AccentPrimary = FLinearColor(0.10f, 0.55f, 0.85f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI")
	FLinearColor AccentAlert = FLinearColor(0.85f, 0.15f, 0.15f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI")
	FLinearColor TextPrimary = FLinearColor(0.92f, 0.94f, 0.96f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI")
	FLinearColor TextSecondary = FLinearColor(0.65f, 0.68f, 0.72f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI")
	FLinearColor BorderColor = FLinearColor(0.22f, 0.25f, 0.29f, 1.0f);
};

// Central runtime theme manager: Windows 11-inspired default, Dark Navy,
// Light, Ocean Blue/Cyan, Red Alert and High Contrast. Also exposes
// Accessibility-relevant scalars (font scale, reduced motion, UI scale).
UCLASS()
class UUIThemeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|UI")
	void SetTheme(EUITheme NewTheme);

	UFUNCTION(BlueprintPure, Category="BlackOcean|UI")
	EUITheme GetCurrentTheme() const { return CurrentTheme; }

	UFUNCTION(BlueprintPure, Category="BlackOcean|UI")
	FUIThemePalette GetCurrentPalette() const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|UI")
	void SetFontScale(float NewScale) { FontScale = FMath::Clamp(NewScale, 0.75f, 2.0f); }

	UFUNCTION(BlueprintPure, Category="BlackOcean|UI")
	float GetFontScale() const { return FontScale; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI|Accessibility")
	bool bColorblindMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|UI|Accessibility")
	bool bReducedMotion = false;

private:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|UI")
	EUITheme CurrentTheme = EUITheme::Windows11Default;

	UPROPERTY(VisibleAnywhere, Category="BlackOcean|UI")
	float FontScale = 1.0f;

	TMap<EUITheme, FUIThemePalette> Palettes;
	void BuildDefaultPalettes();
};
