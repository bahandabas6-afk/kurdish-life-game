# Kurdish Life — Unreal Engine starter

Open `KurdishLife.uproject` in Unreal Engine 5. The C++ project includes build targets, a third-person character, a procedural city greybox, an arcade vehicle pawn, and a starter money/jobs/missions component.

## Current systems
- **Player:** third-person camera, WASD movement, mouse look, Shift sprint.
- **City:** add `KurdishLifeCityBuilder` to a level to generate a simple road grid and placeholder building blocks. Tune block count, spacing and random seed in Details. This is not a detailed Sulaymaniyah recreation.
- **Vehicle:** `KurdishLifeVehiclePawn` is a placeholder arcade car pawn. Place it in a level and possess it through a PlayerController or Blueprint. Default input mappings are now included: `VehicleThrottle` (W forward, S reverse), `VehicleSteer` (D right, A left), and `VehicleBrake` (Space). The pawn still has placeholder cube geometry and arcade movement, not realistic wheels, suspension, entry/exit or traffic AI.
- **Life progression:** add `KurdishLifeProgressionComponent` to a character or other actor. It starts with 500 in-game money and exposes Blueprint-callable functions for spending/earning money, starting/finishing one job, and accepting/completing one mission. UI and save-game persistence are not included yet.

## Build and preview
1. Install Unreal Engine 5.4 or compatible UE5.
2. On Windows, install Visual Studio 2022 with the **Game development with C++** workload.
3. Right-click `KurdishLife.uproject`, choose **Generate Visual Studio project files**, then open the solution and build the Development Editor target.
4. Open the project, create a level, add a PlayerStart and the `KurdishLifeCityBuilder` actor. Set the project GameMode to `KurdishLifeGameModeBase` (already configured as the default), then press Play to test the character.
5. To test the car, add `KurdishLifeVehiclePawn` to the level and possess it using a PlayerController/Blueprint. The keyboard vehicle mappings are configured in `Config/DefaultInput.ini`.

## Honest status
This is a foundation/prototype, not a finished GTA-scale game. The source has been committed to GitHub but has not been compiled or tested in Unreal here. No Windows build, playable browser build, or iOS/Android package has been produced. Detailed Kurdistan city assets, animations, NPCs, traffic, mission design, audio, mobile touch controls, save system and UI still need implementation and testing.

## Repository
See the `Unreal/` folder in the GitHub repository: https://github.com/bahandabas6-afk/kurdish-life-game/tree/main/Unreal
