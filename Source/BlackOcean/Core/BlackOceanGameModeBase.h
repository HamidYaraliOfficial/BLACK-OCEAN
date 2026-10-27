#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlackOceanGameModeBase.generated.h"

UCLASS()
class ABlackOceanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABlackOceanGameModeBase();

protected:
	virtual void BeginPlay() override;
};
