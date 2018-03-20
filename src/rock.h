#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    //void detect_collide(bounding_box_t a, bounding_box_t b);
    double speed;
    bool detect_collide(bounding_box_t  a,bounding_box_t b);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
