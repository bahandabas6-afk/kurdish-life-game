# Kurdish Life — Unreal Engine starter

This folder is the C++ foundation for a third-person open-world project.

## Requirements
- Unreal Engine 5.4 (or a compatible UE5 release)
- Visual Studio 2022 with the C++ game development workload on Windows

## Included
- Unreal project descriptor and C++ runtime module
- Third-person character with spring-arm follow camera
- WASD movement, mouse look, and Shift sprint (after setting the matching input mappings)

## First editor setup
1. Open `KurdishLife.uproject` in Unreal Engine.
2. Allow the IDE project files to generate and compile the C++ module.
3. Create a Blueprint based on `KurdishLifeCharacter`.
4. Set that Blueprint as the Default Pawn in a GameMode.
5. In Project Settings → Input, add axes `MoveForward` (W=+1, S=-1), `MoveRight` (D=+1, A=-1), `Turn` (Mouse X=+1), `LookUp` (Mouse Y=-1), and action `Sprint` (Left Shift).

This is a starter foundation, not a finished GTA-scale game. It does not yet include a detailed city, vehicles, missions, character assets, or mobile packaging. Those require additional development and licensed/created assets.
