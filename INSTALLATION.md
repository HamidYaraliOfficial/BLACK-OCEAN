# BLACK OCEAN — Installation & Build (Windows 10/11)

This guide takes you from a clean Windows 10/11 machine to a running Editor
build of BLACK OCEAN.

## 1. Install prerequisites

1. **Epic Games Launcher** — download from
   https://store.epicgames.com/download and install.
2. **Unreal Engine 5** — open the Epic Games Launcher → **Unreal Engine**
   tab → **Library** → click **+** and install **5.4** (or the latest 5.x).
3. **Visual Studio 2022** — download from
   https://visualstudio.microsoft.com/vs/ . In the installer, select:
   - Workload: **Desktop development with C++**
   - Workload: **Game development with C++**
   - Individual component: a **Windows 10/11 SDK** (installed automatically
     with the workloads above on a default install)
4. **Git** — download from https://git-scm.com/download/win and install with
   default options.

## 2. Verify your environment

From PowerShell, in the project's `Scripts/` folder:

```powershell
./setup-windows.ps1
```

This checks Git, Visual Studio + C++ workload, the Windows SDK and Unreal
Engine 5, and tells you exactly what is missing if anything is.

## 3. Generate project files and build the Editor (Development)

```powershell
./build-development.ps1
```

This locates your Unreal Engine install, runs `GenerateProjectFiles.bat`
against `BlackOcean.uproject`, then compiles the `BlackOceanEditor` target in
the `Development | Win64` configuration.

## 4. Open the Editor

Double-click `BlackOcean.uproject` (or, from the Editor's own launcher,
open it from Epic Games Launcher → Unreal Engine → Library → Recent
Projects once you've opened it once).

## 5. Run the automation tests

```powershell
./run-tests.ps1
```

Runs the `BlackOcean.*` automation test suite headlessly and writes results
to `Tests/TestResults.log`.

## 6. Build a Development game build (optional, for testing outside the Editor)

Use the Editor's **Platforms → Windows → Package Project** menu, or extend
`build-development.ps1` to also build the `BlackOcean` (non-Editor) target
in Development if you need a launchable-but-unoptimized .exe.

## 7. Build a Shipping build

```powershell
./build-shipping.ps1
```

## 8. Package a distributable build

```powershell
./package.ps1
```

This runs `RunUAT.bat BuildCookRun` to cook, stage, pak and archive a
Shipping Win64 build into `Packaged/Windows/`.

## 9. Clean intermediate files (optional)

```powershell
./clean.ps1
```

Removes `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`,
`.vs/` and any generated `.sln`, so you can regenerate a fresh build.

## Troubleshooting

- **"Could not locate an Unreal Engine 5 installation"** — the scripts look
  under `C:\Program Files\Epic Games\UE_5.3` / `UE_5.4` / `UE_5.5`. If yours
  is installed elsewhere, edit the `$EnginePathCandidates` array at the top
  of the relevant script.
- **Missing C++ workload** — re-run the Visual Studio Installer, select
  **Modify** on your VS2022 install, and check **Desktop development with
  C++** and **Game development with C++**.
- **Build fails referencing a plugin** (Water, Niagara, CommonUI,
  EnhancedInput, GameplayAbilities) — these ship with Unreal Engine 5 by
  default; ensure they weren't deselected during the Epic Games Launcher
  engine install (Options → check all default components).
