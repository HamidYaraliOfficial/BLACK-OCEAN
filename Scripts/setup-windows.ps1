<#
.SYNOPSIS
    BLACK OCEAN - Windows environment setup / verification script.
.DESCRIPTION
    Checks that Epic Games Launcher, Unreal Engine 5, Visual Studio 2022
    (with the required workloads), the Windows SDK and Git are all present,
    and reports what is missing. Run this before attempting a build.
#>

Write-Host "=== BLACK OCEAN - Windows Environment Check ===" -ForegroundColor Cyan

function Test-CommandExists {
    param([string]$Name)
    return $null -ne (Get-Command $Name -ErrorAction SilentlyContinue)
}

$issues = @()

# 1. Git
if (Test-CommandExists "git") {
    Write-Host "[OK] Git found: $(git --version)" -ForegroundColor Green
} else {
    $issues += "Git is not installed or not on PATH. Install from https://git-scm.com/download/win"
}

# 2. Visual Studio 2022 (vswhere is installed alongside VS since 15.2+)
$vswherePath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vswherePath) {
    $vsInfo = & $vswherePath -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationVersion
    if ($vsInfo) {
        Write-Host "[OK] Visual Studio with C++ tools found: $vsInfo" -ForegroundColor Green
    } else {
        $issues += "Visual Studio 2022 found, but the 'Desktop development with C++' workload (with Game Development with C++ component) is missing. Open Visual Studio Installer and add it."
    }
} else {
    $issues += "Visual Studio 2022 not detected. Install it from https://visualstudio.microsoft.com/vs/ with the 'Desktop development with C++' and 'Game development with C++' workloads."
}

# 3. Windows SDK (checked via registry)
$sdkRegPath = "HKLM:\SOFTWARE\WOW6432Node\Microsoft\Windows Kits\Installed Roots"
if (Test-Path $sdkRegPath) {
    Write-Host "[OK] Windows SDK installation detected." -ForegroundColor Green
} else {
    $issues += "Windows SDK not detected. It is normally installed alongside the Visual Studio C++ workload - re-run the VS Installer and ensure a Windows 10/11 SDK component is checked."
}

# 4. Unreal Engine 5 (Epic Games Launcher install path)
$uePaths = @(
    "C:\Program Files\Epic Games\UE_5.4",
    "C:\Program Files\Epic Games\UE_5.3",
    "C:\Program Files\Epic Games\UE_5.5"
)
$ueFound = $uePaths | Where-Object { Test-Path $_ }
if ($ueFound) {
    Write-Host "[OK] Unreal Engine 5 found at: $($ueFound -join ', ')" -ForegroundColor Green
} else {
    $issues += "Unreal Engine 5 (5.3/5.4/5.5) was not found under C:\Program Files\Epic Games. Install the Epic Games Launcher from https://store.epicgames.com/download and install Unreal Engine 5 from the Unreal tab."
}

Write-Host ""
if ($issues.Count -eq 0) {
    Write-Host "All required tools were detected. You are ready to run build-development.ps1." -ForegroundColor Green
} else {
    Write-Host "The following items need attention before building:" -ForegroundColor Yellow
    foreach ($issue in $issues) {
        Write-Host " - $issue" -ForegroundColor Yellow
    }
}
