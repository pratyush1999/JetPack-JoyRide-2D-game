#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y, double speed, double vspeed , color_t color) {
    this->position = glm::vec3(x, y, 0.2);
    this->rotation = 0;
    this->speed = speed;
    this->vspeed= vspeed/10;
    this->gravity=0.001;
    this->groundY=bottom_board/2;
    this->fire=1;
    this->width=0.3/2*10.0f;
    this->height=2.0f;
static const GLfloat body_vertex_buffer_data[]={
 (0.1f/2)*10, 1.0f, 0.0f,
    (0.1f)*10, 1.0f, 0.0f,
    (0.1f/2+0.1f/4)*10, 2.0f, 0.0f,

    (0.1f/2)*10, 1.0f, 0.0f,
    (0.1f)*10, 1.0f, 0.0f,
     (0.1f)*10, 3.0f/2, 0.0f,

      (0.1f/2)*10, 1.0f, 0.0f,
           (0.1f)*10, 3.0f/2, 0.0f,
            (0.1f/2)*10, 3.0f/2, 0.0f,
};
static const GLfloat wing_vertex_buffer_data[]={
   

    (0.1f)*10, 1.0f, 0.0f,
    (0.1f+0.1f/2)*10, 2.0f, 0.0f,
    (0.1f+0.1f/2)*10, 0.0f, 0.0f,

    (0.1f/2)*10, 1.0f, 0.0f,
    (0)*10, 2.0f, 0.0f,
    (0)*10, 0.0f, 0.0f,
};
    this->body = create3DObject(GL_TRIANGLES, 9, body_vertex_buffer_data, COLOR_BGREEN, GL_FILL);
    this->wings = create3DObject(GL_TRIANGLES, 6, wing_vertex_buffer_data, COLOR_DBLUE, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body);
    draw3DObject(this->wings);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Dragon::tick() {
    // this->position.x+=this->speed;
    // this->rotation += this->speed;
    // this->position.x -= this->speed;
    // this->position.y -= this->vspeed;
}
void Dragon::collide() {
    // this->speed = -this->speed;
     // this->vspeed = 0.01;
}
void Dragon::move(){
    this->position.x+=this->speed;
    this->vspeed-=this->gravity;
    if (this->position.y+this->vspeed<=groundY||this->position.y+this->vspeed>=top_board)
    {
       this->vspeed=-this->vspeed;
    }
    this->position.y+=this->vspeed;
}
bounding_box_t Dragon::bounding_box() {
      bounding_box_t b1;
      b1.x=this->position.x;
      b1.y=this->position.y;
      b1.width=this->width;
      b1.height=this->height;
      return b1;
}