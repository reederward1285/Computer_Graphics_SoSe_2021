/**
 * @file vertex.cpp
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

//NEW
#include "vertex.h"
#include <iostream>
using namespace std;

Vertex::Vertex()
{

}

Vertex::Vertex(float x, float y, float z)
{
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}

Vertex::Vertex( float point[3])
{
    xyz[0] = point[0];
    xyz[1] = point[1];
    xyz[2] = point[2];
}

void Vertex::print(string description = "Vertex = ")
{
    cout << description << "[ " << xyz[0] << "; " << xyz[1] << "; " << xyz[2] << " ]" << endl;
}
