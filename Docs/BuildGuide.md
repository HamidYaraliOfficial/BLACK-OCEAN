# BLACK OCEAN — Build Guide

See the root `INSTALLATION.md` for first-time environment setup on Windows
10/11. Once your environment passes `Scripts/setup-windows.ps1`:

| Task | Script |
|---|---|
| Generate project files + Development editor build | `Scripts/build-development.ps1` |
| Shipping Win64 build | `Scripts/build-shipping.ps1` |
| Run the automation test suite | `Scripts/run-tests.ps1` |
| Package a distributable Shipping build | `Scripts/package.ps1` |
| Remove intermediate/build artifacts | `Scripts/clean.ps1` |

All scripts auto-detect a `UE_5.3` / `UE_5.4` / `UE_5.5` install under
`C:\Program Files\Epic Games\`. If your engine is installed elsewhere, edit
the `$EnginePathCandidates` array at the top of each script.

CI (Windows runners) should call, in order: `setup-windows.ps1` →
`build-development.ps1` → `run-tests.ps1` → `build-shipping.ps1` →
`package.ps1`, failing the pipeline on any non-zero exit code.
