<#
.SYNOPSIS
    BLACK OCEAN - Generates project files and builds a Development editor build.
#>

$ErrorActionPreference = "Stop"
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$UProjectFile = Join-Path $ProjectRoot "BlackOcean.uproject"

Write-Host "=== BLACK OCEAN - Development Build ===" -ForegroundColor Cyan

if (-not (Test-Path $UProjectFile)) {
    Write-Error "BlackOcean.uproject not found at $UProjectFile"
    exit 1
}

# Locate the Unreal Engine install (adjust EngineAssociation in the .uproject
# if your install path/version differs).
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

$UBTPath = Join-Path $EnginePath "Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
$GenerateProjectFilesScript = Join-Path $EnginePath "Engine\Build\BatchFiles\GenerateProjectFiles.bat"

Write-Host "Generating Visual Studio project files..." -ForegroundColor Cyan
& $GenerateProjectFilesScript $UProjectFile

Write-Host "Building BlackOceanEditor (Development | Win64)..." -ForegroundColor Cyan
& $UBTPath BlackOceanEditor Win64 Development -project="$UProjectFile" -waitmutex

Write-Host "Development build complete." -ForegroundColor Green
Write-Host "Open BlackOcean.uproject to launch the Editor."
