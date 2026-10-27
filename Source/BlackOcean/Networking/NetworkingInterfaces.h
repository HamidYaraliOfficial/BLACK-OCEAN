#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NetworkingInterfaces.generated.h"

// Networking is intentionally kept out of the Simulation Core in the base
// (offline) game. These interfaces define the seam a future multiplayer
// layer (Co-op Fleet Command / Competitive Naval Campaign) would implement:
// a server-authoritative simulation driver, state replication and interest
// management, without the base game depending on any of it.

UINTERFACE(BlueprintType)
class UNetSimulationDriver : public UInterface
{
	GENERATED_BODY()
};

// Implemented by a future dedicated-server module. The offline game runs an
// in-process equivalent so single-player behaves identically to a client
// connected to an authoritative server.
class INetSimulationDriver
{
	GENERATED_BODY()

public:
	virtual bool IsServerAuthoritative() const = 0;
	virtual void SubmitPlayerCommand(FName PlayerId, const FString& SerializedCommand) = 0;
};

UINTERFACE(BlueprintType)
class UNetInterestManager : public UInterface
{
	GENERATED_BODY()
};

// Decides which world entities a given connection needs replicated to it
// (e.g. only contacts within that player's sensor coverage), keeping
// bandwidth bounded as fleet/traffic counts grow.
class INetInterestManager
{
	GENERATED_BODY()

public:
	virtual TArray<FName> GetRelevantEntityIdsForConnection(FName ConnectionId) const = 0;
};
