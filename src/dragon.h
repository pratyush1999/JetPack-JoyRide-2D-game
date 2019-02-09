#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H

class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y,  double speed, double vspeed ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
     double vspeed;
     double height; 
     double width;
     double gravity;
     double groundY;
     double fire;
     void collide();
     void move();
     bounding_box_t bounding_box();
private:
    VAO *body;
    VAO *wings;
};

#endif // DRAGON_H
