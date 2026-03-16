# Ray Tracer — PAP Project

A physically-based ray tracer written in C++ with real-time preview via SDL2. Renders a Cornell Box scene featuring reflective spheres, oriented cubes, soft shadows, and recursive mirror reflections.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus) ![SDL2](https://img.shields.io/badge/SDL2-2.x-orange) ![License](https://img.shields.io/badge/license-MIT-green)

---

## Features

- **Ray-object intersection** — Spheres, axis-aligned quads, and arbitrarily oriented cubes
- **Phong-inspired shading** — Ambient + diffuse lighting (Lambertian model)
- **Hard shadows** — Shadow rays cast toward the point light source
- **Recursive reflections** — Up to 5 bounces for mirror-like surfaces
- **Cornell Box scene** — Classic closed room with coloured walls, a reflective sphere, and a rotated blue cube
- **PPM export** — Rendered frame saved to disk as `rendu_final.ppm`
- **SDL2 window** — Live display of the rendered buffer after computation

---

## Project Structure

```
.
├── include/
│   ├── camera.h        # Perspective camera with orthonormal basis
│   ├── cube.h          # Oriented cube (6 Quad faces)
│   ├── hit_info.h      # Intersection record (point, normal, material)
│   ├── material.h      # RGB colour + shininess/reflectivity
│   ├── quad.h          # Bounded planar quad
│   ├── ray3f.h         # Parametric ray  P(t) = O + t·D
│   ├── scene.h         # Scene graph + render loop
│   ├── sdl_helper.h    # SDL2 window & pixel buffer display
│   ├── shape.h         # Abstract base class for all geometry
│   ├── sphere.h        # Sphere with analytic intersection
│   └── vector3f.h      # 3D vector math (dot, cross, normalize…)
│
└── src/
    ├── camera.cpp
    ├── cube.cpp
    ├── main.cpp         # Scene setup entry point
    ├── material.cpp
    ├── quad.cpp
    ├── ray3f.cpp
    ├── scene.cpp        # traceRay / calculateLighting / render
    ├── sdl_helper.cpp
    ├── shape.cpp
    ├── sphere.cpp
    └── vector3f.cpp
```

---

## Dependencies

| Library | Version | Purpose |
|---------|---------|---------|
| SDL2 | 2.x | Window creation & pixel rendering |
| MinGW / g++ | ≥ 9 | C++ compiler (Windows) |

> On Linux/macOS, remove the `-lmingw32 -lSDL2main` flags and adjust the SDL2 include path accordingly.

---

## Build & Run

Place yourself inside the `src/` directory, then run:

```bash
g++ -g -Wall -Wextra -I../include -o prog *.cpp -lmingw32 -lSDL2main -lSDL2
./prog
```

The renderer will print progress to stdout, save `rendu_final.ppm` in the working directory, and open an SDL2 window showing the result. Close the window to exit.

---

## Scene Overview

The default scene (`main.cpp`) constructs a **Cornell Box** (10×10×10 units):

| Object | Type | Material |
|--------|------|----------|
| Floor | Quad | Neutral white |
| Ceiling | Quad | Neutral white |
| Back wall | Quad | Neutral white |
| Left wall | Quad | Red |
| Right wall | Quad | Green |
| Sphere | Sphere r=2 | Mirror (shininess 0.6) |
| Cube | Oriented Cube | Matte blue |

The point light is positioned at `(0, 4.5, 0)`, just below the ceiling, casting hard shadows downward.

---

## Camera & Coordinate System

The engine uses a **right-handed coordinate system**:
- **+X** → screen right
- **+Y** → screen up
- **+Z** → toward the viewer (camera looks toward −Z)

The camera constructs a local orthonormal frame (Right, Up, Forward) at initialisation, enabling correct perspective projection for any look direction.

---

## Rendering Pipeline

```
For each pixel (x, y):
  1. Compute normalised screen coordinates (u, v) ∈ [-1, 1]
  2. Camera::getRay(u, v, aspectRatio) → Ray3f
  3. Scene::traceRay(ray, depth=5)
      ├─ Find closest intersection across all shapes
      ├─ Scene::calculateLighting(hit)
      │     ├─ Ambient term
      │     ├─ Shadow ray test (isInShadow)
      │     └─ Lambertian diffuse (N·L)
      └─ If shininess > 0 → recursive reflection ray
  4. Clamp colour to [0, 1] → store in imageBuffer
```

---

## Extending the Scene

Add any shape to the scene inside `main.cpp` before calling `scene.render()`:

```cpp
// Sphere
scene.addShape(new Sphere(1.5f, Vector3f(0.0f, -3.5f, 0.0f), matMirror));

// Axis-aligned quad (floor, ceiling, wall…)
scene.addShape(new Quad(origin, widthVec, heightVec, material));

// Oriented cube — constructor 1: explicit vectors
scene.addShape(new Cube(center, size, mat, forwardVec, upVec));

// Oriented cube — constructor 2: camera-relative rotations (pitch, yaw)
scene.addShape(new Cube(center, size, mat, cam.getDirection(), pitchRad, yawRad));
```

Materials are defined as `Material(r, g, b, shininess)` with all values in `[0, 1]`. A shininess of `0` gives a fully diffuse surface; `1` gives a perfect mirror.

---

## Authors

- **Jaiel Bilâl**
- **Kalaivaasan Balakumar**

*PAP Project — 2025*
