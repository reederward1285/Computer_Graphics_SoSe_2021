#include "oglwidget.h"
#include <math.h>

//NEW
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//NEW
vector <Vertex> points;
vector <Triangle> tris;

#define PI 3.14159265358979323846


static double alpha = 45.0; // rotation angle


//---

//NEW


void ReadData( string fname){ //parser
    ifstream file( fname);
    //Error message if data cannot be read in
    if (!file) {
        cout << "error opening file" << endl;
        return;
    }
    string key;
    float x, y, z;
    while( file >> key >> x >> y >> z){
        //getline( file, line);
        //Output of the data for vertex and faces on the console

        cout << key <<", "<< x <<", "<< y <<", "<< z << endl;

        //Saving the data in objects of the Vertex and Triangle class
        //Insert objects into the corresponding vectors
        if (key.compare("v")==0) {
            Vertex v = *new Vertex(x, y, z);
            points.push_back(v);
        } else {
            Triangle t = *new Triangle(x, y, z);
            tris.push_back(t);
        }
    }
    file.close();
}

//Calculate normal vector (crossproduct of two edges)
void cross( float c[3], float ac[3], float bc[3]){ // c = a cross b
    c[0] = ac[1]*bc[2] - ac[2]*bc[1];
    c[1] = ac[2]*bc[0] - ac[0]*bc[2];
    c[2] = ac[0]*bc[1] - ac[1]*bc[0];
};



//---




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

//---

//NEW
void DrawTriangleMesh(){ // drawing a triangle mesh (here tetra)


    glBegin( GL_TRIANGLES); // each 3 points define a triangle
    //Variables
    //for indeces of the vertexes
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    //for points of triangle
    float a[3];
    float b[3];   
    float d[3];
    //for normal vector
    float c[3];
    //for edge vector
    float ac[3];
    float bc[3];

    for( int i=0; i<tris.size(); i++){
        //read indices
        t1 = tris[i].firstIndex -1;
        t2 = tris[i].secondIndex -1;
        t3 = tris[i].thirdIndex -1;

        //Save points of triangles in vectors
        a[0] = points[t1].x;
        a[1] = points[t1].y;
        a[2] = points[t1].z;

        b[0] = points[t2].x;
        b[1] = points[t2].y;
        b[2] = points[t2].z;

        d[0] = points[t3].x;
        d[1] = points[t3].y;
        d[2] = points[t3].z;

        //Calculate vectors of the edges
        ac[0] = points[t1].x-points[t3].x;
        ac[1] = points[t1].y-points[t3].y;
        ac[2] = points[t1].z-points[t3].z;

        bc[0] = points[t2].x-points[t3].x;
        bc[1] = points[t2].y-points[t3].y;
        bc[2] = points[t2].z-points[t3].z;

        //Calculate normal vector
        cross( c, ac, bc);

        //draw tetra
        glNormal3fv( c); // normal vector used for all consecutive points
        glVertex3fv( a); //
        glVertex3fv( b);
        glVertex3fv( d);

    }
    glEnd(); // concludes

}


//---


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
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 50 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
}

OGLWidget::~OGLWidget() // destructor
{
}

void OGLWidget::stepAnimation()
{
    animstep++;    // Increase animation steps
    update();      // Trigger redraw of scene with paintGL
}

void OGLWidget::initializeGL() // initializations to be called once
{
    initializeOpenGLFunctions();

    InitLightingAndProjection(); // define light sources and projection
//NEW
    ReadData("C:\\Users\\Melam\\Documents\\GitHub\\Computer_Graphics_SoSe_2021\\Assignments\\Week 2\\Homework_Majbrit\\PreEx2new\\tetra.obj");
}

void OGLWidget::paintGL() // draw everything, to be called repeatedly
{
    glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0.8, 0.8, 1.0, 1.0); // bright blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();				// Reset The Current Modelview Matrix
    glTranslated( 0 ,0 ,-10.0);     // Move 10 units backwards in z, since camera is at origin
    glScaled( 1.0, 1.0, 1.0);       // scale objects
    glRotated( alpha, 0, 3, 1);     // continuous rotation
    alpha += 5;

    // define color: 1=front, 2=back, 3=both, followed by r, g, and b
    SetMaterialColor( 1, 1.0, .2, .2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue

    //NEW
    // draw a triangle mesh (here tetra)
    DrawTriangleMesh();


    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLWidget::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}

