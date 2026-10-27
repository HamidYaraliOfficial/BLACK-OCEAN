<#
.SYNOPSIS
    BLACK OCEAN - Removes generated/intermediate build artifacts.
#>

$ProjectRoot = Split-Path -Parent $PSScriptRoot

$FoldersToClean = @("Binaries", "Intermediate", "Saved", "DerivedDataCache", ".vs", "Packaged")

Write-Host "=== BLACK OCEAN - Clean ===" -ForegroundColor Cyan

foreach ($Folder in $FoldersToClean) {
    $FullPath = Join-Path $ProjectRoot $Folder
    if (Test-Path $FullPath) {
        Write-Host "Removing $FullPath ..." -ForegroundColor Yellow
        Remove-Item -Recurse -Force $FullPath
    }
}

Get-ChildItem -Path $ProjectRoot -Filter "*.sln" | Remove-Item -Force -ErrorAction SilentlyContinue

Write-Host "Clean complete." -ForegroundColor Green
