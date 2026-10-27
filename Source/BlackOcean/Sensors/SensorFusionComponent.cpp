#include "SensorFusionComponent.h"

USensorFusionComponent::USensorFusionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FContactTrack* USensorFusionComponent::FindTrack(FName TrackId)
{
	for (FContactTrack& Track : Tracks)
	{
		if (Track.TrackId == TrackId)
		{
			return &Track;
		}
	}
	return nullptr;
}

void USensorFusionComponent::IngestReading(FName ApproxTrackId, ESensorSourceType Source, float ReliabilityOfSource,
	EContactClassification ObservedClassification, const FMaritimeCoordinates& ObservedPosition,
	const FGameTimestamp& Now)
{
	ReliabilityOfSource = FMath::Clamp(ReliabilityOfSource, 0.0f, 1.0f);

	FContactTrack* Existing = FindTrack(ApproxTrackId);
	if (!Existing)
	{
		FContactTrack NewTrack;
		NewTrack.TrackId = ApproxTrackId;
		NewTrack.LastKnownPosition = ObservedPosition;
		NewTrack.LastUpdated = Now;
		NewTrack.Confidence = ReliabilityOfSource * 0.6f; // A single source is never fully trusted at first contact.
		NewTrack.Classification = ObservedClassification;
		NewTrack.ContributingSources.Add(Source);
		Tracks.Add(NewTrack);
		return;
	}

	// Fuse: confidence trends toward whichever classification keeps getting
	// corroborated; a single low-reliability contradicting source shouldn't
	// instantly flip an otherwise well-established classification.
	if (Existing->Classification == ObservedClassification)
	{
		Existing->Confidence = FMath::Clamp(Existing->Confidence + ReliabilityOfSource * 0.25f, 0.0f, 1.0f);
	}
	else if (ReliabilityOfSource > Existing->Confidence)
	{
		Existing->Classification = ObservedClassification;
		Existing->Confidence = ReliabilityOfSource * 0.5f;
	}
	else
	{
		Existing->Confidence = FMath::Clamp(Existing->Confidence - 0.1f, 0.0f, 1.0f);
	}

	Existing->LastKnownPosition = ObservedPosition;
	Existing->LastUpdated = Now;
	Existing->ContributingSources.AddUnique(Source);
}

void USensorFusionComponent::DecayTracks(const FGameTimestamp& Now, float MinutesPerConfidenceStep)
{
	if (MinutesPerConfidenceStep <= 0.0f)
	{
		return;
	}

	for (int32 i = Tracks.Num() - 1; i >= 0; --i)
	{
		FContactTrack& Track = Tracks[i];
		const double MinutesSinceUpdate = Now.ToAbsoluteMinutes() - Track.LastUpdated.ToAbsoluteMinutes();
		const int32 DecaySteps = FMath::FloorToInt(MinutesSinceUpdate / MinutesPerConfidenceStep);

		if (DecaySteps > 0)
		{
			Track.Confidence = FMath::Clamp(Track.Confidence - 0.05f * DecaySteps, 0.0f, 1.0f);
			if (Track.Confidence <= 0.02f)
			{
				Tracks.RemoveAt(i);
			}
			else if (Track.Confidence < 0.2f)
			{
				Track.Classification = EContactClassification::Unknown;
			}
		}
	}
}
