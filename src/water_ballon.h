#include "main.h"

#ifndef WATERBALLOON_H
#define WATERBALLOON_H

class WaterBalloon {
public:
    WaterBalloon() {}
    WaterBalloon(float x, float y, double radius,  double speed, double vspeed ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
     double vspeed;
     double radius;
     double gravity;
     double groundY;
     void collide();
     void move();
     bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // WATERBALLOON_H
