# Build the Unreal Editor target for Kurdish Life using the installed UE 5.4 toolchain.
[CmdletBinding()]
param(
    [string]$EngineRoot = $env:UE_5_4_ROOT
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$ProjectFile = Join-Path $PSScriptRoot "KurdishLife.uproject"
if (-not (Test-Path -LiteralPath $ProjectFile -PathType Leaf)) {
    Write-Error "Project file not found: $ProjectFile"
    exit 2
}

if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $EngineRoot = "C:\Program Files\Epic Games\UE_5.4"
}

$BuildScript = Join-Path $EngineRoot "Engine\Build\BatchFiles\Build.bat"
$BuildVersionFile = Join-Path $EngineRoot "Engine\Build\Build.version"

if (-not (Test-Path -LiteralPath $BuildScript -PathType Leaf)) {
    Write-Error "Unreal Build.bat not found under '$EngineRoot'. Pass -EngineRoot or set UE_5_4_ROOT."
    exit 2
}

if (-not (Test-Path -LiteralPath $BuildVersionFile -PathType Leaf)) {
    Write-Error "Unreal Build.version not found under '$EngineRoot'. Check the EngineRoot path."
    exit 2
}

$EngineVersion = Get-Content -LiteralPath $BuildVersionFile -Raw | ConvertFrom-Json
if ($EngineVersion.MajorVersion -ne 5 -or $EngineVersion.MinorVersion -ne 4) {
    Write-Error "This project targets Unreal Engine 5.4, but the selected engine reports $($EngineVersion.MajorVersion).$($EngineVersion.MinorVersion)."
    exit 2
}

Write-Host "Building KurdishLifeEditor (Win64 Development) with Unreal Engine 5.4..."
$BuildArguments = @(
    "KurdishLifeEditor",
    "Win64",
    "Development",
    "-Project=$ProjectFile",
    "-WaitMutex",
    "-NoHotReloadFromIDE"
)

& $BuildScript @BuildArguments
$BuildExitCode = $LASTEXITCODE

if ($BuildExitCode -ne 0) {
    Write-Error "UnrealBuildTool failed with exit code $BuildExitCode."
    exit $BuildExitCode
}

Write-Host "Editor target build completed. Open KurdishLife.uproject in Unreal Editor to create and test the preview map."
exit 0
