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
    iv[0] = i;
    iv[1] = j;
    iv[2] = k;
}
Triangle::Triangle( int i[3])
{
    iv[0] = i[0];
    iv[1] = i[1];
    iv[2] = i[2];
}
