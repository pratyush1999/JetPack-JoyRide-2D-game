#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H

class FireLine {
public:
    FireLine() {}
    FireLine(float x, float y, float angle, double speed, color_t color);
    glm::vec3 position;
    float rotation;
    bool fire;
    double radius;
    double rect_l;
    double rect_w;
    double speed;
    double gravity;
    double groundY;
    double x1,y1;
    float ANGLE;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_line_t bounding_line();
private:
    VAO *object;
      VAO *beam;
};

#endif // FIRELINE_H
