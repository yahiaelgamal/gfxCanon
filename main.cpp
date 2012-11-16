#include "GLUT/glut.h"
#include <iostream.h>
float x = 0.0;
float y = 0.0;
float z = 0.0;

float tz = 0.0;
float s = 1.0;

float rotcanon=0.0f;
float rotholder=0.0f;
void myKeyboard(unsigned char thekey,int mouseX,int mouseY);
//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>
void axis(double length)
{ // draw a z-axis, with cone at end
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(0,0,length); // along the z-axis
    glEnd();
    glTranslated(0, 0,length -0.2);
    glutWireCone(0.04, 0.2, 12, 9);
    glPopMatrix();
}
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
void drawAxis(void){
    glPushMatrix();
    glColor3d(1,0,0); // draw black lines
    axis(5); // x-axis
    
    glColor3d(1,1,0); // draw black lines
    glPushMatrix();
    glRotated(90, 0,1.0, 0);
    axis(5); // y-axis
    
    glColor3d(0,1,0); // draw black lines
    glRotated(-90.0, 1, 0, 0);
    axis(5); // z-axis
    glPopMatrix();
    glPopMatrix();
    
} void displayWire(void)
{
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
   gluPerspective(100.0, //Field of view
                       640/480.0, //Aspect ratio
                       0.9, // Z near
                       100.0);// Z far
    
    double factor = 1;
    glOrtho(-10/factor, 10/factor, -10/factor, 10/factor, 0.1, 500);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0, // eye position
              0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    
    glRotatef(x, 1.0, 0.0, .0);
    glRotatef(y, 0.0, 1.0, .0);
    glRotatef(z, 0.0, 0.0, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); // everything
    
    
    glColor3f(0.5, 0.5, 0.0);
    glPushMatrix(); // wire cube start
    glutWireCube(15);
    
    glPushMatrix(); //canon
    glTranslated(0, -2, 0);
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
    glRotatef(rotcanon, -1.0, 0.0, 0.0);
    glColor3f(0.0, 1, 0.0);
    GLUquadricObj * qobj2;
    qobj2 = gluNewQuadric();
    gluQuadricDrawStyle(qobj2,GLU_FILL);
    gluCylinder(qobj2, 0.80, 0.6, 3.0, 20,8);
    
    glPushMatrix(); // start sphere
    gluSphere(qobj2, 0.8, 20, 10);
    glPopMatrix(); // end sphere
    glPopMatrix(); //end body
    
    glPopMatrix(); // end holder
    
    glPopMatrix(); // end canon
    glPopMatrix(); // end small cube
    glPopMatrix(); // end everything
    
    
    //    drawAxis();
    glutSwapBuffers();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformation testbed - wireframes");
    glutDisplayFunc(displayWire);
    
    GLfloat light_diffuse[] = {0.8, 0.8, 0.8};
    float light_position[] = {10.0, 10.5, 10.5, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHTING);
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    
    glutKeyboardFunc(myKeyboard);
    glClearColor(1.0f, 1.0f, 1.0f,0.0f); // background is white
    glViewport(0, 0, 640, 480);
    glutMainLoop();
}

void myKeyboard(unsigned char thekey,int mouseX,int mouseY){
    switch(thekey){
        case 'x':
            x += 5;
            x= (int)x %360;
            std::cout << x << std::endl;
            break;
        case 'y':
            y += 5;
            y= (int)y %360;
            break;
        case 'z':
            z += 5;
            z= (int)z %360;
            break;
            
        case 'X':
            x -= 5;
            x= (int)x %360;
            break;
        case 'Y':
            y -= 5;
            y= (int)y %360;
            break;
        case 'Z':
            z -= 5;
            z= (int)z %360;
            break;
            
        case 'n':
            tz -= 0.1;
            break;
        case 'N':
            tz += 0.1;
            break;
            
        case 's':
            if (rotholder < 45)
                rotholder += 1.0;
            break;
        case 'S':
            if (rotholder > -45)
                rotholder -= 1.0;
            break;
            
        case 'r':
            if (rotcanon < 60)
                rotcanon += 1;
            break;
            
        case 'R':
            if (rotcanon > 0)
                rotcanon -= 1;
            break;
    }
    glutPostRedisplay();
    
}
