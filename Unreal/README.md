# Kurdish Life — Unreal Engine starter

Open `KurdishLife.uproject` in Unreal Engine 5. The C++ project now includes build targets, a third-person character, a procedural city greybox, an arcade vehicle pawn, and a starter money/jobs/missions component.

## Current systems
- **Player:** third-person camera, WASD movement, mouse look, Shift sprint.
- **City:** add `KurdishLifeCityBuilder` to a level to generate a simple road grid and placeholder building blocks. Tune block count, spacing and random seed in Details. This is not a detailed Sulaymaniyah recreation.
- **Vehicle:** `KurdishLifeVehiclePawn` is a placeholder arcade car pawn. Place it in a level and possess it through a PlayerController or Blueprint. Configure `VehicleThrottle` (W +1, S -1), `VehicleSteer` (D +1, A -1), and `VehicleBrake` (Space). It does not yet have realistic wheels, suspension, entry/exit or traffic AI.
- **Life progression:** add `KurdishLifeProgressionComponent` to a character or other actor. It starts with 500 in-game money and exposes Blueprint-callable functions for spending/earning money, starting/finishing one job, and accepting/completing one mission. UI and save-game persistence are not included yet.

## Build
1. Install Unreal Engine 5.4 or compatible UE5.
2. On Windows, install Visual Studio 2022 with the **Game development with C++** workload.
3. Right-click `KurdishLife.uproject`, choose **Generate Visual Studio project files**, then open the solution and build the Development Editor target.
4. Open the project, create a level, add the city builder actor, and set up a GameMode/PlayerStart. Create Blueprints from the C++ classes to configure the player and vehicle.

## Honest status
This is a foundation/prototype, not a finished GTA-scale game. The code has been committed to the repository but has not been compiled or tested in Unreal here. Detailed Kurdistan city assets, animations, NPCs, traffic, mission design, audio, mobile touch controls, save system, UI and iOS/Android/PC packaged builds still need implementation and testing.
