# 🌟 miniRT - Ray Tracing Engine

![42 Badge](https://img.shields.io/badge/42-miniRT-brightgreen)
![Score](https://img.shields.io/badge/Score-100%2F100-success)
![Language](https://img.shields.io/badge/Language-C-blue)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange)
![Status](https://img.shields.io/badge/Status-Completed-success)


<p align="center">
  <img src="https://raw.githubusercontent.com/byaliego/42-project-badges/main/badges/minirte.png" alt="miniRT Badge" width="150" height="150">
</p>

## 📝 Introduction

**miniRT** is a 42 School project that implements a minimal ray tracing engine, introducing students to the fundamentals of 3D computer graphics, ray tracing algorithms, and mathematical concepts in rendering.

> "Creating entire worlds with nothing but rays of light."

This project renders 3D scenes described in simple `.rt` files, calculating ray-object intersections and lighting to produce realistic images with depth, shadows, and perspective.

## 🎯 Project Objectives

- Implement a basic ray tracing engine from scratch
- Master 3D vector mathematics and geometric calculations
- Understand light behavior and shading models
- Parse and validate scene description files
- Render 3D primitives (spheres, planes, cylinders)
- Interface with the MiniLibX library for image display
- Optimize rendering algorithms for performance

## 🧩 Project Structure

```
miniRT/
├── inc/                 # Header files
│   └── main.h            # MiniLibX interface declarations
├── src/                 # Source files
│   ├── main.c           # Program entry point
│   ├── parser/          # Scene file parsing
│   ├── render/          # Ray tracing implementation
│   ├── utils/           # Utility functions
│   └── mlx/             # MiniLibX interface
├── scenes/              # Example scene files
└── Makefile             # Compilation instructions
```

## 🛠️ Implementation Details

### **main.c**
Program entry point:

| Function | Description |
|----------|-------------|
| **main** | Validates command-line arguments, initializes the scene, and starts the rendering loop |

### **parser/**
Scene file parsing:

| Function | Description |
|----------|-------------|
| **parse_scene** | Parses the `.rt` file and populates the scene data structure |
| **parse_camera** | Parses camera information from the tokens |
| **parse_light** | Parses light information from the tokens |
| **parse_object** | Parses object information (spheres, planes, cylinders) from the tokens |

### **render/**
Ray tracing implementation:

| Function | Description |
|----------|-------------|
| **render_scene** | Renders the entire scene by casting rays through each pixel |
| **trace_ray** | Traces a ray through the scene and computes the color seen along that ray |
| **intersect_sphere** | Checks for intersection between a ray and a sphere |
| **intersect_plane** | Checks for intersection between a ray and a plane |
| **intersect_cylinder** | Checks for intersection between a ray and a cylinder |

### **utils/**
Utility functions:

| Function | Description |
|----------|-------------|
| **vec3_add** | Adds two 3D vectors |
| **vec3_sub** | Subtracts vector b from vector a |
| **vec3_scale** | Scales a vector by a scalar |
| **vec3_dot** | Computes the dot product of two vectors |
| **vec3_cross** | Computes the cross product of two vectors |
| **error_exit** | Prints an error message and exits the program |

### **mlx/**
MiniLibX interface:

| Function | Description |
|----------|-------------|
| **init_window** | Initializes the window using MiniLibX |
| **put_pixel** | Draws a pixel at the specified coordinates with the given color |
| **display_image** | Displays the rendered image in the window |

## 🧮 The Problem

Ray tracing solves the rendering equation by simulating how light interacts with objects:

- For each pixel, cast a ray from the camera through the pixel into the scene
- Determine which object (if any) the ray intersects first
- Calculate the color at the intersection point based on material properties and light sources
- Account for shadows by casting rays from the intersection point to each light source
- (Optional) Calculate reflections and refractions with recursive ray tracing

## 🎮 Program Usage

```
./miniRT <scene_file.rt>
```

### Scene File Format

Scene files use the `.rt` extension and follow a specific format:

```
# Comment lines start with #

# Ambient lighting
A <intensity> <r,g,b>

# Camera
C <position> <orientation> <FOV>

# Light
L <position> <intensity> <r,g,b>

# Sphere
sp <position> <diameter> <r,g,b>

# Plane
pl <position> <normal> <r,g,b>

# Cylinder
cy <position> <orientation> <diameter> <height> <r,g,b>
```

Example:
```
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L -40,0,30 0.7 255,255,255
sp 0,0,20 20 255,0,0
pl 0,-30,0 0,1,0 0,255,0
cy 50,0,20 0,1,0 14.2 21.42 10,0,255
```

## 💡 Key Features

- **Ray-Object Intersection**: Precise mathematical calculations for determining ray intersections
- **Phong Shading Model**: Realistic lighting with ambient, diffuse, and specular components
- **Multiple Light Sources**: Support for multiple point lights with shadow casting
- **Scene Description Files**: Flexible scene configuration through simple text files
- **3D Primitives**: Support for basic geometric shapes (spheres, planes, cylinders)
- **Camera Configuration**: Adjustable camera position, orientation, and field of view
- **MiniLibX Integration**: Real-time rendering and display using the MiniLibX library

## 🧠 Skills Developed

- 3D vector mathematics and linear algebra
- Ray tracing algorithms and techniques
- Light physics and illumination models
- Geometric calculations for 3D primitives
- File parsing and validation
- Graphics programming with MiniLibX
- Optimization techniques for computational graphics

---

<div align="center">
  
  ### 📊 Project Stats
  
  | Metric | Value |
  |--------|-------|
  | Final Score | 100/100 |
  | Primitives | Spheres, Planes, Cylinders |
  | Lighting Model | Phong Shading |
  | Performance | Optimized ray-object intersections |
  
</div>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Graphics-Ray_Tracing-ff69b4?style=for-the-badge" alt="Ray Tracing">
  <img src="https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white" alt="42">
</p>
