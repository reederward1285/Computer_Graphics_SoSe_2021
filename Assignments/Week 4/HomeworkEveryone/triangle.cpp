/**
 * @file triangle.cpp
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

//NEW
#include "triangle.h"
#include "readobj.h"
#include "vertex.h"

//ReadObj readobj;

Triangle::Triangle()
{

}
Triangle::Triangle(int i, int j, int k)
{
    iv[0] = i;
    iv[1] = j;
    iv[2] = k;
    normalVector();
}
Triangle::Triangle( int i[3])
{
    iv[0] = i[0];
    iv[1] = i[1];
    iv[2] = i[2];
}

void Triangle::normalVector()
{
/*
    Vertex a = readobj.points[iv[0]];
    Vertex b = readobj.getVertex(iv[1]);
    Vertex c = getVertex[iv[2]];
    Vertex nvec = (b-a)%(c-a);
    */

}
/**
 * @brief Triangle::print prints all points indecies
 * @param description specific description for console output
 */
void Triangle::print(string description)
{
    cout << description << "[ " << iv[0] << "; " << iv[1] << "; " << iv[2] << " ]" << endl;
}

