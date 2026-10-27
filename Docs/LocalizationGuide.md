# BLACK OCEAN — Localization Guide

## Supported Languages
- English (`en`) — Left-to-Right
- Persian / فارسی (`fa`) — Right-to-Left
- Chinese / 中文 (`zh`) — Left-to-Right

## How It Works
`ULocalizationSubsystem` (Source/BlackOcean/UI) is the runtime language
manager:
- `SetLanguage()` switches the active language and the engine culture.
- `GetCurrentFlowDirection()` returns `RightToLeft` for Persian and
  `LeftToRight` otherwise — root UMG widgets should read this and call
  `SetFlowDirectionPreference` so menus, panels, tables, reports, tooltips
  and dialogs mirror correctly for Persian.
- `GetString(Key)` resolves a string for the active language, falling back
  to English and then to the raw key (so a missing translation is visibly
  obvious rather than a blank widget).

## Adding a String
1. Add the key/value to `Content/Localization/en/Game.json` (source of
   truth), then to `fa/Game.json` and `zh/Game.json`.
2. Run `UContentValidationTool::CheckLocalizationCompleteness` (wired into
   `run-tests.ps1`) to confirm nothing is missing before packaging.

## Fonts & Number Formatting
Assign a font asset with Persian and Chinese glyph coverage plus a fallback
family in Project Settings so missing glyphs never render as tofu boxes.
`ULocalizationSubsystem::FormatNumber` is a minimal placeholder — swap in
`FText::AsNumber` with the active `FCulture` for full ICU-correct digit
grouping if/when the design calls for locale-specific number shaping.
