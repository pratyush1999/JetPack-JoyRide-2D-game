#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y, double radius,  int start_time, color_t color, bool flag) {
    this->position = glm::vec3(x, y, 0.1);
    this->rotation = 10;
    speed = 0.01;
    vspeed=0;
    int n=1000;
    this->start_time=start_time;
    this->flag=flag;
    GLfloat g_vertex_buffer_data[9*n];
int i=0;
double pi=3.14159265358979323846;
double theta=0,angle;
angle=(2*pi)/n;
this->radius=radius;
while(i<9*n)
{
    g_vertex_buffer_data[i++]=0.0f;
    g_vertex_buffer_data[i++]=0.0f;
    g_vertex_buffer_data[i++]=0.0f;
    g_vertex_buffer_data[i++]=cos(theta) * radius;
    g_vertex_buffer_data[i++]=sin(theta) * radius;
    g_vertex_buffer_data[i++]=0.0f;
    theta+=angle;
    g_vertex_buffer_data[i++]=cos(theta) * radius;
    g_vertex_buffer_data[i++]=sin(theta) * radius;
    g_vertex_buffer_data[i++]=0.0f;
}
    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Coin::moveSideways(int f){
    this->position.x+=f*this->speed;
}
void Coin::tick() {
    this->position.x+=this->speed;
    // this->rotation += this->speed;
    // this->position.x -= this->speed;
    // this->position.y -= this->vspeed;
}
void Coin::collide() {
    // this->speed = -this->speed;
     // this->vspeed = 0.01;
}
bounding_ring_t Coin::bounding_ring() {
      bounding_ring_t b1;
      b1.x=this->position.x;
      b1.y=this->position.y;
      b1.radius=this->radius;
      return b1;
}