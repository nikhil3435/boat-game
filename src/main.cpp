#include "main.h"
#include "timer.h"
#include "ground.h"
#include "boat.h"
#include "rock.h"
#include "barrel.h"
#include "enemy.h"
#include "bullet.h"
#include <bits/stdc++.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Ground water1;
Rock rock[15];
Barrel barrel[5];
int flag=1;
int score,level=1;
Enemy enemy1,enemy[5];
Bullet bullet;
Rock rock1,rock2,rock3,rock4,rock5,rock6,rock7,rock8,rock9,rock10,rock11,rock12,rock13,rock14,rock15;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int cam;
int i;
float eye_x,eye_y,eye_z,target_x,target_y,target_z;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    if (cam==1){
                target_x=ball1.position.x;
                target_y=ball1.position.y;
                target_z=ball1.position.z;
            eye_x = ball1.position.x -(6*sin(-ball1.rotation*M_PI/180.0));
            eye_y = ball1.position.y -(6*cos(-ball1.rotation*M_PI/180.0));
            eye_z = ball1.position.z+9;
        }
        else if(cam==2){
            target_x = ball1.position.x + 10000*(3*sin(-ball1.rotation*M_PI/180.0));
            target_y=ball1.position.y + 10000*(3*cos(-ball1.rotation*M_PI/180.0));
            target_z=ball1.position.z;
            eye_x = ball1.position.x-(0*sin(-ball1.rotation*M_PI/180.0));
            eye_y =ball1.position.y-(0*cos(-ball1.rotation*M_PI/180.0));
            eye_z = ball1.position.z+3;
        }
        else if(cam==3){
            eye_x=0;eye_y=-3;eye_z=1;
            target_x=0;target_y=0;target_z=0;
        }
        else if(cam==4){
        float angle = (ball1.rotation*M_PI)/180;
             eye_x=ball1.position.x -2*sin(angle);
             eye_y=ball1.position.y-2*cos(angle);
             eye_z=ball1.position.z+0.75;
             target_x=ball1.position.x;
             target_y=ball1.position.y;
             target_z=ball1.position.z;
        }
        else if(cam==5){
             eye_x=ball1.position.x;
             eye_y=ball1.position.y+0.15;
             eye_z=ball1.position.z+0.80;

             target_x=ball1.position.x + 10000*(3*sin(-ball1.rotation*M_PI/180.0));
             target_y=ball1.position.y + 10000*(3*cos(-ball1.rotation*M_PI/180.0));
             target_z=ball1.position.z-0.5;
        }
    glm::vec3 eye(eye_x,eye_y,eye_z);
    glm::vec3 target(target_x,target_y,target_z);
    glm::vec3 up(0,0,1);
   // glm::vec3 eye (ball1.position.x+2.5*sin(rotation*M_PI/180),0,ball1.position.z+2.5*cos(rotation*M_PI/180) );
    //glm::vec3 target (ball1.position.x, ball1.position.y+1, ball1.position.z);
    //glm::vec3 up (0, 1, 0);
    //Matrices.view = glm::lookAt( eye, target, up );
    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    //glm::vec3 eye (0,-3,1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    //glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    //glm::vec3 target (0, 0, 0);

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
    water1.draw(VP);
    rock1.draw(VP);
    rock2.draw(VP);
    rock3.draw(VP);
    rock4.draw(VP);
    rock5.draw(VP);
    rock6.draw(VP);
    rock7.draw(VP);
    rock8.draw(VP);
    rock9.draw(VP);
    rock10.draw(VP);
    rock11.draw(VP);
    rock12.draw(VP);
    rock13.draw(VP);
    rock14.draw(VP);
    rock15.draw(VP);
    enemy1.draw(VP);
    bullet.draw(VP);
    for(int i=0;i<5;i++){
        barrel[i].draw(VP);
    }
    for(int j=0;j<5;j++){
        enemy[j].draw(VP);
    }
    for(int i=0;i<15;i++){
    rock[i].draw(VP);}

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);
    int hit = glfwGetKey(window, GLFW_KEY_F);
    if (left) {
     //   ball1.position.x -= 0.01;
        ball1.rotation+=.1;
        bullet.rotation +=.1;
        //printf("ff");
        //rotation += 0.1;
        // Do something
    }
    if (right) {
      //  ball1.position.x += 0.01;
        ball1.rotation-=.1;
        bullet.rotation -=.1;
        //rotation += 0.1;
    }
    if (up) {

           // ball1.position.y += 0.01;
        ball1.position.y += (0.1)*cos(ball1.rotation*M_PI/180);
        ball1.position.x += (0.1)*sin(ball1.rotation*M_PI/180);
      //  ball1.position.z = 1;
        //   ball1.position.y += 0.05;

           bullet.position.x=ball1.position.x;
       bullet.position.y = ball1.position.y-0.5;
       bullet.position.z = ball1.position.z+0.1;

    }
    if (down) {
        ball1.position.y -= 0.01;
        bullet.position.x=ball1.position.x;
       bullet.position.y = ball1.position.y-0.5;
       bullet.position.z = ball1.position.z+0.1;
    }
    if (space) {
     //   ball1.position.z = 0.1;
        ball1.speed = 1;

    }
    if(three){
        cam=3;
        eye_x=0;eye_y=-3;eye_z=1;
        target_x=0;target_y=0;target_z=0;
    }
    if(one){
        cam=1;
        target_x=ball1.position.x;
        target_y=ball1.position.y;
        target_z=ball1.position.z;
        eye_x = ball1.position.x -(6*sin(-ball1.rotation*M_PI/180.0));
        eye_y = ball1.position.y -(6*cos(-ball1.rotation*M_PI/180.0));
        eye_z = ball1.position.z+9;
    }
    if(two){
        cam=2;
        target_x = ball1.position.x + 10000*(3*sin(-ball1.rotation*M_PI/180.0));
        target_y=ball1.position.y + 10000*(3*cos(-ball1.rotation*M_PI/180.0));
        target_z=ball1.position.z;
        eye_x = ball1.position.x-(0*sin(-ball1.rotation*M_PI/180.0));
        eye_y =ball1.position.y-(0*cos(-ball1.rotation*M_PI/180.0));
        eye_z = ball1.position.z+3;

    }
    if(four){
        cam=4;
        eye_x=ball1.position.x;
        eye_y=ball1.position.y-3;
        eye_z=ball1.position.z;
        target_x=ball1.position.x;
        target_y=ball1.position.y;
        target_z=ball1.position.z;
    }
    if(five){

        cam=5;
        eye_x=ball1.position.x;
        eye_y=ball1.position.y+0.15;
        eye_z=ball1.position.z+0.80;

        target_x=ball1.position.x + 10000*(3*sin(-ball1.rotation*M_PI/180.0));
        target_y=ball1.position.y + 10000*(3*cos(-ball1.rotation*M_PI/180.0));
        target_z=ball1.position.z;
    }
    if(hit){
        bullet.position.x=ball1.position.x;
       bullet.position.y = ball1.position.y-0.35;
       bullet.position.z = ball1.position.z+0.1;
       for(int l=0;l<1000;l++){
        bullet.position.y += 0.008;
       }
    }

}

void tick_elements() {
    //ball1.tick();
    //camera_rotation_angle += 1;
    for(int k=0;k<5;k++){
        enemy[k].tick();
    }
    enemy1.tick();
    ball1.jump();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // .Create the models
    float r1,r2,r3;
    ball1       = Ball(0, -2.3,0, COLOR_RED);
    water1      = Ground(0,0,0,COLOR_WATER);
    bullet      = Bullet(ball1.position.x+0,ball1.position.y-0.5,ball1.position.z+0.1,COLOR_ORANGE);
    for(i=0;i<8;i++){
        r1=(rand()%200)/10;
        r2=(rand()%10000)/100;
        //r3=(rand()%1)/10;
        rock[i]=Rock(r1,r2,0,COLOR_ROCK);
    }
    for(i=8;i<15;i++){
        r3=-(rand()%200)/10;
        r2= (rand()%10000)/100;
        rock[i]=Rock(r3,r2,-0.2,COLOR_ROCK);
    }
    for(int j=0;j<5;j++){
        r1=(rand()%400)/10;
        r2=(rand()%1000)/10;
        enemy[j]=Enemy(r1-20,r2,0,COLOR_YELLOW);
    }
    for(int t=0;t<5;t++){
        r1=(rand()%400)/10;
        r2=(rand()%1000)/10;
        barrel[t]=Barrel(r1-20,r2,0,COLOR_YELLOW);
    }
    rock1       = Rock(0,1,-0.1,COLOR_ROCK);
    rock2       = Rock(-3.5,12,0,COLOR_ROCK);
    rock3       = Rock(-13,25,-0.3,COLOR_ROCK);
    rock4       = Rock(-1.2,23,-0.2,COLOR_ROCK);
    rock5       = Rock(12,8,0,COLOR_ROCK);
    rock6       = Rock(-2.3,12,0,COLOR_ROCK);
    rock7       = Rock(-23,42,0,COLOR_ROCK);
    rock8       = Rock(13,26.5,0,COLOR_ROCK);
    rock9       = Rock(22,17,0,COLOR_ROCK);
    rock10       = Rock(-22.9,19,-0.2,COLOR_ROCK);
    rock11      = Rock(-31.3,29,0,COLOR_ROCK);
    rock12      = Rock(-10.4,32,0,COLOR_ROCK);
    rock13      = Rock(15,12,-0.1,COLOR_ROCK);
    rock14      = Rock(-3.2,9,0,COLOR_ROCK);
    rock15      = Rock(-11,6.5,0,COLOR_ROCK);
    enemy1      = Enemy(2,7,0,COLOR_YELLOW);
    if (detect_collision_rock(ball1.bounding_box(),rock1.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;
        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock2.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;
        score -= 5;


     }
    if (detect_collision_rock(ball1.bounding_box(),rock3.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock4.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock5.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock6.bounding_box())){
        ball1.position.x -= 0.05;
        score -= 5;

        ball1.position.y -= 0.02;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock7.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock8.bounding_box())){
        ball1.position.x -= 0.05;
        score -= 5;

        ball1.position.y -= 0.02;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock9.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock10.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock11.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock12.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

    }
    if (detect_collision_rock(ball1.bounding_box(),rock13.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock14.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    if (detect_collision_rock(ball1.bounding_box(),rock15.bounding_box())){
        ball1.position.x -= 0.05;
        ball1.position.y -= 0.02;

        score -= 5;

     }
    for(i=0;i<15;i++){
         if (detect_collision_rock(ball1.bounding_box(),rock[i].bounding_box())){
             ball1.position.x -= 0.05;
             ball1.position.y -= 0.02;

             score -= 5;

          }
     }
    for(int s=0;s<5;s++){
         if (detect_collision_enemy(bullet.bounding_box(),enemy[s].bounding_box())){
             score += 20;
             enemy[s].position.x=45;
             enemy[s].position.y=50;

          }
     }

    for(int t=0;t<15;t++){
         if (detect_collision_barrel(ball1.bounding_box(),barrel[t].bounding_box())){
             score = 100;
             barrel[t].position.x = (rand()%500)/10;
             barrel[t].position.y = (rand()%1000)/10;

          }
     }

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
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);
    score=100;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {

            // 60 fps
            // OpenGL Draw commands
            string Result;
            stringstream convert;
                                    //cout << "nonedit score:" << score << endl;
            convert << score;
            Result = convert.str();

            const char *one = "Health ";
            const char *two = Result.c_str();
            const char *three = "   Level ";
            string Result1;
                                    stringstream convert1;
                                    convert1 << level;
                                    Result1 = convert1.str();
                                    const char *four = Result1.c_str();
                                    string total( string(one) + two + string(three) + four);
                                    glfwSetWindowTitle(window, total.c_str());
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}
bool detect_collision_rock(bounding_box_t a, bounding_box_t b) {

    if(abs(a.x-b.x)<=2 && abs(a.y-b.y)<=2 && abs(a.z-b.z)<=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool detect_collision_enemy(bounding_box_t a, bounding_box_t b) {

    if(abs(a.x-b.x)<=1 && abs(a.y-b.y)<=1 && abs(a.z-b.z)<=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool detect_collision_barrel(bounding_box_t a, bounding_box_t b) {

    if(abs(a.x-b.x)<=1 && abs(a.y-b.y)<=1 && abs(a.z-b.z)<=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::infinitePerspective(glm::radians(90.0f), 2.0f,0.1f);
}
void screen_zoom_in(){
    screen_zoom -= 0.1;
    reset_screen();
}
void screen_zoom_out(){
    screen_zoom += 0.1;
    reset_screen();
}
