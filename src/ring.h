#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {
public:
    Ring() {}
    Ring(float x, float y, double radius, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
     double vspeed;
     double radius;
     void collide();
     void moveSideways(int f);
     bounding_box_t bounding_ring();
private:
    VAO *object;
};

#endif // RING_H
