#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0.1);
    this->rotation = 0;
    this->width=0.25;
    this->height=0.25;
    this->used=2;
   static const GLfloat g_vertex_buffer_data[]={
    0.0f, 0.0f, 0.0f,
    this->width , 0.0f, 0.0f,
    this->width , this->height/2, 0.0f,
    this->width , this->height/2, 0.0f,
    this->width , this->height, 0.0f,
    0.0f, this->height, 0.0f,

};
   // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI/180.0f ), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Magnet::tick() {
    // this->rotation += this->speed;
    // this->position.x -= this->speed;
    //this->position.y -= this->vspeed;
}
