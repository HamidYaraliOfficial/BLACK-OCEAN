#include "ContentValidationTool.h"

bool UContentValidationTool::CheckForDuplicateIds(const TArray<FName>& Ids, TArray<FValidationIssue>& OutIssues)
{
	TSet<FName> Seen;
	bool bFoundIssue = false;

	for (const FName& Id : Ids)
	{
		if (Seen.Contains(Id))
		{
			FValidationIssue Issue;
			Issue.IssueType = EValidationIssueType::DuplicateId;
			Issue.Context = Id.ToString();
			Issue.Description = FString::Printf(TEXT("Duplicate identifier detected: %s"), *Id.ToString());
			OutIssues.Add(Issue);
			bFoundIssue = true;
		}
		Seen.Add(Id);
	}
	return !bFoundIssue;
}

bool UContentValidationTool::CheckLocalizationCompleteness(const TMap<FString, FString>& ReferenceTable,
	const TMap<FString, FString>& TargetTable, const FString& TargetLanguageLabel,
	TArray<FValidationIssue>& OutIssues)
{
	bool bComplete = true;
	for (const auto& Pair : ReferenceTable)
	{
		if (!TargetTable.Contains(Pair.Key))
		{
			FValidationIssue Issue;
			Issue.IssueType = EValidationIssueType::MissingLocalization;
			Issue.Context = TargetLanguageLabel;
			Issue.Description = FString::Printf(TEXT("Missing key '%s' in %s string table"), *Pair.Key, *TargetLanguageLabel);
			OutIssues.Add(Issue);
			bComplete = false;
		}
	}
	return bComplete;
}
