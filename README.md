# DynoGame

**DynoGame** is a small **Unreal Engine 5.2** practice project inspired by the classic **Google Chrome Dino game**.

I created this project as a gameplay programming exercise to practice core Unreal Engine C++ systems such as player input, animation states, collision handling, enemy spawning, and game flow management.

---

## Overview

In **DynoGame**, the player controls a dinosaur character that must survive by avoiding incoming obstacles.

The player can:

- **jump** over obstacles
- **duck** under danger
- survive for as long as possible while enemies keep spawning

The game tracks the player's survival time and ends when the dinosaur collides with an obstacle.

This project was created as a simple but useful practice prototype to improve my understanding of Unreal Engine 2D gameplay systems.

---

## Gameplay Features

- **Dino player character**
  - Idle state
  - Jump action
  - Duck action
  - Dead state on collision

- **Animation state system**
  - Flipbook switching based on player state
  - Idle / Jump / Duck / Dead transitions

- **Obstacle enemies**
  - Enemies move toward the player from right to left
  - Destroy themselves after leaving the gameplay area

- **Random spawning system**
  - Enemies spawn at random time intervals
  - Minimum wait time helps avoid unfair overlapping spawns

- **Collision-based game over**
  - The player dies when colliding with an enemy obstacle
  - The game transitions to a dedicated **Game Over** level

- **Survival timer**
  - The GameMode tracks elapsed survival time
  - Can be used for score, UI, or difficulty progression

---

## Technical Focus

This project helped me practice the following Unreal Engine systems:

- C++ pawn setup
- input binding for jump and duck
- Paper2D flipbook animation handling
- capsule collision and overlap events
- collision with the ground to reset jump state
- timer-based random enemy spawning
- GameMode-based survival time tracking
- game over level transition logic

---

## Tech Stack

- **Engine:** Unreal Engine 5.2
- **Language:** C++
- **Framework/Modules:** Unreal Engine Gameplay Framework, Paper2D
- **Project Type:** Practice project
- **Inspiration:** Google Chrome Dino game

---

## Main Classes

### `ADyno`
Handles:
- player input
- jump and duck actions
- collision with obstacles
- animation state updates
- player death and game over trigger

### `AEnemy`
Handles:
- obstacle movement
- automatic movement toward the player
- self-destruction after leaving the screen

### `ASpawner`
Handles:
- random obstacle spawning
- spawn interval management
- timing between enemy spawns

### `ADynoGameGameModeBase`
Handles:
- survival time tracking
- clock start/reset
- ending the game when the player dies
- loading the game over level

---

## What I Learned

This project helped me improve my understanding of how to build a simple but complete gameplay loop in Unreal Engine using C++.

Through this prototype, I practiced:

- handling player state transitions
- using Paper2D flipbooks for gameplay animation
- preventing repeated jumping while in the air
- changing collision size while ducking
- building a simple endless obstacle system
- controlling game flow through GameMode logic

It was a useful project for understanding how multiple gameplay systems work together inside a small arcade-style prototype.

---

## Project Purpose

This project was created as a **practice exercise** inspired by the Dino browser game.

Its purpose was to help me improve my Unreal Engine programming skills by recreating a recognizable endless runner formula and implementing it with my own gameplay logic in C++.

---

## Future Improvements

Possible future improvements for this project include:

- score display based on survival time
- increasing difficulty over time
- multiple obstacle types
- background scrolling system
- start/restart menu
- sound and visual polish
- high score saving
- improved UI feedback

---

## Status

**Completed as a practice project**

---

## Author

**George Bolias**  
Game Programmer / Unreal Engine Developer

- Portfolio: [https://www.georgebolias.com/](https://www.georgebolias.com/)
- LinkedIn: [https://www.linkedin.com/in/georgebolias/](https://www.linkedin.com/in/georgebolias/)
- GitHub: [https://github.com/GamingMystae](https://github.com/GamingMystae)
