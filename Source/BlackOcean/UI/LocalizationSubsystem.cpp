#include "LocalizationSubsystem.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Internationalization/Internationalization.h"

void ULocalizationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void ULocalizationSubsystem::SetLanguage(ELanguageCode NewLanguage)
{
	CurrentLanguage = NewLanguage;
	FInternationalization::Get().SetCurrentCulture(GetCultureCode(NewLanguage));
}

ETextFlowDirection ULocalizationSubsystem::GetCurrentFlowDirection() const
{
	return (CurrentLanguage == ELanguageCode::Persian) ? ETextFlowDirection::RightToLeft : ETextFlowDirection::LeftToRight;
}

FString ULocalizationSubsystem::GetCultureCode(ELanguageCode Language)
{
	switch (Language)
	{
		case ELanguageCode::Persian: return TEXT("fa");
		case ELanguageCode::Chinese: return TEXT("zh-Hans");
		case ELanguageCode::English:
		default: return TEXT("en");
	}
}

bool ULocalizationSubsystem::LoadStringTableFromJson(ELanguageCode Language, const FString& JsonFilePath)
{
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *JsonFilePath))
	{
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		return false;
	}

	TMap<FString, FString> Table;
	for (const auto& Pair : JsonObject->Values)
	{
		FString StringValue;
		if (Pair.Value->TryGetString(StringValue))
		{
			Table.Add(Pair.Key, StringValue);
		}
	}

	StringTables.Add(Language, Table);
	return true;
}

FString ULocalizationSubsystem::GetString(const FString& Key) const
{
	if (const TMap<FString, FString>* Table = StringTables.Find(CurrentLanguage))
	{
		if (const FString* Value = Table->Find(Key))
		{
			return *Value;
		}
	}
	// Fall back to English, then to the raw key, so missing translations
	// never render as a blank widget (surfaced instead by the Content
	// Validation Tool as a missing-localization warning before shipping).
	if (CurrentLanguage != ELanguageCode::English)
	{
		if (const TMap<FString, FString>* EnglishTable = StringTables.Find(ELanguageCode::English))
		{
			if (const FString* Value = EnglishTable->Find(Key))
			{
				return *Value;
			}
		}
	}
	return Key;
}

FString ULocalizationSubsystem::FormatNumber(float Value) const
{
	// Persian/Chinese locales conventionally still use Latin digits for
	// gameplay HUD numbers in most naval-sim UIs; grouping separator is kept
	// consistent. Swap to FText::AsNumber(Value, ..., Culture) for full ICU
	// locale-correct digit shaping if the design later calls for it.
	return FString::Printf(TEXT("%.1f"), Value);
}
