# Build the Unreal Editor target for Kurdish Life using the installed UE 5.4 toolchain.
[CmdletBinding()]
param(
    [string]$EngineRoot = $env:UE_5_4_ROOT,
    [switch]$PreflightOnly
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$ProjectFile = Join-Path $PSScriptRoot "KurdishLife.uproject"
if (-not (Test-Path -LiteralPath $ProjectFile -PathType Leaf)) {
    Write-Error "Project file not found: $ProjectFile"
    exit 2
}

try {
    $ProjectDescriptor = Get-Content -LiteralPath $ProjectFile -Raw | ConvertFrom-Json -ErrorAction Stop
}
catch {
    Write-Error "Project descriptor is not valid JSON: $($_.Exception.Message)"
    exit 2
}

if ($ProjectDescriptor.EngineAssociation -ne "5.4") {
    Write-Error "KurdishLife.uproject must target Unreal Engine 5.4; found '$($ProjectDescriptor.EngineAssociation)'."
    exit 2
}

$RuntimeModules = @($ProjectDescriptor.Modules | Where-Object {
    $_.Name -eq "KurdishLife" -and $_.Type -eq "Runtime"
})
if ($RuntimeModules.Count -ne 1) {
    Write-Error "KurdishLife.uproject must declare exactly one Runtime module named KurdishLife."
    exit 2
}

$RequiredProjectFiles = @(
    "Source\KurdishLife.Target.cs",
    "Source\KurdishLifeEditor.Target.cs",
    "Source\KurdishLife\KurdishLife.Build.cs",
    "Source\KurdishLife\KurdishLife.h",
    "Source\KurdishLife\KurdishLife.cpp",
    "Source\KurdishLife\KurdishLifeCharacter.h",
    "Source\KurdishLife\KurdishLifeCharacter.cpp",
    "Source\KurdishLife\KurdishLifeCityBuilder.h",
    "Source\KurdishLife\KurdishLifeCityBuilder.cpp",
    "Source\KurdishLife\KurdishLifeGameModeBase.h",
    "Source\KurdishLife\KurdishLifeGameModeBase.cpp",
    "Source\KurdishLife\KurdishLifeProgressionComponent.h",
    "Source\KurdishLife\KurdishLifeProgressionComponent.cpp",
    "Source\KurdishLife\KurdishLifeVehiclePawn.h",
    "Source\KurdishLife\KurdishLifeVehiclePawn.cpp"
)
foreach ($RelativePath in $RequiredProjectFiles) {
    $RequiredPath = Join-Path $PSScriptRoot $RelativePath
    if (-not (Test-Path -LiteralPath $RequiredPath -PathType Leaf)) {
        Write-Error "Required Unreal project file is missing: $RequiredPath"
        exit 2
    }
}

Write-Host "Project descriptor and required module/target files passed preflight checks."

if ($PreflightOnly) {
    Write-Host "Preflight-only mode: Unreal installation and C++ compilation were not checked."
    exit 0
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
