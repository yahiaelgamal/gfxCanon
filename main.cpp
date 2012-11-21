#include "GLUT/glut.h"
#include <iostream.h>
#include <math.h>

#define PI 3.14159265
#define MAX_RESIST 3.5
#define MIN_RESIST 0.5
#define MAX_HOLE_RAD 6
#define MAX_SCORE 15.0

void anim(void);
float camera_x = 0.0;
float camera_y = 0.0;
float camera_z = 0.0;

float tx = 0.0;
float ty = 0.0;
float tz = 1.0;
float s = 130.0;

float rotbody=0.0f;
float rotholder=0.0f;
float canonfor = 4.0f;

bool kazifa_view = false;

float score = 0.0;

struct Kazifa{
    float x;
    float y;
    float z;
    
    float anglx;
    float angly;
    float anglz;
    
    float resist;
    
    bool moving;
    
    void init(float xx, float yy, float zz,
              float ax, float ay, float az){
        x = xx;
        y = yy;
        z = zz;
        anglx = ax;
        angly = ay;
        anglz = az;
    }
    void init(){
        x = 0.0;
        y = 7.5;
        z = canonfor-1;
        anglx = rotholder;
        angly = rotbody;
        anglz = 0;
        if (resist == 0)
            resist = 3.3;
        
        moving = false;
    }
    void draw(){
        glPushMatrix(); // start sphere
        glTranslated(x, y, z);
        GLUquadricObj * qobj;
        qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj,GLU_FILL);
        gluSphere(qobj, 0.6, 20, 10);
        glPopMatrix(); // end sphere
    }
    void update(){
       // cout << "rotbody " << angly << "  sin " << sin(angly) << endl;
        y +=1*sin(PI*angly/180);
        angly-=resist;
        x -= sin(PI*rotholder/180);
        z +=1*cos(PI*rotbody/180);;
        
        if (y < -3.0)
            init();
    }
    void undo_update(){
        
        z -=1*cos(PI*rotbody/180);;
        x += sin(PI*rotholder/180);
        angly+=resist;
        y -=1*sin(PI*angly/180);
        
    }
    void print(){
        printf("x:%f, y:%f, z:%f\n", x,y,z);
    }
    
    void print_power(){
       //printf("%f",  (MAX_RESIST-resist));
        std::cout << "power:";
        for (float i = MAX_RESIST-resist; i > 0; i-=0.1){
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}kazifa;


struct Hole{
    float x,y,z,r;
    bool hit;
    
    void init(float mx, float my, float mz, float rad){
        x = mx;
        y = my;
        z = mz;
        r = rad;
        hit = false;
    }
    
    void draw(){
        if(hit)
            return;
        
        GLUquadricObj * qobj;
        qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj,GLU_FILL);
        
        glPushMatrix(); // start disk
        glTranslated(x,y, z);
        glRotatef(90, 1.0, 0, 0);
        glColor3f(0, 0, 0);
//        gluDisk(qobj, r-0.75, r, 20, 4);
        gluCylinder(qobj, r, r, 0.5, 20,4);
        glPopMatrix(); // end disk
    }
    
    bool isIn(Kazifa kaz){
        if (hit)
            return false;
        
        if (kaz.x < x + r && kaz.x > x - r &&
            kaz.y < y + 0.5 && kaz.y > y - 0.5 &&
            kaz.z < z + r && kaz.z > z - r){
            hit = true;
            score += MAX_HOLE_RAD - r;
            printf("Score is %.0f%%\n", score/MAX_SCORE*100);
            return true;
        }
        else{
        //    printf("NOT HIT %f\n",r);
            return false;
        }
    }
    
    void print(){
        printf("x:%f, y:%f, z:%f, r:%f\n", x,y,z,r);
    }
};

Hole h1, h2, h3, h4, h5;
Hole holes[5] = {h1,h2,h3,h4,h5};

void myKeyboard(unsigned char thekey,int mouseX,int mouseY);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void drawWheels(void){
    
    glPushMatrix(); //start wheels
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(-0.2, -1.25,0.0); // cylinder at (0,0,1)
    
    int dx[4] = {-1,-1,1,1};
    int dz[4] = {1,-1, 1,-1};
    for (int i = 0; i < 4; i++){
        glPushMatrix(); // start one wheel
        glColor3f(0.0, 0.0, 0.5);
        glTranslated(dx[i]*2.7, 0, dz[i]*1.5); // cylinder at (0,0,1)
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glScalef(0.5, 0.5, 0.25);
        GLUquadricObj * qobj;
        qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj,GLU_FILL);
        gluCylinder(qobj, 1.0, 1.0, 2.0, 20,8);
        
        glPushMatrix();
        if (dx [i] == -1){
            glRotatef(180, 0.0, 1.0, 0.0);
        }else{
            glTranslated(0.0, 0.0, 2.0);
        }
        gluDisk(qobj, 0, 1.0, 20, 4);
        
        glTranslated(0,0,-2.0);
        gluDisk(qobj, 0, 1.0, 20, 4);
        glTranslated(0,0,2.0);
        glColor3f(0.8, 0.2, 0.5);
        glutSolidCone(0.3, 5, 20, 10);
        glPopMatrix();
        glPopMatrix(); // end one wheel
        
    }
    glPopMatrix(); // end wheelss
}

void drawCanon(void){
    glColor3f(0.5, 0.5, 0.0);
    glPushMatrix(); // wire cube start
    glutWireCube(50);
    
    glPushMatrix(); //canon
    glTranslated(0, 2, canonfor);
    glScalef(1.5, 1.5, 1.5);
    
    glPushMatrix(); //base
    glScalef(1, 0.5, 1);
    glutSolidCube(5);
    glPopMatrix(); // end base
    
    
    glColor3f(1,0,0);
    
    
    drawWheels();
    
    glPushMatrix(); // start holder
    
    glTranslated(0, 1.75, -0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(rotholder, 0.0, 0.0, 1.0);
    
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj, 2.0, 2.0, 0.5, 20,10);
    
    glPushMatrix(); // start disk
    gluDisk(qobj, 0, 2.0, 20, 4);
    glColor3f(0.8, 0.2, 0.5);
    glPopMatrix(); // end disk
    
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    
    glPushMatrix(); // start 5azoo2_1
    glColor3f(1,1,0);
    glTranslated(-1.0, 1.5, 0);
    glScalef(0.2, 1, 0.3);
    glutSolidCube(3);
    
    glPopMatrix(); // end 5azoo2_1
    
    
    glPushMatrix(); // start 5azoo2_2
    
    glColor3f(1,1,0);
    glTranslated(1.0, 1.5, 0);
    glScalef(0.2, 1, 0.3);
    glutSolidCube(3);
    
    glPopMatrix(); // end 5azoo2_2
    
    glPushMatrix(); // start body
    
    glTranslated(0, 2.0, -0.5);
    glRotatef(rotbody, -1.0, 0.0, 0.0);
    glColor3f(0.0, 1, 0.0);
    GLUquadricObj * qobj2;
    qobj2 = gluNewQuadric();
    gluQuadricDrawStyle(qobj2,GLU_FILL);
    gluCylinder(qobj2, 0.80, 0.6, 3.0, 20,8);
    
    glPushMatrix(); // start sphere
    gluSphere(qobj2, 0.8, 20, 10);
    glPopMatrix(); // end sphere
    
    glPushMatrix();
    glColor3f(0.0,0.0,1);
    //    glTranslated(0, 1.0 ,0); // torus at (0,1,0)
    //    glRotated(90.0, 1,0,0);
    glutSolidTorus(0.1, 0.8, 20,10);
    glPopMatrix();
    
    glTranslated(0.0, 0.0, 3.0);
    glColor3f(1.0,0,0);
    GLUquadricObj * qobj3;
    qobj3 = gluNewQuadric();
    gluQuadricDrawStyle(qobj3,GLU_FILL);
    gluCylinder(qobj3, 0.60, 0.8, 0.75, 20,8);
    
    
    glPopMatrix(); //end body
    
    glPopMatrix(); // end holder
    
    glPopMatrix(); // end canon
    glPopMatrix(); // end small cube
    
}

void displayWire(void)
{
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(s, //Field of view
                   800.0/600.0, //Aspect ratio
                   0.9, // Z near
                   100.0);// Z far
    
    double factor = 1;
    glOrtho(-10/factor, 10/factor, -10/factor, 10/factor, 0.1, 500);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    if (kazifa_view)
        gluLookAt(kazifa.x, kazifa.y, kazifa.z+1.0, // eye
              kazifa.x, kazifa.y+0.5, kazifa.z, // center
              0.0, 1.0, 0.0); // normal
    else
        gluLookAt(0.0,0.0,5.0, // eye
              0.0,0.0,0.0,
              0.0, 1.0, 0.0); // normal
    
    glRotatef(camera_x, 1.0, 0.0, .0);
    glRotatef(camera_y, 0.0, 1.0, .0);
    glRotatef(camera_z, 0.0, 0.0, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); // everything
    
    drawCanon();
    kazifa.draw();
    
    for (int i = 0; i < 5; i++){
        holes[i].isIn(kazifa);
    }
    
    for(int i = 0; i < 5; i++){
        holes[i].draw();
    }
    
    glPopMatrix(); // end everything
    glFlush();
}

void init_holes(void){
    holes[0].init(5,0,45,2);
    holes[1].init(-8,0,30,4);
    holes[2].init(13,0,55,5);
    holes[3].init(-4,0,23,3);
    holes[4].init(5,0,39,1);
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    
    glutInitWindowSize(800,600);
    
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformation testbed - wireframes");
    glutDisplayFunc(displayWire);
    
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0};
    float light_position[] = {10.0, 10.5, 10.5, 0.0};
    
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);
    
    glEnable(GL_DEPTH_TEST);
    //    glDepthMask(GL_TRUE);
    //    glDepthFunc(GL_LEQUAL);
    //    glDepthRange(0.0f, 1.0f);
    
    glutKeyboardFunc(myKeyboard);
    glClearColor(1.0f, 1.0f, 1.0f,0.0f); // background is white
	glutIdleFunc(anim);
    glViewport(0, 0, 800, 600);
    
    init_holes();
    kazifa.init();
    glutMainLoop();
}

void myKeyboard(unsigned char thekey,int mouseX,int mouseY){
    int init_kazifa = 0;
    switch(thekey){
            // camera
        case 'x':
            camera_x += 5;
            camera_x= (int)camera_x %360;
            break;
        case 'y':
            camera_y += 5;
            camera_y= (int)camera_y %360;
            break;
        case 'z':
            camera_z += 5;
            camera_z= (int)camera_z %360;
            break;
            
        case 'X':
            camera_x -= 5;
            camera_x= (int)camera_x %360;
            break;
        case 'Y':
            camera_y -= 5;
            camera_y= (int)camera_y %360;
            break;
        case 'Z':
            camera_z -= 5;
            camera_z= (int)camera_z %360;
            break;
        
        case 'K':
            if (kazifa_view){
                kazifa_view = false;
                s = 130;
                
            }else{
                kazifa_view = true;
                camera_x=0;
                camera_y=0;
                camera_z=0;
                s=80;
            }
            break;
            
            // play/rewind
        case 'p':
            kazifa.moving = true;
//            kazifa.update();
            break;
        case 'P':
            kazifa.moving = false;
//            kazifa.undo_update();
            break;
            
            
            // control
        case 'r':
            if (rotbody < 90)
                rotbody += 1;
            init_kazifa =1;
            break;
            
        case 'R':
            if (rotbody > 0)
                rotbody -= 1;
            init_kazifa =1;
            break;
            
        case 'e':
            if (rotholder < 45)
                rotholder += 1;
            init_kazifa =1;
            break;
            
        case 'E':
            if (rotholder > -45)
                rotholder -= 1;
            init_kazifa =1;
            break;
            
        case 'f':
            canonfor += 1;
            init_kazifa =1;
            break;
        case 'F':
            canonfor -= 1;
            init_kazifa =1;
            break;
            
            // zoom
        case 's':
            s +=1;
            break;
        case 'S':
            s -=1;
            break;
            
            // power
        case '+':
            if(kazifa.resist > MIN_RESIST)
                kazifa.resist -= 0.1;
            kazifa.print_power();
            break;
        case '-':
            if(kazifa.resist < MAX_RESIST)
                kazifa.resist += 0.1;
            kazifa.print_power();
            break;
            
            // init
        case 'I':
            kazifa.init();
            //printf("kazifa.angly %f\n", kazifa.angly);
            break;
            
    }
    if (init_kazifa)
        kazifa.init();
//    glutPostRedisplay();
    
}

void anim(){
    if (kazifa.moving){
        kazifa.update();
    }
    for (int i = 0; i < 3e6; i++){}
    glutPostRedisplay();
}
