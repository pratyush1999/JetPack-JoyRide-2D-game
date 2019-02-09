#include "segment.h"
#include "main.h"

Segment::Segment(int digit, float x, float y)
{
    this->position = glm::vec3(x, y, 0.3);
    for (int i = 0; i < 8; i++) l[i] = false;
    switch (digit) {
    case 0:
        l[1] = l[2] = l[3] = l[4] = l[5] = l[6] = true;
        break;
    case 1:
        l[2] = l[3] = true;
        break;
    case 2:
        l[1] = l[2]  = l[4] = l[5] = l[7]= true;
        break;
    case 3:
        l[1] = l[2] = l[3] = l[4] = l[7]=true;
        break;
    case 4:
         l[2] = l[3] = l[6] = l[7] =true;
        break;
    case 5:
        l[1]  = l[3] = l[4] = l[6] = l[7]= true;
        break;
    case 6:
        l[1] = l[3] = l[4] = l[5] = l[6] = l[7]=true;
        break;
    case 7:
        l[1] = l[2] = l[3] = true;
        break;
    case 8:
        l[1] = l[2] = l[3]  = l[4] = l[5] = l[6]  = l[7]= true;
        break;
    case 9:
        l[1] = l[2]= l[3] = l[4] = l[6] = l[7] = true;
        break;
    }
    const GLfloat endpoints[][4] = {
        {0, 0.2, 0.1, 0.2},
        {0.1, 0.2, 0.1, 0.1},
        {0.1, 0.1, 0.1, 0},
        {0.1, 0,  0, 0},
        {0, 0,  0, 0.1},
        {0, 0.2,  0, 0.1},
        {0, 0.1,  0.1, 0.1},
    };
    GLfloat line_vertex_buffer_data[100];
    for (int i = 0; i < 7; i++) {
        if (l[i+1])
        {
              int k=0;
              line_vertex_buffer_data[k++]=x+endpoints[i][0];
               line_vertex_buffer_data[k++]=y+endpoints[i][1];
               line_vertex_buffer_data[k++]=0.0f;
                line_vertex_buffer_data[k++]=x+endpoints[i][2];
                line_vertex_buffer_data[k++]=y+endpoints[i][3];
                line_vertex_buffer_data[k++]=0.0f;
              this->lines[i]=create3DObject(GL_LINES, 2, line_vertex_buffer_data, COLOR_KAALA, GL_FILL);
        }
    }
}

void Segment::draw(glm::mat4 VP) {
      Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for (int i = 0; i < 7; i++) 
        {
            if(l[i+1])
             draw3DObject(this->lines[i]);
        }
}