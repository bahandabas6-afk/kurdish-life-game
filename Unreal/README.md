# Kurdish Life — Unreal Engine 5.4 starter

This folder is a **source-code starter**, not a finished game or a ready-to-run packaged build. It provides a third-person C++ character, a visible primitive preview body, a procedural Sulaymaniyah-inspired city greybox actor, a placeholder arcade vehicle pawn, and a small jobs/missions/money component.

## What is in the repository

- **Project/build files:** `KurdishLife.uproject`, Game and Editor targets, and the `KurdishLife` module.
- **Third-person character:** camera boom and follow camera; WASD movement, mouse look and Shift sprint. The legacy input config also maps a standard gamepad's left stick to movement, right stick to camera look, and left-stick click to sprint. Controller mappings are source configuration and still need testing with a connected controller. The character now has a simple static low-poly preview body made from Unreal's built-in cube and sphere meshes, so it is visible without importing art assets. It is only a visual proxy: it has no skeletal rig, face, clothing, or walk animation.
- **City greybox:** add `KurdishLifeCityBuilder` to a level to generate a road grid, raised sidewalks, simple streetlights and placeholder building blocks. Block count, spacing, seed, building count and building height are editable on the actor. Road widths, sidewalk offsets and building placement margins now scale with block spacing so smaller and larger grid settings stay more consistent. Toggle ground, sidewalks and streetlights independently.
- **City materials:** assign project Material assets to the actor's `City|Materials` fields (Ground, Road, Sidewalk, Building, Street Light Pole and Street Light Head). The builder applies each optional material to its matching instanced mesh. Empty fields use the engine's default material; no finished material pack is supplied.
- **Vehicle:** `KurdishLifeVehiclePawn` is a placeholder arcade car pawn. Place it in a level and possess it through a PlayerController or Blueprint. Keyboard mappings are included: `VehicleThrottle` (W forward, S reverse), `VehicleSteer` (D right, A left), and `VehicleBrake` (Space). A standard gamepad uses the right trigger for forward throttle, left trigger for reverse, left stick for steering and left shoulder for brake. Acceleration is applied using `DeltaSeconds`, steering reverses with reverse travel, and throttle/steering values are clamped. The `Vehicle|Handling` properties in the pawn's Details panel let you tune maximum forward/reverse speed, forward/reverse acceleration, brake response, coasting response and steering rate without editing C++. Releasing possession clears throttle, steering, braking and speed so the unpossessed placeholder cannot continue driving from stale input. It still has placeholder geometry—not realistic wheels, suspension, traffic AI, or player enter/exit interaction.
- **Life progression:** add `KurdishLifeProgressionComponent` to a character or other actor. It starts with 500 in-game money and exposes Blueprint-callable functions for spending/earning money, starting/finishing one job, and accepting/completing one mission. UI and save-game persistence are not included.
- **Graphics settings:** Lumen global illumination/reflections, TSR anti-aliasing, Virtual Shadow Maps and a high-quality scalability profile are configured. These are renderer settings only; they do not create realistic art assets or guarantee a high frame rate. Lower scalability on weaker hardware.

## Requirements

- Windows 10/11 64-bit.
- **Unreal Engine 5.4** (the project explicitly sets `EngineAssociation` to `5.4`).
- Visual Studio 2022 with the **Game development with C++** workload and a Windows SDK.
- Enough disk space for Unreal Engine, Visual Studio and generated intermediate/build files.

This repository does not contain a prebuilt executable, an iOS/Android package, a saved Unreal level, or a complete Content asset library.

## Build the editor target on Windows

1. Clone or download the repository and keep the `Unreal/` folder structure intact.
2. Install Unreal Engine 5.4 and Visual Studio 2022 with the **Game development with C++** workload and a Windows SDK.
3. From the repository root, run the helper script in PowerShell:

   ```powershell
   powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\Unreal\BuildEditor-Windows.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.4"
   ```

   Before invoking Unreal Build Tool, the script parses the `.uproject` JSON, checks that `EngineAssociation` is `5.4`, checks for exactly one `KurdishLife` Runtime module, and verifies that the Game/Editor targets plus every current module header/source file and `Config/DefaultInput.ini` exist. It also scans the character and vehicle C++ files for legacy `BindAxis`/`BindAction` names and confirms that each has a corresponding `AxisName`/`ActionName` declaration in `DefaultInput.ini`. It then checks that the Unreal Build Tool files exist, verifies that the selected engine reports version 5.4, and asks Unreal Build Tool to compile `KurdishLifeEditor` for `Win64 Development`. These preflight checks validate project structure and input-name consistency only; they do **not** prove that the C++ code compiles or that a physical controller works. The same source checks can run without an Unreal installation by passing `-PreflightOnly`; a Windows GitHub Actions workflow runs that mode when Unreal source or the workflow changes. If Unreal is installed elsewhere, pass its installation root with `-EngineRoot`. You can also set `UE_5_4_ROOT` and omit that parameter. This builds the editor C++ target; it does **not** create a packaged game or a saved level.
4. When the build succeeds, open `Unreal/KurdishLife.uproject` in Unreal Editor and follow **Make a first playable editor preview** below.

If you prefer Visual Studio, right-click `Unreal/KurdishLife.uproject`, choose **Generate Visual Studio project files**, open the generated `.sln`, select **Development Editor** and **Win64**, and build `KurdishLifeEditor`. Then open the `.uproject` in Unreal Editor. If the editor asks to rebuild the module, complete the C++ build first.

## Make a first playable editor preview

No `.umap` level is committed yet, so create a small test map in the editor:

1. Create a new **Basic** level and save it as `Content/Maps/KurdishLifePreview.umap` (create the `Maps` folder if needed).
2. Add a **PlayerStart** near the origin, with its base above the ground.
3. Add one **KurdishLifeCityBuilder** actor at the world origin. Start with its defaults; the actor generates a compact grid of placeholder blocks, roads, sidewalks and streetlights in its construction script.
4. Add a **Directional Light** (Movable), **Sky Atmosphere**, **Sky Light** and a subtle **Exponential Height Fog**. If you use a Post Process Volume, enable **Infinite Extent (Unbound)** and keep exposure on Auto initially.
5. Press **Play**. The configured `KurdishLifeGameModeBase` spawns the C++ third-person character; use **W/A/S/D** to move, mouse to look and **Left Shift** to sprint. The simple geometric body is a temporary visibility proxy, not the final Aras character.
6. Save the level. Reopen it later to repeat the preview. Adjust the city builder's editable settings in the Details panel to change the block layout and building variation.

### Optional vehicle check

Place a `KurdishLifeVehiclePawn` in the level and set up possession from a PlayerController or Blueprint before pressing Play. When possessed, W/S throttle, A/D steer and Space brake; a standard gamepad uses the right/left triggers for forward/reverse, left stick for steering and left shoulder for brake. In the pawn's Details panel, expand **Vehicle | Handling** to tune the forward/reverse speed limits, acceleration, braking/coasting response and steering rate. These values are exposed for iteration; the pawn remains a simple kinematic placeholder, not a physics vehicle. Verify the feel at more than one frame rate and test collision against the city blocks. Reverse steering follows the direction of travel. When possession is removed, the pawn clears its input and speed state; verify this with the actual possession/exit Blueprint. The current starter does **not** automatically spawn, enter, exit or possess the car; this is a separate setup task.

## Lighting and material iteration

- Assign simple project materials to the city builder's `City|Materials` fields. Start with visibly different ground, road, sidewalk and building materials; replace them with authored PBR materials later.
- For a movable sun, enable **Atmosphere Sun Light** if a Sky Atmosphere is present.
- Build the sky first, then use the Sky Light's **Recapture** control if the scene does not update automatically.
- Tune exposure, contrast and bloom only after daylight, road width and building readability look correct.

## Controls

| Context | Input | Action |
|---|---|---|
| Character | W / S | Move forward / backward |
| Character | A / D | Move left / right |
| Character | Mouse | Rotate camera |
| Character | Left Shift / gamepad left-stick click | Sprint |
| Character | Gamepad left stick | Move |
| Character | Gamepad right stick | Rotate camera |

| Vehicle (when possessed) | W / S | Throttle / reverse |
| Vehicle (when possessed) | A / D | Steer |
| Vehicle (when possessed) | Space / gamepad left shoulder | Brake |
| Vehicle (when possessed) | Gamepad right / left trigger | Throttle / reverse |
| Vehicle (when possessed) | Gamepad left stick | Steer |


## Honest status and next work

The current milestone is a **source-only Unreal starter** with a visible primitive character proxy and a procedural city greybox generator. It is not GTA-scale, and this repository has not been compiled or opened in Unreal in this environment. No screenshot, rendered level, executable, Windows package, or iOS/Android build has been produced or verified.

Source review on 2026-11-16: the city builder's generated-component cleanup loop was changed to iterate its `TObjectPtr` array directly, avoiding pointer-deduction ambiguity. On 2026-11-17, the greybox road/sidewalk widths and building placement margins were made proportional to block spacing to reduce street-edge overlap when the grid size is adjusted. On 2026-11-18, vehicle throttle was changed from per-input-callback acceleration to `DeltaSeconds`-scaled acceleration, input values were clamped, and reverse steering was made to follow travel direction. These are source-level changes only; they still need a Development Editor build and in-editor driving checks in Unreal Engine 5.4. On 2026-11-19, progression rewards were changed to saturate at the maximum signed 32-bit wallet balance and the money-change event now reports only the amount actually credited, avoiding integer overflow from unusually large rewards. On 2026-11-20, the vehicle pawn was updated to clear its control and speed state when it is unpossessed; verify the callback and the intended enter/exit flow in the editor. On 2026-11-21, the placeholder vehicle's handling values were exposed in the Details panel so the speed limits, acceleration, brake/coast response and steering rate can be tuned per placed pawn; these settings still need in-editor validation. On 2026-11-22, a Windows PowerShell helper was added to validate the selected Unreal installation is 5.4 and invoke the Development Editor build; the script itself has not been run in this environment. On 2026-11-23, the helper gained source-only preflight checks for valid project JSON, exactly one expected Runtime module, and the required Game/Editor target and module build files. Those checks have not been executed in Windows PowerShell here and do not replace an Unreal build. On 2026-11-24, the legacy input config gained standard gamepad mappings for third-person movement/look/sprint and placeholder vehicle throttle/steering/braking; verify axis direction, trigger behavior, dead zones and button recognition with the actual controller in Unreal Editor. On 2026-11-25, the Windows build helper gained a `-PreflightOnly` mode, an explicit project EngineAssociation check and checks for all current module source/header files; a Windows GitHub Actions workflow now runs this source-layout preflight on Unreal-related changes. This workflow does not install Unreal Engine or compile C++. Its first run exposed a missing closing parenthesis in the helper's required-file array; that typo was corrected in commit [`a8012cc`](https://github.com/bahandabas6-afk/kurdish-life-game/commit/a8012cc9eb6be9074bd68c7d9dd0d510856e90ee). The corrected source preflight passed in [GitHub Actions run 45667243219](https://github.com/bahandabas6-afk/kurdish-life-game/actions/runs/45667243219) and [run 45667325020](https://github.com/bahandabas6-afk/kurdish-life-game/actions/runs/45667325020); these confirm only PowerShell execution, project descriptor checks and required-file presence, not C++ compilation or Unreal Editor behavior. On 2026-11-26, the preflight was extended to compare every legacy `BindAxis`/`BindAction` name in the character and vehicle C++ sources with the matching axis/action declaration in `DefaultInput.ini`. This new cross-check has been committed but is awaiting its own Windows Actions run; it is a static source check, not a controller test or C++ build.

Still required for a convincing demo: compile and editor verification on Windows; save and review the first `.umap`; custom Aras character mesh, rig and animation; authored Sulaymaniyah buildings, roads, signs and materials; reliable vehicle possession/entry/exit; NPCs and traffic; job/mission UI and save persistence; audio; and mobile touch controls plus platform-specific packaging and testing.

## Repository

[Open the Unreal starter folder on GitHub](https://github.com/bahandabas6-afk/kurdish-life-game/tree/main/Unreal)
