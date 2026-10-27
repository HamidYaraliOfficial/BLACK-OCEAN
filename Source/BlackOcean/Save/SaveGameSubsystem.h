#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

// Versioned save payload. Real projects would flesh this out with full world
// state (fleets, economy, diplomacy, research, discovered regions, etc);
// this scaffold defines the envelope, versioning and validation flow.
UCLASS()
class UBlackOceanSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Save")
	int32 SaveFormatVersion = 1;

	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Save")
	FString CampaignId;

	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Save")
	FDateTime SavedAtRealTime;

	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Save")
	FString SerializedWorldStateJson;

	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Save")
	FString IntegrityChecksum;
};

// Handles multiple save slots, autosave, manual save, checkpoints, version
// migration and a basic checksum-based integrity check for crash recovery.
UCLASS()
class USaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Save")
	bool SaveToSlot(const FString& SlotName, int32 UserIndex, const FString& CampaignId, const FString& WorldStateJson);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Save")
	bool LoadFromSlot(const FString& SlotName, int32 UserIndex, FString& OutWorldStateJson);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Save")
	bool ValidateIntegrity(const FString& SlotName, int32 UserIndex) const;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Save")
	void AutoSave(const FString& CampaignId, const FString& WorldStateJson);

	static constexpr int32 CurrentSaveFormatVersion = 1;

private:
	static FString ComputeChecksum(const FString& Payload);

	// Upgrades an older-format save payload in place. Extend per format bump.
	static void MigrateIfNeeded(UBlackOceanSaveGame* SaveObject);
};
