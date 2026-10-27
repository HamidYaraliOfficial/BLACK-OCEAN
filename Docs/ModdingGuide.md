# BLACK OCEAN — Modding Guide (Foundation)

BLACK OCEAN's data-driven systems are designed to be moddable without engine
recompilation:

- **Ship classes**: add rows to the `FShipClassDefinition` Data Table.
- **Research nodes**: add `FResearchNode` entries with new prerequisites.
- **Localization**: add or edit `Content/Localization/<code>/Game.json`
  (English `en`, Persian `fa`, Chinese `zh` ship with this scaffold).
- **Scenarios/Missions**: author `FMissionBriefing` / `FMissionObjective`
  data assets rather than hard-coding mission logic in C++.

## Validation
Before packaging, run `Scripts/run-tests.ps1`; extend
`UContentValidationTool` (Source/BlackOcean/Tools) with additional checks as
new content types are added (this scaffold ships duplicate-ID and
localization-completeness checks as a starting point).

## Versioning
Mods should declare a compatible engine/content version. `USaveGameSubsystem`
already tracks `SaveFormatVersion` for this purpose; extend the same pattern
for mod manifests as the modding system matures.
