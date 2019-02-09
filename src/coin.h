#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin {
public:
    Coin() {}
    Coin(float x, float y, double radius, int start_time, color_t color, bool flag);
    glm::vec3 position;
    float rotation;
    bool flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int start_time;
    double speed;
     double vspeed;
     double radius;
     void collide();
     bounding_ring_t bounding_ring();
     void moveSideways(int f);
private:
    VAO *object;
};

#endif // COIN_H
