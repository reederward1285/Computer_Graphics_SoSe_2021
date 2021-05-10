/**
 * @file readobj.cpp
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

#include "readobj.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "triangle.h"
#include "vertex.h"
using namespace std;


ReadObj::ReadObj()
{

}

/**
 * @brief ReadObj::ReadPoints reads points from a .obj file
 * @param fname path to the file
 * @return vector of points
 */
vector<vector<float>> ReadObj:: ReadPoints( string fname){
    vector<vector<float>> vecpoints;
    vector<float> xpoints;
    vector<float> ypoints;
    vector<float> zpoints;

    ifstream file( fname);

    //Error message if data cannot be read in
    if (!file) {
        cout << "error opening file" << endl;
        return vecpoints;
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

        }
    }
    vecpoints.push_back(xpoints);
    vecpoints.push_back(ypoints);
    vecpoints.push_back(zpoints);
    file.close();

    //cout <<"ReadPoints"<< endl;
    return vecpoints;
}

/**
 * @brief ReadObj::ReadTriangle reads points from a .obj file and creates Vertex and Triangle objects
 * @param fname path to the file
 */
void ReadObj:: ReadTriangle( string fname){
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
            Triangle t = *new Triangle(x-1, y-1, z-1);
            tris.push_back(t);
        }

    }

    file.close();

    //cout <<"ReadTriangle"<< endl;
}

vector<Vertex> ReadObj::getPoints()
{
    return points;
}


vector<Triangle> ReadObj::getTris()
{
    return tris;
}




