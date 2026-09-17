# CombatPrototype

A small 2D combat prototype built with **C++** and **raylib**.

This project started as a C++ OOP practice project and is gradually evolving into a modular game prototype.  
The current focus is on basic combat mechanics, animation, AI, collision handling, and code structure.

## Current Features

- Player movement with directional animations
- Player melee attacks
- Boss idle, chasing, and attacking behavior
- Basic Boss AI state machine
- Attack hitbox detection and damage handling
- Character collision detection and resolution
- Centralized texture loading and unloading
- Debug visualization for collision and combat hitboxes

## Project Structure

```text
code/
├── main.cpp
├── ai/
│   ├── BossAI.cpp
│   └── BossAI.h
├── animation/
│   ├── AnimationSystem.cpp
│   └── AnimationSystem.h
├── character/
│   ├── Character.cpp
│   ├── Character.h
│   ├── Player.h
│   └── Boss.h
├── combat/
│   ├── CombatSystem.cpp
│   └── CombatSystem.h
├── physics/
│   ├── CollisionSystem.cpp
│   ├── CollisionSystem.h
│   └── FacingDirection.h
└── resources/
    ├── GameAssets.cpp
    └── GameAssets.h
```

## Architecture

The project is being refactored from a `main.cpp`-driven prototype into separate systems with clearer responsibilities.

- **BossAI** handles Boss decision-making and AI states.
- **CombatSystem** handles attack hitboxes, hit detection, and damage.
- **AnimationSystem** selects animations and updates animation frames.
- **CollisionSystem** handles character collision boxes and physical collision resolution.
- **GameAssets** owns and manages texture loading and unloading.
- **main.cpp** coordinates the game loop and the different systems.

One design principle used during the refactoring is to keep different responsibilities separate even when they use similar underlying data. For example, physical character collision is handled by `CollisionSystem`, while attack hitboxes remain part of `CombatSystem`.

## Development Status

This project is currently an early combat prototype rather than a complete game.

Recent development has focused on moving functionality that was originally implemented directly in `main.cpp` into dedicated modules while keeping the prototype functional after each refactoring step.

### Planned Next Steps

- Introduce a `PlayerController` layer for player input and decision handling
- Add defense mechanics
- Add a posture / stamina system
- Add dodge rolling and invincibility frames
- Continue expanding the combat system

## Tech Stack

- C++
- raylib
- MinGW-w64 / g++
- Visual Studio Code
- Git / GitHub