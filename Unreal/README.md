# Kurdish Life — Unreal Engine starter

Open `KurdishLife.uproject` in Unreal Engine 5. The C++ project includes build targets, a third-person character, a procedural city greybox, an arcade vehicle pawn, and a starter money/jobs/missions component.

## Current systems
- **Player:** third-person camera, WASD movement, mouse look, Shift sprint.
- **City:** add `KurdishLifeCityBuilder` to a level to generate a road grid, raised sidewalks, simple streetlights and placeholder building blocks. Block count, spacing, seed, building count and building height are editable on the actor. Toggle ground, sidewalks and streetlights independently.
- **City materials:** assign project Material assets to the actor's `City|Materials` fields (Ground, Road, Sidewalk, Building, Street Light Pole and Street Light Head). The builder applies each optional material to its matching instanced mesh. If a field is empty, the engine's basic-shape default material remains. This is a material-assignment foundation, not a supplied finished material pack.
- **Vehicle:** `KurdishLifeVehiclePawn` is a placeholder arcade car pawn. Place it in a level and possess it through a PlayerController or Blueprint. Keyboard mappings are included: `VehicleThrottle` (W forward, S reverse), `VehicleSteer` (D right, A left), and `VehicleBrake` (Space). The pawn still has placeholder geometry and arcade movement, not realistic wheels, suspension, entry/exit or traffic AI.
- **Life progression:** add `KurdishLifeProgressionComponent` to a character or other actor. It starts with 500 in-game money and exposes Blueprint-callable functions for spending/earning money, starting/finishing one job, and accepting/completing one mission. UI and save-game persistence are not included yet.
- **Graphics settings:** Lumen global illumination/reflections, TSR anti-aliasing, Virtual Shadow Maps and a high-quality scalability profile are configured. These are renderer settings only; they do not create realistic art assets or guarantee a high frame rate. Use a lower scalability level on weaker hardware.

## Suggested lighting and preview setup
1. Create or open a test level, add a `PlayerStart` and one `KurdishLifeCityBuilder` actor.
2. Add a `Directional Light` and set it to **Movable**. Enable **Atmosphere Sun Light** if you add a Sky Atmosphere.
3. Add a `Sky Atmosphere` and a `Sky Light`; use **Movable** for the Sky Light while iterating. Build the sky first, then use the Sky Light's **Recapture** control if the scene does not update automatically.
4. Add an `Exponential Height Fog` for distance depth. Keep fog subtle while checking street/building readability.
5. Add a `Post Process Volume`, enable **Infinite Extent (Unbound)**, and initially leave exposure on **Auto**. Tune exposure, contrast and bloom only after the basic daylight looks correct.
6. Select the city builder and assign simple project materials to its `City|Materials` fields. Start with distinct road, sidewalk, ground and building materials so the layout reads clearly; replace them with authored PBR materials later.
7. Press Play and inspect the whole district, then adjust `BlocksPerSide`, `BlockSpacing`, building count and height in the builder's Details panel.

## Build and preview
1. Install Unreal Engine 5.4 or compatible UE5.
2. On Windows, install Visual Studio 2022 with the **Game development with C++** workload.
3. Right-click `KurdishLife.uproject`, choose **Generate Visual Studio project files**, then open the solution and build the Development Editor target.
4. Open the project, create a level, add a PlayerStart and the `KurdishLifeCityBuilder` actor. The project GameMode is configured as `KurdishLifeGameModeBase`; press Play to test the character.
5. To test the car, add `KurdishLifeVehiclePawn` to the level and possess it using a PlayerController/Blueprint.

## Honest status
This is a foundation/prototype, not a finished GTA-scale game. The repository edits have not been compiled or tested in Unreal in this environment, and the level has not been opened or rendered here. No Windows build, playable browser build, or iOS/Android package has been produced. Detailed Sulaymaniyah/Kurdistan assets, authored PBR materials, character animations, NPCs, traffic, mission design, audio, mobile touch controls, save system and UI still need implementation and testing.

## Repository
See the `Unreal/` folder in the GitHub repository: https://github.com/bahandabas6-afk/kurdish-life-game/tree/main/Unreal
