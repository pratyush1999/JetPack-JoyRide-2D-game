#include "main.h"

#ifndef magnet_H
#define magnet_H

class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double width;
    int used;
    double height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // magnet_H
