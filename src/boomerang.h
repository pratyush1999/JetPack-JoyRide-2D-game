#include "main.h"

#ifndef boomerang_H
#define boomerang_H

class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, double hspeed, double vspeed, color_t color);
    glm::vec3 position;
    float rotation;
    double width;
    double height;
    double hspeed;
    double vspeed;
    double haccel;
    int timmaB;
    double gravity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
    void tick();
    void move();
private:
    VAO *object;
};

#endif // boomerang_H
