# BLACK OCEAN — Technical Design Overview

## Engine & Language Split
- **C++** owns all heavy simulation: Ocean, Ships, Submarine, Crew, Sensors,
  Navigation, Fleet, Command, AI, Logistics, Ports, Shipyard, Research,
  Economy, Diplomacy, Missions, Save, Replay, UI theming/localization logic.
- **Blueprint** (added by designers in-editor) is reserved for level
  composition, animation, UI widget layout/binding, VFX and rapid iteration —
  it should call into the C++ subsystems/components above rather than
  reimplementing simulation logic.

## Module Layout
A single primary game module (`BlackOcean`) contains one folder per system
under `Source/BlackOcean/`. This keeps the initial build simple; systems can
be split into their own UE plugins later (see `Plugins/`) once their
interfaces stabilize, without changing where the logic lives.

## Determinism
`UTimeControlSubsystem` is the single source of truth for campaign time.
Systems that need to be replayable/testable (Ocean drift, damage spread,
crew fatigue, supply runs) take `DeltaMinutes` from this clock rather than
`DeltaTime`/`FPlatformTime`, so a recorded `UReplayRecorderSubsystem` session
and the Scenario Simulation Harness can reproduce a run exactly given the
same random seed.

## Data-Driven Content
Ship classes (`FShipClassDefinition`), research nodes (`FResearchNode`) and
similar design-owned data are `USTRUCT : public FTableRowBase`, meant to be
authored in Data Tables/Data Assets rather than hard-coded, so designers can
add/rebalance content without recompiling. `Content/Localization/<lang>/Game.json`
follows the same philosophy for quick string-table iteration.

## Extending This Scaffold
Each module currently implements a meaningful, working subset of its named
system (see the README feature-to-file map). To extend a system:
1. Add new fields/structs following the existing pattern in that module.
2. Keep simulation logic in C++; expose `UFUNCTION(BlueprintCallable)` /
   `BlueprintPure` entry points for designers.
3. Feed new state through `UWorldStateSubsystem::RecordCausalEvent` where it
   should be visible to the Causal Event Graph / Fleet Chronicle.
4. Add an automation test under `Tests/` alongside the feature (see
   `PortOperatingHoursTest.cpp` for the pattern).
