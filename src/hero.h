#include "main.h"

#ifndef HERO_H
#define HERO_H


class Hero {
public:
    Hero() {}
    Hero(double x, double y, color_t color);
        double mycos[500], mysin[500];
    glm::vec3 position;
    ll super;
     double cossa(double x);
     double sinna(double x);
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double yco;
    double bodyL;
    double groundY;
    double haccel;
    double bodyW;
    double legW;
    double jetPackW;
    double jetPackL;
    double legH;
    double neckW;
    double neckL;
    double vspeed;
    double gravity;
    double ringAngle;
    double onRing;
    double ringx;
    double ringy;
    double ring_radius;
    int lives;
    int score;
    int coinsCollected;
    bounding_box_t bounding_torso, bounding_leg;
     void collide();
     void moveSideways(int f);
     void moveVertically(int j);
     pair<bounding_box_t, bounding_box_t> bounding_box();
private:
    VAO *object;
    VAO *jetPack;
};
#endif // HERO_H
