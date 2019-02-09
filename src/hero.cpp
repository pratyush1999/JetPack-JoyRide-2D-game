#include "hero.h"
#include "main.h"

Hero::Hero(double x, double y, color_t color) {
    this->rotation = 0;
    this->speed = 0.02;
    this->vspeed=0;
    this->bodyW=1.0f/4;
    this->bodyL=1.0f/4;
    this->legW=bodyW/4;
    this->legH=bodyL/3;
    this->yco=y+this->legH;
    this->super=-1;
    //y=y+this->legH;
    this->position = glm::vec3(x, y+this->legH, 0.2);
    this->haccel=0;
    neckW=bodyW/4;
    neckL=bodyL/6;
    jetPackW=bodyW/4;
    jetPackL=bodyL/1.5;
    this->groundY=(screen_center_y - 4)/2.0f;
    gravity=0.009;
    score=0;
    coinsCollected=0;
    lives=1000;
    this->ringAngle=0;
    this->onRing=0;
    this->ringx=0;
    this->ringy=0;
    this->ring_radius=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
   GLfloat vertex_buffer_data[] = {
        0.0f, bodyL, 0.0f, //  torso
        0.0f, 0.0f, 0.0f,
        bodyW, 0.0f, 0.0f,
        bodyW, bodyL, 0.0f,
        0.0f, bodyL, 0.0f,
        bodyW, 0.0f, 0.0f,

        legW, 0.0f, 0.0f,   //leg
        2*legW, -legH, 0.0f,
        legW, -legH, 0.0f,
        legW, 0.0f, 0.0f,
        2*legW, 0.0f, 0.0f,
        legW, -legH, 0.0f,

        legW+1.5*legW, 0.0f, 0.0f,   //leg
        2*legW+1.5*legW, -legH, 0.0f,
        legW+1.5*legW, -legH, 0.0f,
        legW+1.5*legW, 0.0f, 0.0f,
        2*legW+1.5*legW, 0.0f, 0.0f,
        legW+1.5*legW, -legH, 0.0f,

        // legW, bodyL, 0.0f,    //neck
        // legW+neckW, bodyL, 0.0f,
        // legW, bodyL+neckL, 0.0f,
        // legW+neckW, bodyL, 0.0f,   
        // legW+neckW, bodyL+neckL, 0.0f,
        // legW, bodyL+neckL, 0.0f,   
    };
        this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
     GLfloat vertex_buffer_data_jetPack[] = {

        -jetPackW, jetPackL+jetPackL/2, 0.0f, //  jetPack
        0.0f, 0.0f+jetPackL/2, 0.0f,
        -jetPackW, 0.0f+jetPackL/2, 0.0f,
       -jetPackW, jetPackL+jetPackL/2, 0.0f,
        0.0f, 0.0f+jetPackL/2, 0.0f,
        0.0f, jetPackL+jetPackL/2, 0.0f,
    };
    this->jetPack = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_jetPack, COLOR_KAALA, GL_FILL);
}
double Hero::cossa(double x)
{
  double pi=3.14159265359;
  x=x* pi/180;
  double ret=1;
  double z=1;
  int y=1;
  int l=1;
  for (int i = 0; i < 10; ++i)
  {
      z=z*x*x;
      y=y*l*(l+1);
      if(i%2!=0)
      ret+=z/y;
    else
      ret-=z/y;
  }
  //return 1 - (x*x)/2 + (x*x*x*x)/24 -(x*x*x*x*x*x)/720 + (x*x*x*x*x*x*x*x)/40320;   
  int i, n=10;
  double sum=1, t=1;  
    for(i=1;i<=n;i++)
    {
        t=t*(-1)*x*x/(2*i*(2*i-1));
        sum=sum+t;
    }
    return sum;
}
double Hero::sinna(double x)
{
  double pi=3.14159265359;
  x=x* pi/180;
  //return x - (x*x*x)/6 + (x*x*x*x*x)/120 - (x*x*x*x*x*x*x)/5040 +(x*x*x*x*x*x*x*x*x)/362880;
  int i, n;
    double sum, t;
    n=10;
    t=x;
    sum=x;
     
    /* Loop to calculate the value of Sine */
    for(i=1;i<=n;i++)
    {
        t=(t*(-1)*x*x)/(2*i*(2*i+1));
        sum=sum+t;
    }
    return sum;
     
}
void Hero::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
     if (this->onRing==1)
        {  
            double ring_rad=this->ring_radius-this->bodyL;
          this->position.x= this->ringx-ring_rad*cossa(this->ringAngle);
          this->position.y= this->ringy+ring_rad*sinna(this->ringAngle);
         this->rotation=90-this->ringAngle;
          this->ringAngle+=1;
        }
      //  this->rotation=90;
      glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        if (this->ringAngle==180.0f)
            {
              this->position.x+=2*this->ring_radius;
              this->onRing=0;
              this->ringAngle=0;
              this->rotation=0;
           }
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->jetPack);
}

void Hero::set_position(float x, float y) {
   // this->position = glm::vec3(x, y, 0);
}
void Hero::moveSideways(int f){
  if ((float)this->position.x+f*this->speed>screen_center_x)
  {
     this->position.x=screen_center_x-f*this->speed;
     return ;
  }
  if((float)this->position.x+f*this->speed<left_board)
  {
    this->position.x=left_board-f*this->speed;
    return ;
  }
   if(this->onRing==0)
    this->position.x+=f*this->speed;
  if (this->position.x>screen_center_x) 
  {
    this->position.x=screen_center_x;
  }
  if (this->position.x<left_board)
  {
    this->position.x=left_board;
  }
}
void Hero::tick() {
    // this->rotation += this->speed;
    // this->position.x -= this->speed;
    //this->position.y -= this->vspeed;
}
void Hero::moveVertically(int j)
{
  if (this->position.y-this->legH<=this->groundY)
  {
    this->position.y=this->groundY+this->legH;
  }
  if (this->position.y+this->bodyL>=top_board)
  {
    this->position.y=top_board-this->bodyL;
  }
  if(this->onRing==1)
  return ;
  if (j==0&&(float)this->position.y-(float)this->legH<=(float)groundY)
  {
    this->position.y=this->legH+groundY;
    this->vspeed=0;
    return ;
  }        
  this->vspeed-=this->gravity;
   if (j==1)
    {
        // if (this->vspeed<=0)
        // {
        //   this->vspeed+=0.01;
        // }else
        this->vspeed+=0.01;
    }
    this->position.y += this->vspeed;
}
void Hero::collide() {
    // this->speed = -this->speed;
    // this->vspeed = 0.01;
}
pair<bounding_box_t, bounding_box_t> Hero::bounding_box() {
      bounding_box_t b1, b2;
      b1.x=this->position.x;
      b1.y=this->position.y;
      b1.width=this->bodyW;
      b1.height=this->bodyL;
      b2.x=b1.x+legW;
      b2.y=b1.y-legH;
      b2.width=this->legW;
      b2.height=this->legH;
      return make_pair(b1,b2);
}
