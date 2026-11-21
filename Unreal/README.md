# Kurdish Life — Unreal Engine 5.4 starter

This folder is a **source-code starter**, not a finished game or a ready-to-run packaged build. It provides a third-person C++ character, a visible primitive preview body, a procedural Sulaymaniyah-inspired city greybox actor, a placeholder arcade vehicle pawn, and a small jobs/missions/money component.

## What is in the repository

- **Project/build files:** `KurdishLife.uproject`, Game and Editor targets, and the `KurdishLife` module.
- **Third-person character:** camera boom and follow camera; WASD movement, mouse look and Shift sprint. The character now has a simple static low-poly preview body made from Unreal's built-in cube and sphere meshes, so it is visible without importing art assets. It is only a visual proxy: it has no skeletal rig, face, clothing, or walk animation.
- **City greybox:** add `KurdishLifeCityBuilder` to a level to generate a road grid, raised sidewalks, simple streetlights and placeholder building blocks. Block count, spacing, seed, building count and building height are editable on the actor. Road widths, sidewalk offsets and building placement margins now scale with block spacing so smaller and larger grid settings stay more consistent. Toggle ground, sidewalks and streetlights independently.
- **City materials:** assign project Material assets to the actor's `City|Materials` fields (Ground, Road, Sidewalk, Building, Street Light Pole and Street Light Head). The builder applies each optional material to its matching instanced mesh. Empty fields use the engine's default material; no finished material pack is supplied.
- **Vehicle:** `KurdishLifeVehiclePawn` is a placeholder arcade car pawn. Place it in a level and possess it through a PlayerController or Blueprint. Keyboard mappings are included: `VehicleThrottle` (W forward, S reverse), `VehicleSteer` (D right, A left), and `VehicleBrake` (Space). Acceleration is applied using `DeltaSeconds`, steering reverses with reverse travel, and throttle/steering values are clamped. The `Vehicle|Handling` properties in the pawn's Details panel let you tune maximum forward/reverse speed, forward/reverse acceleration, brake response, coasting response and steering rate without editing C++. Releasing possession clears throttle, steering, braking and speed so the unpossessed placeholder cannot continue driving from stale input. It still has placeholder geometry—not realistic wheels, suspension, traffic AI, or player enter/exit interaction.
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
2. Install Unreal Engine 5.4 and Visual Studio 2022 with the C++ workload.
3. Right-click `Unreal/KurdishLife.uproject` and choose **Generate Visual Studio project files**.
4. Open the generated `.sln` file in Visual Studio.
5. Select **Development Editor** and **Win64**, then build the `KurdishLifeEditor` target. Allow Unreal to compile shaders and generate project files on first launch.
6. Open `KurdishLife.uproject` in Unreal Editor. If Unreal asks to rebuild the module, use the Visual Studio build step above first.

## Make a first playable editor preview

No `.umap` level is committed yet, so create a small test map in the editor:

1. Create a new **Basic** level and save it as `Content/Maps/KurdishLifePreview.umap` (create the `Maps` folder if needed).
2. Add a **PlayerStart** near the origin, with its base above the ground.
3. Add one **KurdishLifeCityBuilder** actor at the world origin. Start with its defaults; the actor generates a compact grid of placeholder blocks, roads, sidewalks and streetlights in its construction script.
4. Add a **Directional Light** (Movable), **Sky Atmosphere**, **Sky Light** and a subtle **Exponential Height Fog**. If you use a Post Process Volume, enable **Infinite Extent (Unbound)** and keep exposure on Auto initially.
5. Press **Play**. The configured `KurdishLifeGameModeBase` spawns the C++ third-person character; use **W/A/S/D** to move, mouse to look and **Left Shift** to sprint. The simple geometric body is a temporary visibility proxy, not the final Aras character.
6. Save the level. Reopen it later to repeat the preview. Adjust the city builder's editable settings in the Details panel to change the block layout and building variation.

### Optional vehicle check

Place a `KurdishLifeVehiclePawn` in the level and set up possession from a PlayerController or Blueprint before pressing Play. When possessed, W/S throttle, A/D steer and Space brake. In the pawn's Details panel, expand **Vehicle | Handling** to tune the forward/reverse speed limits, acceleration, braking/coasting response and steering rate. These values are exposed for iteration; the pawn remains a simple kinematic placeholder, not a physics vehicle. Verify the feel at more than one frame rate and test collision against the city blocks. Reverse steering follows the direction of travel. When possession is removed, the pawn clears its input and speed state; verify this with the actual possession/exit Blueprint. The current starter does **not** automatically spawn, enter, exit or possess the car; this is a separate setup task.

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
| Character | Left Shift | Sprint |
| Vehicle (when possessed) | W / S | Throttle / reverse |
| Vehicle (when possessed) | A / D | Steer |
| Vehicle (when possessed) | Space | Brake |

## Honest status and next work

The current milestone is a **source-only Unreal starter** with a visible primitive character proxy and a procedural city greybox generator. It is not GTA-scale, and this repository has not been compiled or opened in Unreal in this environment. No screenshot, rendered level, executable, Windows package, or iOS/Android build has been produced or verified.

Source review on 2026-11-16: the city builder's generated-component cleanup loop was changed to iterate its `TObjectPtr` array directly, avoiding pointer-deduction ambiguity. On 2026-11-17, the greybox road/sidewalk widths and building placement margins were made proportional to block spacing to reduce street-edge overlap when the grid size is adjusted. On 2026-11-18, vehicle throttle was changed from per-input-callback acceleration to `DeltaSeconds`-scaled acceleration, input values were clamped, and reverse steering was made to follow travel direction. These are source-level changes only; they still need a Development Editor build and in-editor driving checks in Unreal Engine 5.4. On 2026-11-19, progression rewards were changed to saturate at the maximum signed 32-bit wallet balance and the money-change event now reports only the amount actually credited, avoiding integer overflow from unusually large rewards. On 2026-11-20, the vehicle pawn was updated to clear its control and speed state when it is unpossessed; verify the callback and the intended enter/exit flow in the editor. On 2026-11-21, the placeholder vehicle's handling values were exposed in the Details panel so the speed limits, acceleration, brake/coast response and steering rate can be tuned per placed pawn; these settings still need in-editor validation.

Still required for a convincing demo: compile and editor verification on Windows; save and review the first `.umap`; custom Aras character mesh, rig and animation; authored Sulaymaniyah buildings, roads, signs and materials; reliable vehicle possession/entry/exit; NPCs and traffic; job/mission UI and save persistence; audio; and mobile touch controls plus platform-specific packaging and testing.

## Repository

[Open the Unreal starter folder on GitHub](https://github.com/bahandabas6-afk/kurdish-life-game/tree/main/Unreal)
