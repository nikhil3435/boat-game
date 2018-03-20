#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    bool detect_collide(bounding_box_t  a,bounding_box_t b);
    bounding_box_t bounding_box();
private:
    VAO *object1,*object2;
};

#endif // BALL_H
