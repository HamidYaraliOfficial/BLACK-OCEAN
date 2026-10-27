#include "SaveGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/SecureHash.h"

void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

FString USaveGameSubsystem::ComputeChecksum(const FString& Payload)
{
	return FMD5::HashAnsiString(*Payload);
}

void USaveGameSubsystem::MigrateIfNeeded(UBlackOceanSaveGame* SaveObject)
{
	if (!SaveObject)
	{
		return;
	}
	// Placeholder for future format migrations, e.g.:
	// if (SaveObject->SaveFormatVersion < 2) { ...upgrade fields...; SaveObject->SaveFormatVersion = 2; }
	SaveObject->SaveFormatVersion = FMath::Max(SaveObject->SaveFormatVersion, CurrentSaveFormatVersion);
}

bool USaveGameSubsystem::SaveToSlot(const FString& SlotName, int32 UserIndex, const FString& CampaignId, const FString& WorldStateJson)
{
	UBlackOceanSaveGame* SaveObject = Cast<UBlackOceanSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlackOceanSaveGame::StaticClass()));
	if (!SaveObject)
	{
		return false;
	}

	SaveObject->SaveFormatVersion = CurrentSaveFormatVersion;
	SaveObject->CampaignId = CampaignId;
	SaveObject->SavedAtRealTime = FDateTime::UtcNow();
	SaveObject->SerializedWorldStateJson = WorldStateJson;
	SaveObject->IntegrityChecksum = ComputeChecksum(WorldStateJson);

	return UGameplayStatics::SaveGameToSlot(SaveObject, SlotName, UserIndex);
}

bool USaveGameSubsystem::LoadFromSlot(const FString& SlotName, int32 UserIndex, FString& OutWorldStateJson)
{
	if (!UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		return false;
	}

	UBlackOceanSaveGame* SaveObject = Cast<UBlackOceanSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (!SaveObject)
	{
		return false;
	}

	if (ComputeChecksum(SaveObject->SerializedWorldStateJson) != SaveObject->IntegrityChecksum)
	{
		// Corrupted save - caller should fall back to the last known-good
		// autosave/checkpoint slot for crash recovery.
		return false;
	}

	MigrateIfNeeded(SaveObject);
	OutWorldStateJson = SaveObject->SerializedWorldStateJson;
	return true;
}

bool USaveGameSubsystem::ValidateIntegrity(const FString& SlotName, int32 UserIndex) const
{
	if (!UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		return false;
	}
	const UBlackOceanSaveGame* SaveObject = Cast<UBlackOceanSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	return SaveObject && ComputeChecksum(SaveObject->SerializedWorldStateJson) == SaveObject->IntegrityChecksum;
}

void USaveGameSubsystem::AutoSave(const FString& CampaignId, const FString& WorldStateJson)
{
	SaveToSlot(TEXT("AutoSave"), 0, CampaignId, WorldStateJson);
}
