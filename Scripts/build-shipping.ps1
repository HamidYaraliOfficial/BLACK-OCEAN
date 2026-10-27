<#
.SYNOPSIS
    BLACK OCEAN - Builds a Shipping configuration Win64 game build.
#>

$ErrorActionPreference = "Stop"
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$UProjectFile = Join-Path $ProjectRoot "BlackOcean.uproject"

Write-Host "=== BLACK OCEAN - Shipping Build ===" -ForegroundColor Cyan

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

Write-Host "Building BlackOcean (Shipping | Win64)..." -ForegroundColor Cyan
& $UBTPath BlackOcean Win64 Shipping -project="$UProjectFile" -waitmutex

Write-Host "Shipping build complete." -ForegroundColor Green
