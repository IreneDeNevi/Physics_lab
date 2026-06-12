# Bootstrap script for Windows + conda-forge
# Usage:
#   powershell -ExecutionPolicy Bypass -File .\setup_windows.ps1

$ErrorActionPreference = "Stop"

$envFile = Join-Path $PSScriptRoot "environment.yml"
if (-not (Test-Path $envFile)) {
    throw "environment.yml not found in script directory"
}

Write-Host "Creating conda environment 'laboratorio3' from environment.yml..." -ForegroundColor Cyan
conda env create -f $envFile

Write-Host "Environment created." -ForegroundColor Green
Write-Host "Activate with: conda activate laboratorio3" -ForegroundColor Yellow
Write-Host "Then run scripts from their own folders (datasets are local)." -ForegroundColor Yellow
