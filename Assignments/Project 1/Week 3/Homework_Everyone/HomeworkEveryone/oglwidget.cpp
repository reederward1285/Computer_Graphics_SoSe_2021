/**
 * @file olgwidget.cpp
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

#include "oglwidget.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "readobj.h"
#include "chaikin.h"
#include "interpolatingcubicsubdivision.h"

using namespace std;

ReadObj read = *new ReadObj();
Chaikin chai = *new Chaikin();
InterpolatingCubicSubdivision cubic = *new InterpolatingCubicSubdivision();

vector <vector<float>> vecpoints;
//vector <vector<float>> allPoints;
float colorValues[3][4] = // Values with colors for SetMaterialColor()
{
    {1, 1.0, .2, .2},
    {1, .2, .2, 1.0},
    {1, 1.0, 0.9, 0.2}
};


#define PI 3.14159265358979323846
void SetMaterialColor( int side, float r, float g, float b);

// initialize Open GL lighting and projection matrix
void InitLightingAndProjection() // to be executed once before drawing
{
    // light positions and colors
    GLfloat LightPosition1[4] = { 10, 5, 10,  0};
    GLfloat LightPosition2[4] = { -5, 5, -10,  0};
    GLfloat ColorRedish[4] = { 1.0,  .8,  .8,  1}; // white with a little bit of red
    GLfloat ColorBlueish[4] = { .8,  .8,  1.0,  1};// white with a little bit of blue

    glEnable( GL_DEPTH_TEST); // switch on z-buffer
    glDepthFunc( GL_LESS);

    glShadeModel( GL_SMOOTH); // Gouraud shading
    //glShadeModel( GL_FLAT);

    glEnable( GL_LIGHTING); // use lighting
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 1); // draw both sides

    // define and switch on light 0
    glLightfv( GL_LIGHT0, GL_POSITION, LightPosition1);
    glLightfv( GL_LIGHT0, GL_DIFFUSE,  ColorRedish);
    glLightfv( GL_LIGHT0, GL_SPECULAR, ColorRedish);
    glEnable( GL_LIGHT0);

    // define and switch on light 1
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition2);
    glLightfv( GL_LIGHT1, GL_DIFFUSE,  ColorBlueish);
    glLightfv( GL_LIGHT1, GL_SPECULAR, ColorBlueish);
    glEnable( GL_LIGHT1);

    glMatrixMode( GL_PROJECTION); // define camera projection
    glLoadIdentity(); // reset matrix to identity (otherwise existing matrix will be multiplied with)
    glOrtho( -15, 15, -10, 10, -20, 20); // orthogonal projection (xmin xmax ymin ymax zmin zmax)
    //glFrustum( -10, 10, -8, 8, 2, 20); // perspective projektion

}


void DrawLineChaikin() {

    //---Connecting the points---
    //set color of the line
    SetMaterialColor( 1, 0.2, 1.0, .2);
    //draw line
    glBegin( GL_LINE_STRIP); // glBegin()
    for( unsigned int i=0; i<vecpoints[0].size(); i++){
        glVertex3f( vecpoints[0][i], vecpoints[1][i], vecpoints[2][i]);
    }
    glEnd();

    //vector matrix for the points calculated in the algorithm
    vector<vector<float>> newpoints;
    newpoints.insert(newpoints.begin(), vecpoints.begin(), vecpoints.end());

// Subdivison-loop
    for(int x=0;x<3;x++)  // loop 3 times for three lines
        {
            //call Chaikin algorithm
            newpoints = chai.chaikinAlg(newpoints[0], newpoints[1], newpoints[2]);
            //set color of the line
            SetMaterialColor(colorValues[x][0], colorValues[x][1], colorValues[x][2], colorValues[x][3]);
            //draw line
            glBegin( GL_LINE_STRIP);

            for( unsigned int i=0; i<newpoints[0].size(); i++)
            {
                glVertex3f( newpoints[0][i], newpoints[1][i], newpoints[2][i]);
            }
            glEnd();
        }
}

void DrawLineCubic() {

    //---Connecting the points---
    //set color of the line
    SetMaterialColor( 1, 0.2, 1.0, .2);
    //draw line
    glBegin( GL_LINE_STRIP);
    for( unsigned int i=0; i<vecpoints[0].size(); i++){
        //glColor3f(0,1,0);
        glVertex3f( vecpoints[0][i], vecpoints[1][i], vecpoints[2][i]);
    }
    glEnd();

    //vector matrix for the points calculated in the algorithm
    vector<vector<float>> newpoints;
    newpoints.insert(newpoints.begin(), vecpoints.begin(), vecpoints.end());

// Subdivison-loop
    for(int x=0;x<3;x++)  // loop 3 times for three lines
        {
            //call Chaikin algorithm
            newpoints = cubic.cubicAlg(newpoints[0], newpoints[1], newpoints[2]);
            //set color of the line
            SetMaterialColor(colorValues[x][0], colorValues[x][1], colorValues[x][2], colorValues[x][3]);
            //draw line
            glBegin( GL_LINE_STRIP);

            for( unsigned int i=0; i<newpoints[0].size(); i++)
            {
                glVertex3f( newpoints[0][i], newpoints[1][i], newpoints[2][i]);
            }
            glEnd();
        }
}

// define material color properties for front and back side
void SetMaterialColor( int side, float r, float g, float b){
    float	amb[4], dif[4], spe[4];
    int	i, mat;

    dif[0] = r; // diffuse color as defined by r,g, and b
    dif[1] = g;
    dif[2] = b;
    for( i=0; i<3; i++){
        amb[i] = .1 * dif[i]; // ambient color is 10 percent of diffuse
        spe[i] = .5; // specular color is just white / gray
    }
    amb[3] = dif[3] = spe[3] = 1.0; // alpha component is always 1
    switch( side){
        case 1:	mat = GL_FRONT; break;
        case 2:	mat = GL_BACK; break;
        default: mat = GL_FRONT_AND_BACK; break;
    }
    glMaterialfv( mat, GL_AMBIENT, amb); // define ambient, diffuse and specular components
    glMaterialfv( mat, GL_DIFFUSE, dif);
    glMaterialfv( mat, GL_SPECULAR, spe);
    glMaterialf( mat, GL_SHININESS, 50.0); // Phong constant for the size of highlights
}


OGLWidget::OGLWidget(QWidget *parent) // constructor
    : QOpenGLWidget(parent)
{
    cout <<"OGLWidget "<< endl;
}


OGLWidget::~OGLWidget() // destructor
{
    cout <<"OGLWidget destructor "<< endl;
}


void OGLWidget::initializeGL() // initializations to be called once
{
    cout <<"InitializeGL "<< endl;
    initializeOpenGLFunctions();

    InitLightingAndProjection(); // define light sources and projection

    //read points
    //vecpoints = read.ReadPoints("C:\\majbrit\\Medieninformatik\\Semester 4\\ComputerGraphics\\Aufgaben\\3\\HomeworkEveryone\\Dot.obj");
    vecpoints = read.ReadPoints("D:\\Dropbox\\Repos\\Computer_Graphics_SoSe_2021\\Assignments\\Week 3\\Homework_Everyone\\HomeworkEveryone\\Dot.obj");
    //vecpoints = read.ReadPoints("C:\\Users\\Melam\\Documents\\GitHub\\Computer_Graphics_SoSe_2021\\Assignments\\Week 3\\Homework_Everyone\\HomeworkEveryone\\Dot.obj");
}


void OGLWidget::paintGL() // draw everything, to be called repeatedly
{
    //cout <<"paintGL "<< endl;
    glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0.8, 0.8, 1.0, 1.0); // bright blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();				// Reset The Current Modelview Matrix
    glTranslated( 0 ,0 ,-10.0);     // Move 10 units backwards in z, since camera is at origin
    glScaled( 1.0, 1.0, 1.0);       // scale objects
    //glRotated( alpha, 0, 3, 1);     // continuous rotation
    //alpha += 5;

    // define color: 1=front, 2=back, 3=both, followed by r, g, and b
    SetMaterialColor( 1, 1.0, .2, .2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue

    //draw lines with Chaikin algorithm
    DrawLineChaikin();

    //draw lines with Cubic algorithm
    //DrawLineCubic();

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

