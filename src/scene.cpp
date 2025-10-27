#include "../include/scene.h"

Scene::Scene(Camera camera_value, Shape* shapes_values[3], Ray3f source_value) {
    camera = camera_value;
    for (int i = 0; i < 3; ++i) shapes[i] = shapes_values[i];
    source = source_value;
}

void render(int width, int height, std::string filename) {

}

Camera Scene::getCamera() const {
    return camera;
}

Ray3f Scene::getSource() const {
    return source;
}

Ray3f Scene::getSource() const {
    return source;
}