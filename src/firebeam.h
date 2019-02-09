#include "main.h"

#ifndef firebeam_H
#define firebeam_H

class firebeam {
public:
    firebeam() {}
    firebeam(float x, float y, double angle, double speed, color_t color);
    glm::vec3 position;
    float rotation;
    double radius;
    double rect_l;
    double rect_w;
    double speed;
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

#endif // firebeam_H
