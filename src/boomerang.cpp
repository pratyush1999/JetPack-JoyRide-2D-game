#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y, double hspeed, double vspeed, color_t color) {
    this->position = glm::vec3(x, y, 0.1);
    this->rotation = 0;
    this->width=0.25;
    this->height=0.10;
    this->vspeed=0.05;
    this->hspeed=0.05;
    this->gravity=-0.001;
    this->haccel=-0.001;
    this->timmaB=0;
        //this->gravity=0;
    static const GLfloat g_vertex_buffer_data[]={
    0.0f, 0.0f, 0.0f,
    this->width , 0.0f, 0.0f,
    this->width , this->height/2, 0.0f,
    this->width , this->height/2, 0.0f,
    this->width , this->height, 0.0f,
    0.0f, this->height, 0.0f,
};
    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Boomerang::tick() {
    // this->rotation += this->speed;
    // this->position.x += this->speed;
    // this->position.y += this->vspeed;
}
void Boomerang::move(){
    timmaB++;
    if ((((float)this->hspeed+(float)this->haccel)*this->hspeed)<=0)
    {
      this->rotation=180.0f;
        this->hspeed=-0.1*(this->hspeed/absol(this->hspeed));
        this->haccel=-this->haccel;
    }
    if ((float)(this->position.y+this->vspeed)<=bottom_board/2)
    {
        this->position.y=bottom_board/2-this->vspeed+0.01;
        this->vspeed=-this->vspeed;
    }
    // if (this->position.x<=left_board)
    // {
    //     this->hspeed=0.25;
    // }
    // if (((this->hspeed+this->haccel)*this->hspeed)<=0)
    // {
    //      this->hspeed=-0.2*(this->hspeed/absol(this->hspeed));
    //      this->haccel=-this->haccel;
    // }
   this->hspeed+=this->haccel;
    this->position.x+=this->hspeed;
    this->vspeed+=this->gravity;
      this->position.y+=this->vspeed;
        // if(this->position.y<=bottom_board/2)
        //    this->position.x=-1000;
}
bounding_box_t Boomerang::bounding_box() {
      bounding_box_t b1;
      b1.x=this->position.x;
      b1.y=this->position.y;
      b1.width=this->width;
      b1.height=this->height;
      return b1;
}
