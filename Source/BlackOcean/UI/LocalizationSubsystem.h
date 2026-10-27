#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackOceanTypes.h"
#include "LocalizationSubsystem.generated.h"

// Runtime language + text-flow-direction manager for English / Persian /
// Chinese. Persian resolves to RightToLeft; English and Chinese resolve to
// LeftToRight. UMG root widgets should read GetCurrentFlowDirection() and
// call SetFlowDirectionPreference so menus, panels, tables, reports,
// tooltips and dialogs mirror correctly for Persian.
UCLASS()
class ULocalizationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Localization")
	void SetLanguage(ELanguageCode NewLanguage);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Localization")
	ELanguageCode GetCurrentLanguage() const { return CurrentLanguage; }

	UFUNCTION(BlueprintPure, Category="BlackOcean|Localization")
	ETextFlowDirection GetCurrentFlowDirection() const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Localization")
	static FString GetCultureCode(ELanguageCode Language);

	// Loads a simple key->string table for the given language from
	// Content/Localization/<code>/Game.json. In a full build this would be
	// superseded by the UE5 Localization Dashboard's .locres pipeline; this
	// JSON path is provided for quick iteration and modding.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Localization")
	bool LoadStringTableFromJson(ELanguageCode Language, const FString& JsonFilePath);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Localization")
	FString GetString(const FString& Key) const;

	// Formats a number using the current language's grouping/decimal
	// convention (kept minimal here; hook into ICU-backed FText::AsNumber
	// in a full build for locale-correct grouping).
	UFUNCTION(BlueprintPure, Category="BlackOcean|Localization")
	FString FormatNumber(float Value) const;

private:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Localization")
	ELanguageCode CurrentLanguage = ELanguageCode::English;

	TMap<ELanguageCode, TMap<FString, FString>> StringTables;
};
