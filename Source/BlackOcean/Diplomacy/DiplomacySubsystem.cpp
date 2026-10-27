#include "DiplomacySubsystem.h"

void UDiplomacySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDiplomacySubsystem::AdjustRelation(FName OtherFactionId, float Delta)
{
	FDiplomaticRelation& Relation = Relations.FindOrAdd(OtherFactionId);
	Relation.OtherFactionId = OtherFactionId;
	Relation.RelationScore = FMath::Clamp(Relation.RelationScore + Delta, -1.0f, 1.0f);
}

float UDiplomacySubsystem::GetMinimumRelationForTreaty(ETreatyType TreatyType)
{
	switch (TreatyType)
	{
		case ETreatyType::TradeAgreement:            return -0.2f;
		case ETreatyType::NavigationRights:           return -0.1f;
		case ETreatyType::SearchAndRescueAgreement:   return -0.3f;
		case ETreatyType::PortAccess:                 return 0.1f;
		case ETreatyType::IntelligenceSharing:        return 0.4f;
		case ETreatyType::ResearchCooperation:        return 0.5f;
		default: return 0.0f;
	}
}

bool UDiplomacySubsystem::ProposeTreaty(FName OtherFactionId, ETreatyType TreatyType)
{
	FDiplomaticRelation& Relation = Relations.FindOrAdd(OtherFactionId);
	Relation.OtherFactionId = OtherFactionId;

	if (Relation.RelationScore < GetMinimumRelationForTreaty(TreatyType))
	{
		return false;
	}

	Relation.ActiveTreaties.AddUnique(TreatyType);
	return true;
}

bool UDiplomacySubsystem::HasTreaty(FName OtherFactionId, ETreatyType TreatyType) const
{
	const FDiplomaticRelation* Relation = Relations.Find(OtherFactionId);
	return Relation && Relation->ActiveTreaties.Contains(TreatyType);
}

float UDiplomacySubsystem::GetRelationScore(FName OtherFactionId) const
{
	const FDiplomaticRelation* Relation = Relations.Find(OtherFactionId);
	return Relation ? Relation->RelationScore : 0.0f;
}
