#ifndef SCENE_H
#define SCENE_H

#include <string>

#include "camera.h"
#include "shape.h"
#include "ray3f.h"

class Scene {
private:
    Camera camera;
    Shape* shapes[3];
    Ray3f source;
    

public:
    Scene(Camera camera_value, Shape* shapes_values[3], Ray3f source_value);
    void render(int width, int height, std::string filename);
    Camera getCamera() const;
    Shape* getShapes() const;
    Ray3f getSource() const;
};

#endif