#include "oglwidget.h"
#include <math.h>

//NEW
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "readobj.h"


using namespace std;



ReadObj read = *new ReadObj();

vector <Vertex> points;
vector <Triangle> tris;

//needed
vector <vector<float>> vecpoints;

/*
vector <float> xnew;
vector <float> ynew;
vector <float> znew;
vector <float> xnewn;
vector <float> ynewn;
vector <float> znewn;
*/


#define PI 3.14159265358979323846
void SetMaterialColor( int side, float r, float g, float b);



//static double alpha = 45.0; // rotation angle


//---

//NEW

/*
void ReadData( string fname){
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
            xpoints.push_back(x);
            ypoints.push_back(y);
            zpoints.push_back(z);
            Vertex v = *new Vertex(x, y, z);
            points.push_back(v);
        } else {
            Triangle t = *new Triangle(x, y, z);
            tris.push_back(t);
        }

    }
    vecpoints.push_back(xpoints);
    vecpoints.push_back(ypoints);
    vecpoints.push_back(zpoints);
    file.close();

    cout <<"ReadData"<< endl;

    cout <<"xpoints "<< xpoints.size() << endl;



}
*/







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



vector<vector<float>> Chaikin(vector<float> xold, vector<float> yold, vector<float> zold) {
    //vector matrix for the points calculated in the algorithm
    vector<vector<float>> xyznew;
    vector <float> xnew;
    vector <float> ynew;
    vector <float> znew;

    //---calculate mask---
    //size of the matrix
    int columns = xold.size();
    int lines = (columns-1)*2;
    float matrix[lines][columns];
    //fill martrix with 0
    for( int i=0; i<lines; i++) {
        for( int j=0; j<columns; j++) {
            matrix[i][j] = 0;
        }
    }
    //fill center of the matrix
    int c = columns-2;
    int l = (lines-3)*2;
    int i=2;
    int j=1;
    while( i<l) {
        while(  j<c) {
            matrix[i][j] = 0.75;
            matrix[i][j+1] = 0.25;
            matrix[i+1][j] = 0.25;
            matrix[i+1][j+1] = 0.75;
            j=j+1;
            break;
        }
        i=i+2;
    }
    //fill first two and last two lines of the matrix
    matrix[0][0] = 1.0;
    matrix[1][1] = 0.5;
    matrix[1][0] = 0.5;
    matrix[lines-1][columns-1] = 1.0;
    matrix[lines-2][columns-1] = 0.5;
    matrix[lines-2][columns-2] = 0.5;

    //---matrix multiplication---
    float xproduct = 0;
    float yproduct = 0;
    float zproduct = 0;
    for( int i=0; i<lines; i++) {
        xproduct = 0;
        yproduct = 0;
        zproduct = 0;
        for( int j=0; j<columns; j++) {
            //calculate x,y and z of one new point
            xproduct += matrix[i][j]*xold[j];
            yproduct += matrix[i][j]*yold[j];
            zproduct += matrix[i][j]*zold[j];
        }
        //insert new coordinates in vectors
        xnew.push_back(xproduct);
        ynew.push_back(yproduct);
        znew.push_back(zproduct);
    }
    xyznew.push_back(xnew);
    xyznew.push_back(ynew);
    xyznew.push_back(znew);

    //return calculated points
    return xyznew;
}

void DrawLine() {

    //---Connecting the points---
    //set color of the line
    SetMaterialColor( 1, 0.2, 1.0, .2);
    //draw line
    glBegin( GL_LINE_STRIP);
    for( int i=0; i<vecpoints[0].size(); i++){
        //glColor3f(0,1,0);
        glVertex3f( vecpoints[0][i], vecpoints[1][i], vecpoints[2][i]);
    }
    glEnd();

    //vector matrix for the points calculated in the algorithm
    vector<vector<float>> newpoints;

    //---first subdivision---
    //call Chaikin algorithm
    newpoints = Chaikin(vecpoints[0], vecpoints[1], vecpoints[2]);
    //set color of the line
    SetMaterialColor( 1, 1.0, .2, .2);
    //draw line
    glBegin( GL_LINE_STRIP);
    for( int i=0; i<newpoints[0].size(); i++){
        glVertex3f( newpoints[0][i], newpoints[1][i], newpoints[2][i]);
    }
    glEnd();

    //---second subdivision---
    newpoints = Chaikin(newpoints[0], newpoints[1], newpoints[2]);
    SetMaterialColor( 1, .2, .2, 1.0);
    glBegin( GL_LINE_STRIP);
    for( int i=0; i<newpoints[0].size(); i++){
        glVertex3f( newpoints[0][i], newpoints[1][i], newpoints[2][i]);
    }
    glEnd();

    //---third subdivision---
    newpoints = Chaikin(newpoints[0], newpoints[1], newpoints[2]);
    SetMaterialColor( 1, 1.0, 0.9, 0.2);
    glBegin( GL_LINE_STRIP);
    for( int i=0; i<newpoints[0].size(); i++){
        glVertex3f( newpoints[0][i], newpoints[1][i], newpoints[2][i]);
    }
    glEnd();
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
    /*
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 50 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
    */
    cout <<"OGLWidget "<< endl;
}

OGLWidget::~OGLWidget() // destructor
{
    cout <<"OGLWidget destructor "<< endl;
}

/*
void OGLWidget::stepAnimation()
{
   // animstep++;    // Increase animation steps
    //update();      // Trigger redraw of scene with paintGL
    cout <<"stepAnimator "<< endl;
}
*/

void OGLWidget::initializeGL() // initializations to be called once
{
    cout <<"InitializeGL "<< endl;
    initializeOpenGLFunctions();

    InitLightingAndProjection(); // define light sources and projection
//NEW
    vecpoints = read.ReadPoints("C:\\majbrit\\Medieninformatik\\Semester 4\\ComputerGraphics\\Aufgaben\\3\\HomeworkEveryone\\Dot.obj");
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


    //NEW
    // draw a triangle mesh (here tetra)
    //DrawTriangleMesh();

    DrawLine();


    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}
/*
void OGLWidget::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}
*/

