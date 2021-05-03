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


Triangle::Triangle()
{

}
Triangle::Triangle(int i, int j, int k)
{
    indices[0] = i;
    indices[1] = j;
    indices[2] = k;
}
Triangle::Triangle( int i[3])
{
    indices[0] = i[0];
    indices[1] = i[1];
    indices[2] = i[2];
}
