#ifndef SEGMENT_H
#define SEGMENT_H

#include "main.h"

class Segment
{
public:
    Segment() {}
    Segment(int digit, float x, float y);
    glm::vec3 position;
    bool l[10];
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO* lines[7];
};

#endif // SEGMENT_H