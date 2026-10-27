#include "ResearchTreeSubsystem.h"

void UResearchTreeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UResearchTreeSubsystem::RegisterNode(const FResearchNode& Node)
{
	Nodes.Add(Node.NodeId, Node);
}

bool UResearchTreeSubsystem::ArePrerequisitesMet(FName NodeId) const
{
	const FResearchNode* Node = Nodes.Find(NodeId);
	if (!Node)
	{
		return false;
	}
	for (FName PrereqId : Node->Prerequisites)
	{
		const FResearchNode* Prereq = Nodes.Find(PrereqId);
		if (!Prereq || !Prereq->bIsCompleted)
		{
			return false;
		}
	}
	return true;
}

bool UResearchTreeSubsystem::StartOrContinueResearch(FName NodeId, int32 DaysToApply, int32 AvailableResearchCapacityDays)
{
	FResearchNode* Node = Nodes.Find(NodeId);
	if (!Node || Node->bIsCompleted || !ArePrerequisitesMet(NodeId))
	{
		return false;
	}

	const int32 DaysApplied = FMath::Min(DaysToApply, AvailableResearchCapacityDays);
	Node->DaysInvested += DaysApplied;

	if (Node->DaysInvested >= Node->TimeDaysRequired)
	{
		Node->bIsCompleted = true;
	}
	return true;
}

bool UResearchTreeSubsystem::IsCompleted(FName NodeId) const
{
	const FResearchNode* Node = Nodes.Find(NodeId);
	return Node && Node->bIsCompleted;
}
