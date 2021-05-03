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

void Vertex::print(string description )
{
    cout << description << "[ " << xyz[0] << "; " << xyz[1] << "; " << xyz[2] << " ]" << endl;
}

Vertex operator%(Vertex a, Vertex b)
{
    Vertex c;
    c.xyz[0] = a.xyz[1]*b.xyz[2] - a.xyz[2]*b.xyz[1];
    c.xyz[1] = a.xyz[2]*b.xyz[0] - a.xyz[0]*b.xyz[2];
    c.xyz[2] = a.xyz[0]*b.xyz[1] - a.xyz[1]*b.xyz[0];

    return c;
}

Vertex operator-(Vertex a, Vertex b)
{
    Vertex c;
    c.xyz[0] = a.xyz[0] - b.xyz[0];
    c.xyz[1] = a.xyz[1] - b.xyz[1];
    c.xyz[2] = a.xyz[2] - b.xyz[2];

    return c;
}
