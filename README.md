# Plants vs Zombies

## Overview

This project is a simplified "Plants vs Zombies" game with hexagon enemies in a 3x3 grid. Players place rhombus defenders strategically to shoot projectiles and eliminate hexagons.

## Requirements

- **CMake:** Required for building and running the game.
  
## Basic Functionality

- **Game Elements:** Simple grid with rhombus defenders and hexagon enemies.
- **Animations:** Smooth movement and disappearance of hexagons and projectiles.
- **Gameplay:** Place rhombi, random enemy spawning, completion detection, projectile appearance, collision detection.

## Advanced Features

- **Drag & Drop:** GUI layout, rhombus selection and display, release detection, cell deletion.
- **Resource Management:** Star spawning, collection, display, placement restriction, resource count.
- **Color-Based Gameplay:** GUI display, enemy variety, projectile matching, color match.

## Implementation Details

- **Visual Elements:** Construct using triangles or basic shapes.
- **Scene Construction:** Design a grid-based scene with specific color schemes.
- **Drag & Drop:** Transform cursor coordinates, implement AABB for object detection.
- **Collision Detection:** Utilize circles for collision approximation.
- **GUI Implementation:** Design a concise interface with framed visuals, containers, and indicators.

