#include "board.h"
#include "main.h"

Board::Board(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    GLfloat vertex_buffer_data[10000] ;
    GLfloat line_vertex_buffer_data[10000] ;
    int c=0;
    int c1=0;
    float x1,y1=bottom_board/2;
    float w=0.5,h1=0.5,h=0.5;
    height=4*h1;
    width=2*(8)*w;
    ll tot=4*2*(8);
    for (int i = 0; i < 4; ++i)
    {
        x1=left_board;
        for (int j = 0; j < 2*(8); ++j)
        {
            h=h1;
            vertex_buffer_data[c++]=x1*1.0f;
            vertex_buffer_data[c++]=y1*1.0f;
            vertex_buffer_data[c++]=0.0f;
            
            vertex_buffer_data[c++]=x1*1.0f;
            vertex_buffer_data[c++]=(y1-h)*1.0f;
            vertex_buffer_data[c++]=0.0f;
           
            vertex_buffer_data[c++]=(x1+w)*1.0f;
            vertex_buffer_data[c++]=(y1-h)*1.0f;
            vertex_buffer_data[c++]=0.0f;

            vertex_buffer_data[c++]=x1*1.0f;
            vertex_buffer_data[c++]=y1*1.0f;
            vertex_buffer_data[c++]=0.0f;

            vertex_buffer_data[c++]=(x1+w)*1.0f;
            vertex_buffer_data[c++]=y1*1.0f;
            vertex_buffer_data[c++]=0.0f;

            vertex_buffer_data[c++]=(x1+w)*1.0f;
            vertex_buffer_data[c++]=(y1-h)*1.0f;
            vertex_buffer_data[c++]=0.0f;
            x1+=w;
        }
        y1-=h;
    }
    this->bg = create3DObject(GL_TRIANGLES, tot*6, vertex_buffer_data, COLOR_LRED, GL_FILL);
        c=0,c1=0;
    y1=bottom_board/2;
for (int i = 0; i < 4; ++i)
    {
        x1=left_board;
        for (int j = 0; j < 2*(8); ++j)
        {
            h=h1;
            if (j%3==0)
            {
                h+=0.1;
            }
            vertex_buffer_data[c++]=x1*1.0f;
            vertex_buffer_data[c++]=y1*1.0f;
            vertex_buffer_data[c++]=0.0f;
            
            vertex_buffer_data[c++]=x1*1.0f;
            vertex_buffer_data[c++]=(y1-h)*1.0f;
            vertex_buffer_data[c++]=0.0f;
           
            vertex_buffer_data[c++]=(x1+w)*1.0f;
            vertex_buffer_data[c++]=(y1-h)*1.0f;
            vertex_buffer_data[c++]=0.0f;

            vertex_buffer_data[c++]=x1*1.0f;
            vertex_buffer_data[c++]=y1*1.0f;
            vertex_buffer_data[c++]=0.0f;

            vertex_buffer_data[c++]=(x1+w)*1.0f;
            vertex_buffer_data[c++]=y1*1.0f;
            vertex_buffer_data[c++]=0.0f;

            vertex_buffer_data[c++]=(x1+w)*1.0f;
            vertex_buffer_data[c++]=(y1-h)*1.0f;
            vertex_buffer_data[c++]=0.0f;
//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
            line_vertex_buffer_data[c1++]=x1*1.0f;
            line_vertex_buffer_data[c1++]=y1*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;
            
            line_vertex_buffer_data[c1++]=x1*1.0f;
            line_vertex_buffer_data[c1++]=(y1-h)*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;
           
            line_vertex_buffer_data[c1++]=(x1+w)*1.0f;
            line_vertex_buffer_data[c1++]=(y1-h)*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;

            line_vertex_buffer_data[c1++]=x1*1.0f;
            line_vertex_buffer_data[c1++]=(y1-h)*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;

            line_vertex_buffer_data[c1++]=x1*1.0f;
            line_vertex_buffer_data[c1++]=y1*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;

            line_vertex_buffer_data[c1++]=(x1+w)*1.0f;
            line_vertex_buffer_data[c1++]=y1*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;

            line_vertex_buffer_data[c1++]=(x1+w)*1.0f;
            line_vertex_buffer_data[c1++]=(y1-h)*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;

            line_vertex_buffer_data[c1++]=(x1+w)*1.0f;
            line_vertex_buffer_data[c1++]=y1*1.0f;
            line_vertex_buffer_data[c1++]=0.0f;

            x1+=w;
        }
        y1-=h;
    }
    this->object = create3DObject(GL_TRIANGLES, tot*6, vertex_buffer_data, color, GL_FILL);
     this->outline = create3DObject(GL_LINES, tot*8, line_vertex_buffer_data, COLOR_KAALA, GL_FILL);
}

void Board::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bg);
    draw3DObject(this->object);
   // draw3DObject(this->outline);
}

void Board::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
bounding_box_t Board::bounding_box() {
      bounding_box_t b1;
      b1.x=left_board;
      b1.y=bottom_board;
      b1.width=this->width;
      b1.height=this->height;
      return b1;
}
