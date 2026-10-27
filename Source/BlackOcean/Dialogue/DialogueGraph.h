#pragma once

#include "CoreMinimal.h"
#include "DialogueGraph.generated.h"

USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	FText ChoiceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	FName NextNodeId;

	// Simple condition keys (e.g. "MissionState.Completed", "Crew.Trust>0.5")
	// evaluated externally by the Dialogue Engine against current game state.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	TArray<FString> RequiredConditionKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	float RelationshipDelta = 0.0f;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	FName NodeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	FName SpeakerCharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	FText Line;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	TArray<FDialogueChoice> Choices;
};

USTRUCT(BlueprintType)
struct FDialogueGraph
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	FName GraphId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	FName StartNodeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Dialogue")
	TArray<FDialogueNode> Nodes;

	const FDialogueNode* FindNode(FName NodeId) const
	{
		return Nodes.FindByPredicate([NodeId](const FDialogueNode& N) { return N.NodeId == NodeId; });
	}
};
