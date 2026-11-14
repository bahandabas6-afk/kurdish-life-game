# Kurdish Life — Unreal Engine starter

Open `KurdishLife.uproject` in Unreal Engine 5. The C++ module provides a third-person character, spring-arm camera, WASD/mouse controls and Shift sprint.

## City prototype
Add an actor of class `KurdishLifeCityBuilder` to a level. It procedurally lays out a simple grid of roads and placeholder building masses. Adjust block count, spacing and random seed in Details. This is a greybox layout, not a finished detailed Sulaymaniyah map.

## Vehicle prototype
`KurdishLifeVehiclePawn` is an early placeholder vehicle pawn with basic arcade movement. Place it in a level and possess it from a PlayerController/Blueprint. Configure axes `VehicleThrottle` (W +1, S -1), `VehicleSteer` (D +1, A -1), and action `VehicleBrake` (Space). Full vehicle physics, wheels, suspension, entry/exit and traffic AI are not implemented.

## Requirements
- Unreal Engine 5.4 or compatible UE5
- Visual Studio 2022 with C++ game development components

This is a starter codebase, not a finished game. Detailed city art, character/car assets, missions, NPCs, sound, mobile controls and packaged builds remain to be developed.
