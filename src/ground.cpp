#include "ground.h"
#include "main.h"

Ground::Ground(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.00;
    static const GLfloat vertex_buffer_data[] = {
        -150.0, 100.0, 0, // vertex 1
        -150.0, -100.0, 0, // vertex 2
        150.0,  -100.0, 0, // vertex 3

        150.0,  -100.0, 0, // vertex 3
        150.0, 100.0, 0, // vertex 4
        -150.0, 100.0, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_WATER, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ground::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Ground::tick() {
    //this->position.x -= speed;
    // this->position.y -= speed;
    //this->position.z -= speed;
}

/*bool Ground::detect_collide(bounding_box_t a, bounding_box_t b)
{
    if(abs(a.x-b.x)<=1 && abs(a.y-b.y)<=1 && abs(a.z-b.z)<=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}*/
bounding_box_t Ground::bounding_box() {
    float x = this->position.x, y = this->position.y, z= this->position.z;

    bounding_box_t bbox = { x, y,z, 0.4, 0.4 };
    return bbox;
}
