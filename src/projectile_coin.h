#include "main.h"

#ifndef PROJECTILE_COIN_H
#define PROJECTILE_COIN_H

class Projectile_Coin {
public:
    Projectile_Coin() {}
    Projectile_Coin(float x, float y, double radius,  double speed, double vspeed ,color_t color, double factor);
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
     double factor;
     void collide();
     void move();
     bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PROJECTILE_COIN_H
