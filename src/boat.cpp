#include "boat.h"
#include "main.h"

Ball::Ball(float x, float y,float z, color_t color) {
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
     static const GLfloat vertex_buffer_data2[] = {

            -0.15f,0.25f,0.15f,
            0.15f,0.25f,0.15f,
            -0.15f,0.25f,0.0f,
             0.15f,0.25f,0.15f,
             -0.15f,0.25f,0.0f,
            0.15f,0.25f,0.0f,

     };


    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BLACK,GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_RED,GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_YELLOW,GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
     rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);

}

void Ball::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Ball::jump() {
    if(this->speed!=0)
        this->position.z += this->speed;
    this->speed-=0.2;
    if(this->position.z<=0)
    {
        this->position.z = 0;
        this->speed = 0;
    }
}

bool Ball::detect_collide(bounding_box_t a, bounding_box_t b)
{
    if(abs(a.x-b.x)<=1 && abs(a.y-b.y)<=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y, z= this->position.z;

    bounding_box_t bbox = { x, y,z, 0.4, 0.4 };
    return bbox;
}

