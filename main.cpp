#include "GLUT/glut.h"
#include <iostream.h>
#include <math.h>

#define PI 3.14159265

float camera_x = 0.0;
float camera_y = -90.0;
float camera_z = 0.0;

float tx = 0.0;
float ty = 0.0;
float tz = 12.0;
float s = 170.0;

float rotbody=0.0f;
float rotholder=0.0f;
float canonfor = 4.0f;

struct Kazifa{
    float x;
    float y;
    float z;

    float anglx;
    float angly;
    float anglz;
     
    float resist = 5/1;
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
        y = 5.5;
        z = canonfor-1;
        anglx = 0;
        angly = rotbody;
        anglz = 0;
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
        cout << "rotbody " << angly << "  sin " << sin(angly) << endl;
        
        y +=1*sin(PI*angly/180);
        angly-=resist;
        
        z +=1*cos(PI*rotbody/180);;
    }
    void undo_update(){

        z -=1*cos(PI*rotbody/180);;
        angly+=resist;
        y -=1*sin(PI*angly/180);

    }
    void print(){
        printf("x:%f, y:%f, z:%f\n", x,y,z);
    }
}kazifa;


struct Hole{
    float x,y,z,r;
    
    void init(float mx, float my, float mz, float rad){
        x = mx;
        y = my;
        z = mz;
        r = rad;
    }
    
    void draw(){
        GLUquadricObj * qobj;
        qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj,GLU_FILL);
        
        glPushMatrix(); // start disk
        glTranslated(x,y, z);
        glColor3f(0, 0, 0);
        gluDisk(qobj, r-0.75, r, 20, 4);
        glPopMatrix(); // end disk
    }
    
    bool isIn(Kazifa kaz){
        if (kaz.x < x + r && kaz.x > x - r &&
            kaz.y < y + r && kaz.y > y - r &&
            kaz.z < z + 1 && kaz.z > z - 1)
            return true;
        else
            return false;
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
    glutWireCube(15);
    
    glPushMatrix(); //canon
    glTranslated(0, 0, canonfor );
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
                   640/480.0, //Aspect ratio
                   0.1, // Z near
                   100.0);// Z far
    
    double factor = 1;
    glOrtho(-10/factor, 10/factor, -10/factor, 10/factor, 0.1, 500);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluLookAt(tx, ty, tz, // eye position
              0.0, 0.0, 0.0, // center
              0.0, 1.0, 0.0); // normal
    
    
    glRotatef(camera_x, 1.0, 0.0, .0);
    glRotatef(camera_y, 0.0, 1.0, .0);
    glRotatef(camera_z, 0.0, 0.0, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); // everything
    
    drawCanon();
    kazifa.draw();
    
    h1.init(0,5,15,2);
    h1.draw();
    kazifa.print();
    printf("%d\n", h1.isIn(kazifa));
    
    glPopMatrix(); // end everything
    glutSwapBuffers();
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
    
    GLfloat light_diffuse[] = {0.8, 0.8, 0.8};
    float light_position[] = {10.0, 10.5, 10.5, 0.0};
    float light_position2[] = {-10.0, 10.5, -10.5, 0.0};
    
    float light_position3[] = {0.0, -10.5, -10.5, 0.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_diffuse);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
//    glEnable(GL_LIGHTING);
    
    glEnable(GL_DEPTH_TEST);
    //    glDepthMask(GL_TRUE);
    //    glDepthFunc(GL_LEQUAL);
    //    glDepthRange(0.0f, 1.0f);
    
    glutKeyboardFunc(myKeyboard);
    glClearColor(1.0f, 1.0f, 1.0f,0.0f); // background is white
    glViewport(0, 0, 800, 600);
    
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
            std::cout << camera_x << std::endl;
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
            
        // play/rewind
        case 'p':
            kazifa.update();
            break;
        case 'P':
            kazifa.undo_update();
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
            if (rotholder > 0)
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
            kazifa.resist -= 0.5;
            printf("kazifa.resist %f\n", kazifa.resist);
            break;
        case '-':
            kazifa.resist += 0.5;
            printf("kazifa.resist %f\n", kazifa.resist);
            break;
        // init
        case 'I':
            kazifa.init();
            printf("kazifa.angly %f\n", kazifa.angly);
            break;
        
    }
    if (init_kazifa)
        kazifa.init();
    glutPostRedisplay();
    
}
