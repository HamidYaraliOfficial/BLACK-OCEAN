<#
.SYNOPSIS
    BLACK OCEAN - Packages a Shipping build for Windows using UnrealAutomationTool (RunUAT).
#>

$ErrorActionPreference = "Stop"
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$UProjectFile = Join-Path $ProjectRoot "BlackOcean.uproject"
$OutputDir = Join-Path $ProjectRoot "Packaged\Windows"

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

$RunUAT = Join-Path $EnginePath "Engine\Build\BatchFiles\RunUAT.bat"

Write-Host "=== BLACK OCEAN - Packaging (Windows / Shipping) ===" -ForegroundColor Cyan

& $RunUAT BuildCookRun `
    -project="$UProjectFile" `
    -noP4 -platform=Win64 -clientconfig=Shipping -serverconfig=Shipping `
    -cook -allmaps -build -stage -pak -archive `
    -archivedirectory="$OutputDir"

Write-Host "Packaging complete. Output at $OutputDir" -ForegroundColor Green
