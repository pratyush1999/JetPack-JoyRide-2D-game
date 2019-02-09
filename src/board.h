#include "main.h"

#ifndef BOARD_H
#define BOARD_H


class Board {
public:
    Board() {}
    Board(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float width;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *outline;
    VAO* bg;
};

#endif // BOARD_H
