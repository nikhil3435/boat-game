#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed=0;
    //speedy=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.125f,-0.125f,-0.25f, // triangle 1 : begin
        -0.25f,-0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f, // triangle 1 : end
        0.125f, 0.125f,-0.25f, // triangle 2 : begin
        -0.125f,-0.125f,-0.25f,
        -0.125f, 0.125f,-0.25f, // triangle 2 : end
        0.25f,-0.25f, 0.25f,
        -0.125f,-0.125f,-0.25f,
        0.125f,-0.125f,-0.25f,
        0.125f, 0.125f,-0.25f,
        0.125f,-0.125f,-0.25f,
        -0.125f,-0.125f,-0.25f,
        -0.125f,-0.125f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.125f, 0.125f,-0.25f,
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        -0.125f,-0.125f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.125f,-0.125f,-0.25f,
        0.125f, 0.125f,-0.25f,
        0.125f,-0.125f,-0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.125f, 0.125f,-0.25f,
        -0.125f, 0.125f,-0.25f,
        0.25f, 0.25f, 0.25f,
        -0.125f, 0.125f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f
        /*0.24, 0.15,0.67,
              0.14, -0.15,0.5,
              0.14, -0.15, -0.5,

              0.24, 0.15,0.67,
              0.14, -0.15, -0.5,
              0.24, 0.15, -0.5,

              -0.14, -0.15, -0.5,
              -0.24, 0.15, -0.67,
               0.14, -0.15, -0.5,

              -0.24, 0.15, -0.67,
              0.14, -0.15, -0.5,
              0.24, 0.15, -0.67,

              -0.24, 0.15, -0.67,
              -0.14, -0.15, -0.5,
              -0.24, 0.15, 0.67,

              -0.14, -0.15, -0.5,
              -0.24, 0.15, 0.67,
              -0.14, -0.15,0.5,

              -0.24, 0.15, 0.67,
              -0.14, -0.15,0.5,
              0.14, -0.15,0.5,

              -0.24, 0.15, 0.67,
              0.14, -0.15,0.5,
              0.24, 0.15, 0.67,

              0.24, 0.15, 0.67,
              0.24, 0.15, -0.67,
              -0.24, 0.15, -0.67,

              0.24, 0.15, 0.67,
              -0.24, 0.15, -0.67,
              -0.24, 0.15, 0.67,

              -0.14, -0.15,0.5,
              0.14, -0.15,0.5,
              -0.14, -0.15, -0.5,

              0.14, -0.15,0.5,
              -0.14, -0.15, -0.5,
              0.14, -0.15, -0.5,*/
    };
     static const GLfloat vertex_buffer_data1[] = {

             0.0f,-0.15f,0.25f,
             0.0f,0.15f,0.25f,
             0.0f,0.15f,0.80f,

};


    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_VIOLET,GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_PINK,GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Enemy::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Enemy::tick() {
    if(this->position.y < 2 ){
        this->position.y += 75;
        this->position.x += 3;
    }
    else if(this->position.x > -75 && this->position.x < 75 ){
        this->position.y -= 0.01;
        this->position.x -= 0.01;

    }
    else{
        this->position.x += 15;
    }



    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y, z= this->position.z;

    bounding_box_t bbox = { x, y,z, 0.4, 0.4 };
    return bbox;
}

