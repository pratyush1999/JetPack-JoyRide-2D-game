#include "fireLine.h"
#include "main.h"

FireLine::FireLine(float x, float y, float ANGLE, double speed, color_t color) {
    this->position = glm::vec3(x, y, 0.1);
    this->rotation = ANGLE;
    GLfloat g_vertex_buffer_data[100000];
        this->ANGLE=ANGLE;
        this->fire=1;
   x1=0.5;
  y1=0;
    double theta=0,angle;
    int n=100;
    long double pi=3.14159265359;
   int i=0;
  angle=(2*pi)/n;
  radius=0.1;
  this->speed=speed;
  this->groundY=bottom_board/2;
  this->gravity=-0.001;
//circles at ends
for(int iter=1;iter<=2;++iter)
{
 theta=0;
  while(i<9*n*iter)
{
    g_vertex_buffer_data[i++]=0.0f+x1;
    g_vertex_buffer_data[i++]=0.0f+y1;
    g_vertex_buffer_data[i++]=0.0f;
    g_vertex_buffer_data[i++]=cos(theta) * radius+x1;
    g_vertex_buffer_data[i++]=sin(theta) * radius+y1;
    g_vertex_buffer_data[i++]=0.0f;
    theta+=angle;
    g_vertex_buffer_data[i++]=cos(theta) * radius+x1;
    g_vertex_buffer_data[i++]=sin(theta) * radius+y1;
    g_vertex_buffer_data[i++]=0.0f;
}
x1=-x1,y1=-y1;
}
   // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
g_vertex_buffer_data[i++]=x1;
g_vertex_buffer_data[i++]=y1;
g_vertex_buffer_data[i++]=0.0f;
g_vertex_buffer_data[i++]=x1;
g_vertex_buffer_data[i++]=y1+0.01f;
g_vertex_buffer_data[i++]=0.0f;
g_vertex_buffer_data[i++]=-x1;
g_vertex_buffer_data[i++]=y1;
g_vertex_buffer_data[i++]=0.0f;
g_vertex_buffer_data[i++]=-x1;
g_vertex_buffer_data[i++]=y1;
g_vertex_buffer_data[i++]=0.0f;
g_vertex_buffer_data[i++]=-x1;
g_vertex_buffer_data[i++]=y1+0.01f;
g_vertex_buffer_data[i++]=0.0f;
g_vertex_buffer_data[i++]=x1;
g_vertex_buffer_data[i++]=y1+0.01f;
g_vertex_buffer_data[i++]=0.0f;
   this->object = create3DObject(GL_TRIANGLES, 54*n+6, g_vertex_buffer_data, color, GL_FILL);
   x1=0.5*cos(ANGLE*pi/180);
   y1=0.5*sin(ANGLE*pi/180);
}

void FireLine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI/180.0f ), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void FireLine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void FireLine::tick() {
        this->speed+=this->gravity;
  if (this->position.y+this->speed>=top_board||this->position.y+this->speed<=this->groundY)
      {
        this->speed=-this->speed;
      }
      this->position.y += this->speed;
}
bounding_line_t FireLine::bounding_line() {
      bounding_line_t b1;
      b1.x1=-x1+this->position.x;
      b1.x2=x1+this->position.x;
      b1.y1=-y1+this->position.y;
      b1.y2=y1+this->position.y;
      return b1;
}