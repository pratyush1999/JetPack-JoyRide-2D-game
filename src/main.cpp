#include "main.h"
#include "timer.h"
#include "ball.h"
#include "board.h"
#include "hero.h"
#include "coin.h"
#include "fireLine.h"
#include "magnet.h"
#include "boomerang.h"
#include "ring.h"
#include "water_ballon.h"
#include "dragon.h"
#include "projectile_coin.h"
#include "segment.h"
using namespace std;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
/**************************
* Customizable functions *
**************************/
    int inputtta=1;
Board ball1;
Board ball2;
Board ball3;
Hero hero;
Coin coin1;
Dragon dragon;
vector<WaterBalloon>fireballs;
vector<Boomerang>boomerangs;
vector<Projectile_Coin> projectile_coins;
vector<FireLine>firelines;
vector<WaterBalloon>waterballons;
vector<Coin>coins;
vector<Ring>rings;
vector<Magnet>magnets;
Magnet magnet;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
Timer t60(1.0 / 60);
int timma=0;
double mycos[600], mysin[600];
void print_score(glm::mat4 VP)
{
    int s=hero.lives;
    int c=hero.score;
    vector<ll>digs;
    c=max(c, 0);
    s=max(s, 0);
    if (s==0)
    {
        digs.pb(0);
    }
    while(s>0)
    {
        digs.pb(s%10);
        s/=10;
    }
   reverse(digs.begin(), digs.end());
    Segment seg;
    float x;
    x=0;
    for(auto d:digs)
    {
        seg=Segment(d, x+=0.1, 1.8);
        seg.draw(VP);
    }
    digs.clear();
    if (c==0)
    {
        digs.pb(0);
    }
    while(c>0)
    {
        digs.pb(c%10);
        c/=10;
    }
    reverse(digs.begin(), digs.end());
     x=0;
    for(auto d:digs)
    {
        seg=Segment(d, x+=0.1, 1.6);
        seg.draw(VP);
    }
}
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
   ball1.draw(VP);
   ball2.draw(VP);
   ball3.draw(VP);
 hero.draw(VP);

 for(auto &f:firelines)
    f.draw(VP);
for(auto &boomerang: boomerangs)
    boomerang.draw(VP);
    for(auto &r:rings)
        r.draw(VP);
    for(auto &y:coins)
        {
            y.draw(VP);
        }
    for(auto &w: waterballons)
        w.draw(VP);
     for(auto &f: fireballs)
        f.draw(VP);
   for(auto &m:magnets)
   {
    
        m.draw(VP);
     m.used--;
   }
   for(auto &m:projectile_coins)
   {
     m.draw(VP);
   }
   dragon.draw(VP);
   print_score(VP);
}

void tick_input(GLFWwindow *window) 
{
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int jump=glfwGetKey(window, GLFW_KEY_SPACE);
    int f=0;
    if (left) {
       f=-1;
    }
    if(right){
        f=1;
    }
    if (hero.super!=-1&&inputtta>0)
    {
        if ((timma-hero.super)>=500)
        {
            hero.super=-1;
        }
        else
        {
            f=10;
        }
    }
    if (hero.position.x+f*hero.speed<=screen_center_x&&hero.position.x+f*hero.speed>left_board)
       {
            hero.moveSideways(f);
       }
       else if (hero.onRing==0)
        {
            for(auto &y:coins)
            {
                y.moveSideways(-f);
            }
                for(auto &f1:firelines)
                    f1.position.x-=f*0.01;
                for(auto &boomerang: boomerangs)
                boomerang.position.x-=f*0.01;
                for(auto &r:rings)
                    r.position.x-=f*0.01;
                for(auto &y:coins)
                    {
                        y.position.x-=f*0.01;
                    }
                for(auto &w: waterballons)
                     w.position.x-=f*0.01;
                for(auto &f1: fireballs)
                    f1.position.x-=f*0.01;
            for(auto &m:magnets)
                {
    
                    m.position.x-=f*0.01;
                    m.used--;
                }
            for(auto &m:projectile_coins)
                {
                    m.position.x-=f*0.01;
                }
                dragon.position.x-=f*0.01;
        }
    if (hero.super!=-1&&inputtta>0)
    {
        return ;
    }
    if (glfwGetKey(window, GLFW_KEY_J))
    {
        waterballons.pb(WaterBalloon(hero.position.x+hero.bodyW+hero.legW, hero.position.y+hero.bodyW+hero.legW, 0.1,  0.05,  0.05, COLOR_BLUE));
    }
    for(auto &w: waterballons)
        w.move();
    for(auto &w: fireballs)
        w.move();
    for(auto &m:projectile_coins)
   {
     m.move();
   }
    hero.moveVertically(jump);
    pair<bounding_box_t, bounding_box_t>p=hero.bounding_box();
    bounding_box_t groundKa=ball1.bounding_box();
    if (detect_collision(p.ss,groundKa))
    {
        hero.position.y=hero.groundY+hero.legH;
    }
    for(auto &boomerang: boomerangs)
    {
        if (detect_collision(p.ff, boomerang.bounding_box())||detect_collision(p.ss, boomerang.bounding_box()))
        {
         if (hero.onRing==0)
            {
                hero.lives--;
            }
            boomerang.position.y=-1000;
        //exit(0);
        }
    }   
    if (hero.position.y+hero.bodyL+hero.neckL>top_board)
    {
        hero.position.y=top_board-hero.bodyL-hero.neckL;
    }
     
    for(auto &m:magnets)
    {
        if (m.position.x>hero.position.x&&m.position.y==hero.position.y)
        {
            //m.used--;
            if (hero.position.x+0.1<screen_center_x&&hero.position.x+0.1>left_board)
            {
                if (hero.onRing==0)
                  hero.position.x+=0.1;
            }
            else if (hero.onRing==0)
            {
                int f=10;
               for(auto &y:coins)
            {
                y.moveSideways(-0.1);
            }
                for(auto &f1:firelines)
                    f1.position.x-=f*0.01;
                for(auto &boomerang: boomerangs)
                boomerang.position.x-=f*0.01;
                for(auto &r:rings)
                    r.position.x-=f*0.01;
                for(auto &y:coins)
                    {
                        y.position.x-=f*0.01;
                    }
                for(auto &w: waterballons)
                     w.position.x-=f*0.01;
                for(auto &f1: fireballs)
                    f1.position.x-=f*0.01;
            for(auto &m:projectile_coins)
                {
                    m.position.x-=f*0.01;
                }
                dragon.position.x-=f*0.01;
            }
                    m.position.y=-1000;
        }
        //m.position.x-=1000;
    }
         for(auto &y:coins)
            {
                if (detect_collision_coin(p.ff, y.bounding_ring())||detect_collision_coin(p.ss, y.bounding_ring()))
                {
                    y.position.x=-10000;
                    if (hero.onRing==0)
                    {
                      hero.score+=1;
                    }
                    if (y.flag)
                    {
                        hero.super=timma;
                    }
                }
            }
        for(auto &w: projectile_coins)
          {
             if (detect_collision(w.bounding_box(), p.ff)||detect_collision(w.bounding_box(), p.ss))
             {
                if (hero.onRing==0)
                {
                        if (w.factor==2)
                        {
                             hero.lives+=4;
                        }else
                        hero.score+=4;
                    w.position.y=-1000;
                }
            
             }
          }
          for(auto &w: fireballs)
          {
             if (detect_collision(w.bounding_box(), p.ff)||detect_collision(w.bounding_box(), p.ss))
             {
                 if (hero.onRing==0)
                    w.position.y=-1000;
                // exit(0);
             }
          }
          
        for(auto &w: waterballons)
        {
            for(auto &f:firelines)
            {
                if (detect_collision_line(w.bounding_box(), f.bounding_line() ))
                {
                    f.fire=0;
                    f.position.y=-100;
                    w.position.y=-1000;
                }
            }
            if (detect_collision(w.bounding_box(), dragon.bounding_box() ))
            {
                dragon.fire=0;
                dragon.speed=0;
                dragon.vspeed=0;
                w.position.y=-1000;
            }
        }
        if (dragon.fire==1&&timma%20==1)
        {
            double speed=0.03, vspeed=0.05;
            if(hero.position.x<dragon.position.x)
                speed=-speed;
            if(hero.position.y<dragon.position.y)
                vspeed=-vspeed;
            fireballs.pb(WaterBalloon(dragon.position.x+dragon.width/2, dragon.position.y+dragon.height, 0.1, speed, vspeed, COLOR_ICY));
        }
    if (dragon.fire==1&&(detect_collision(p.ff, dragon.bounding_box())||detect_collision(p.ss, dragon.bounding_box())))
    {
         if (hero.onRing==0)
             {
                hero.lives--;
                dragon.speed=0;
                dragon.vspeed=0;
            }
        //exit(0);
    }
    for(auto &f:firelines)
    {
        if (f.fire==1)
        {
             if (detect_collision_line(p.ff, f.bounding_line())||detect_collision_line(p.ss, f.bounding_line()))
             {
                 if (hero.onRing==0)
                    {
                        f.position.y=-1000;
                        hero.lives--;
                    }
                    //exit(0);
             }
        }
    }
    
    for(auto &ring: rings)
    {
        if (detect_collision(p.ff, ring.bounding_ring())||detect_collision(p.ss, ring.bounding_ring()))
                {
                    if (hero.onRing==0)
                    {
                        hero.onRing=1;
                        hero.ringx=ring.position.x;
                        hero.ringy=ring.position.y;
                        hero.ring_radius=ring.radius;
                        hero.ringAngle=0;
                    }
                  
                }
    }
    
    
}

void tick_elements() {
    ++timma;
    int f1=1;
    if (hero.score%10==0)
    {
      ++f1;   
    }
    if (timma%100==3)
    {
           // boomerang     = Boomerang(rand()%(4), 0, 0.1, 0.2, COLOR_GREEN);
        int coinx=rand()%4;
        bool flag=0;
        color_t color=COLOR_YELLOW;
        if(coinx>=2)
            {
                color=COLOR_OYELLOW;
            }
        coin1=Coin(coinx, rand()%(4), 0.1f, timma , color, flag);
        coins.push_back(coin1);
    }
    if (timma%500==3)
    {
        firelines.pb(FireLine(0, rand()%(4), 45.0f, 0, COLOR_RED));
    }
    if (timma%(1000/f1)==3)
    {
                projectile_coins.pb(Projectile_Coin(hero.position.x, 2, 0.1,  0.02,  0.05, COLOR_KAALA, 3));
        
        Projectile_Coin pcoin=projectile_coins[projectile_coins.size()-1];
        projectile_coins.pb(Projectile_Coin(pcoin.position.x+2*pcoin.radius, pcoin.position.y, pcoin.radius,  pcoin.speed,  pcoin.vspeed, COLOR_KAALA, pcoin.factor));
        
        projectile_coins.pb(Projectile_Coin(pcoin.position.x-2*pcoin.radius, pcoin.position.y, pcoin.radius,  pcoin.speed, pcoin.vspeed, COLOR_KAALA, pcoin.factor));
        
        projectile_coins.pb(Projectile_Coin(pcoin.position.x, pcoin.position.y+2*pcoin.radius, pcoin.radius,  pcoin.speed, pcoin.vspeed, COLOR_KAALA, pcoin.factor));
       
        projectile_coins.pb(Projectile_Coin(pcoin.position.x, pcoin.position.y-2*pcoin.radius, pcoin.radius,  pcoin.speed,  pcoin.vspeed, COLOR_KAALA, pcoin.factor));
    }
    if (timma%(2000/f1)==3)
    {
            FireLine f=FireLine(1, rand()%(4), 0, 0.1, COLOR_GREEN);
            firelines.pb(f);
            firelines.pb(FireLine(1, f.position.y+0.1 , 0, 0.1, COLOR_GREEN));
    }
    if (timma%2000==10)
    {
            rings.pb(Ring(-1, rand()%(4), 0.7, COLOR_RED));
    }
    if (timma%3000==3)
    {
                boomerangs.pb(Boomerang(rand()%4 , 1, 0.1, 0.1, COLOR_GREEN));
            magnets.pb(Magnet(rand()%(4), hero.position.y, COLOR_BLUE));
    }
    if(timma%4000==2)
    {
        projectile_coins.pb(Projectile_Coin(hero.position.x, 1.8, 0.1,  0.02,  0.05, COLOR_HRED, 2));
        
        Projectile_Coin pcoin=projectile_coins[projectile_coins.size()-1];
        projectile_coins.pb(Projectile_Coin(pcoin.position.x+2*pcoin.radius, pcoin.position.y, pcoin.radius,  pcoin.speed,  pcoin.vspeed, COLOR_HRED, pcoin.factor));
        
        projectile_coins.pb(Projectile_Coin(pcoin.position.x-2*pcoin.radius, pcoin.position.y, pcoin.radius,  pcoin.speed, pcoin.vspeed, COLOR_HRED, pcoin.factor));
        
        projectile_coins.pb(Projectile_Coin(pcoin.position.x, pcoin.position.y+2*pcoin.radius, pcoin.radius,  pcoin.speed, pcoin.vspeed, COLOR_HRED, pcoin.factor));
       
        projectile_coins.pb(Projectile_Coin(pcoin.position.x, pcoin.position.y-2*pcoin.radius, pcoin.radius,  pcoin.speed,  pcoin.vspeed, COLOR_HRED, pcoin.factor));
              coin1=Coin(rand()%4, rand()%(4), 0.1f, timma , COLOR_RED , 1);
        coins.push_back(coin1);
    }
    for(auto &f:firelines)
        f.tick();
    dragon.move();
    for(auto &boomerang: boomerangs)
        boomerang.move();
    camera_rotation_angle = 100;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models  float left   = screen_center_x - 4 / screen_zoom;
    ball1       = Board(0, 0, COLOR_LIGHT_BLUE);
    ball2       = Board(0, 8-bottom_board/2, COLOR_LIGHT_BLUE);
     ball3       = Board(0, 5.5-bottom_board/2, COLOR_LIGHT_BLUE);
    hero     = Hero(left_board, bottom_board/2, COLOR_RED);
    dragon = Dragon(0, 0, 0, 0.1, COLOR_RED);
    long double pi=3.14159265359;
    // firelines.pb(FireLine(1, 1.2, 0, 0.1, COLOR_GREEN));
    // firelines.pb(FireLine(1, 1, 0, 0.1, COLOR_GREEN));
    // firelines.pb(FireLine(0, 0, 45.0f, 0, COLOR_RED));
    // rings.pb(Ring(-1, 1, 0.7, COLOR_RED));
    // magnets.pb(Magnet(0, hero.position.y, COLOR_BLUE));
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    window = initGLFW(width, height);

    initGL (window, width, height);
    
    /* Draw in loop */
    for (int i = 0; i < 181; ++i)
    {
            mycos[i]=cos(i);
            mysin[i]=sin(i);
    }
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            tick_elements();
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    if (a.x+a.width<b.x)
    {
        return 0;
    }
    if (a.x>b.x+b.width)
    {
        return 0;
    }
     if (a.y+a.height<b.y)
    {
        return 0;
    }
    if (a.y>b.y+b.height)
    {
        return 0;
    }
    return 1;
}
ld absol(ld x)
{
    if (x<0)
    {
        return -x;
    }
    return x;
}
bool checkSameSide(pair<ld ,ld>p, pair<ld ,ld>p1, bounding_line_t b)
{
    long double x1=p.ff,y1=p.ss,m;
    m=(b.x2-b.x1)*(y1-b.y1)-(b.y2-b.y1)*(x1-b.x1);
    x1=p1.ff,y1=p1.ss;
    m/=absol(m);
    m=m*((b.x2-b.x1)*(y1-b.y1)-(b.y2-b.y1)*(x1-b.x1));
    m/=absol(m);
    if (m<0)
    {
        return 0;
    }
    return 1;
}
bool detect_collision_line(bounding_box_t a, bounding_line_t b) {
    
    if (a.x>max(b.x1, b.x2)||a.x+a.width<min(b.x1, b.x2)||a.y>max(b.y1, b.y2)||a.y+a.height<min(b.y1, b.y2))
    {
        return 0;
    }
    long double x1=a.x,y1=a.y;
    ll f=1;

    f=f&checkSameSide(mp(x1,y1), mp(x1,y1+a.height), b);
    f=f&checkSameSide(mp(x1,y1), mp(x1+a.width,y1), b);

    x1=a.x+a.width;
    y1=a.y+a.height;
    f=f&checkSameSide(mp(x1,y1), mp(x1-a.width,y1), b);
    f=f&checkSameSide(mp(x1,y1), mp(x1,y1-a.height), b);
    return 1-f;
}
bool detect_collision_coin(bounding_box_t a, bounding_ring_t b) {
    if (((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))<=b.radius*b.radius)
    {
        return 1;
    }
    if (((a.x-b.x)*(a.x-b.x)+(a.y+a.height-b.y)*(a.y+a.height-b.y))<=b.radius*b.radius)
    {
        return 1;
    }
    if (((a.x+a.width-b.x)*(a.x+a.width-b.x)+(a.y+a.height-b.y)*(a.y+a.height-b.y))<=b.radius*b.radius)
    {
        return 1;
    }
    if (((a.x+a.width-b.x)*(a.x+a.width-b.x)+(a.y-b.y)*(a.y-b.y))<=b.radius*b.radius)
    {
        return 1;
    }
    return 0;
}
void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
