#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlackOceanTypes.h"
#include "BlackOceanGameInstance.generated.h"

// Central access point for cross-level persistent state (active campaign id,
// selected language/theme, difficulty). Heavy simulation lives in subsystems.
UCLASS()
class UBlackOceanGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Campaign")
	FString ActiveCampaignId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Settings")
	ELanguageCode CurrentLanguage = ELanguageCode::English;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Settings")
	EUITheme CurrentTheme = EUITheme::Windows11Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Settings")
	EDifficultyLevel CurrentDifficulty = EDifficultyLevel::Standard;
};
