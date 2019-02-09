#ifndef MAIN_H
#define MAIN_H
#define GLM_ENABLE_EXPERIMENTAL
 #define right_board  screen_center_x + 4 / screen_zoom
#define left_board screen_center_x - 4 / screen_zoom
#define top_board screen_center_y + 4 / screen_zoom
#define bottom_board screen_center_y - 4 / screen_zoom
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};
struct bounding_line_t {
    float x1;
    float y1;
    float x2;
    float y2;
};
struct bounding_ring_t {
    float x;
    float y;
    double radius;
};
ld absol(ld x);
bool detect_collision(bounding_box_t a, bounding_box_t b);
bool detect_collision_coin(bounding_box_t a, bounding_ring_t b);
bool detect_collision_line(bounding_box_t a, bounding_line_t b);
bool checkSameSide(pair<ld ,ld>p, bounding_line_t b);
extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();
void print_score(glm::mat4 VP);

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_KAALA;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_LIGHT_BLUE ;
extern const color_t COLOR_LRED ;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_BGREEN ;
extern const color_t COLOR_DBLUE;
extern const color_t COLOR_HRED;
extern const color_t COLOR_ICY;
extern const color_t COLOR_OYELLOW;
#endif
