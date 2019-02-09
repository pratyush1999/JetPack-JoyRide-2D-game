#include "projectile_coin.h"
#include "main.h"

Projectile_Coin::Projectile_Coin( float x, float y, double radius, double speed, double vspeed , color_t color, double factor) {
    this->position = glm::vec3(x, y, 0.1);
    this->rotation = 0;
    this->speed = speed;
    this->vspeed= vspeed;
    this->gravity=0.001;
    this->factor=factor;
    this->groundY=bottom_board/2;
    int n=1000;
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
    this->object = create3DObject(GL_TRIANGLES, this->factor*n, g_vertex_buffer_data, color, GL_FILL);
}

void Projectile_Coin::draw(glm::mat4 VP) {
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

void Projectile_Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Projectile_Coin::tick() {
    // this->position.x+=this->speed;
    // this->rotation += this->speed;
    // this->position.x -= this->speed;
    // this->position.y -= this->vspeed;
}
void Projectile_Coin::collide() {
    // this->speed = -this->speed;
     // this->vspeed = 0.01;
}
void Projectile_Coin::move(){
    this->position.x+=this->speed;
    this->vspeed-=this->gravity;
    this->position.y += this->vspeed;
    if (this->position.y<=groundY)
    {
        this->position.y=-1000;
    }
}
bounding_box_t Projectile_Coin::bounding_box() {
      bounding_box_t b1;
      b1.x=this->position.x-this->radius;
      b1.y=this->position.y-this->radius;
      b1.width=2*this->radius;
      b1.height=2*this->radius;
      return b1;
}