#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    void jump();

    bool detect_collide(bounding_box_t  a,bounding_box_t b);
    bounding_box_t bounding_box();
private:
    VAO *object1,*object2,*object3;
};

#endif // BALL_H
