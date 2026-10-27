<#
.SYNOPSIS
    BLACK OCEAN - Runs the automation test suite headlessly via the Editor-Cmd.
#>

$ErrorActionPreference = "Stop"
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$UProjectFile = Join-Path $ProjectRoot "BlackOcean.uproject"

$EnginePathCandidates = @(
    "C:\Program Files\Epic Games\UE_5.4",
    "C:\Program Files\Epic Games\UE_5.3",
    "C:\Program Files\Epic Games\UE_5.5"
)
$EnginePath = $EnginePathCandidates | Where-Object { Test-Path $_ } | Select-Object -First 1

if (-not $EnginePath) {
    Write-Error "Could not locate an Unreal Engine 5 installation. Run setup-windows.ps1 first."
    exit 1
}

$EditorCmd = Join-Path $EnginePath "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$LogFile = Join-Path $ProjectRoot "Tests\TestResults.log"

Write-Host "=== BLACK OCEAN - Automation Test Run ===" -ForegroundColor Cyan

& $EditorCmd $UProjectFile `
    -ExecCmds="Automation RunTests BlackOcean; Quit" `
    -unattended -nopause -nosplash -log="$LogFile"

Write-Host "Test run complete. See $LogFile for results." -ForegroundColor Green
