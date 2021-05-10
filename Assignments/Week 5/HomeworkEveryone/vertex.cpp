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

void Vertex::operator*=(float a)
{
    // need to test this function and implement it into the calculation routine
    xyz[0] = xyz[0] * a;
    xyz[1] = xyz[1] * a;
    xyz[2] = xyz[2] * a;
}

void Vertex::operator+=(Vertex a)
{
    // need to test this function and implement it into the calculation routine
    xyz[0] = xyz[0] + a.xyz[0];
    xyz[1] = xyz[1] + a.xyz[1];
    xyz[2] = xyz[2] + a.xyz[2];
}


/**
 * @brief Vertex::print outputs x, y and z cooridinates of a vertex
 * @param description description of vertex
 */
void Vertex::print(string description )
{
    cout << description << "[ " << xyz[0] << "; " << xyz[1] << "; " << xyz[2] << " ]" << endl;
}

/**
 * @brief operator + adds two vertexes
 * @param a first Vertex
 * @param b second Vertex
 * @return result sum
 */
Vertex operator+ (Vertex a, Vertex b)
{
    return Vertex(a.xyz[0] + b.xyz[0], a.xyz[1] + b.xyz[1], a.xyz[2] + b.xyz[2]);
}

/**
 * @brief operator - subtracts second vertex from first vertex
 * @param a first Vertex
 * @param b second Vertex
 * @return result difference
 */
Vertex operator- (Vertex a, Vertex b)
{
    return Vertex(a.xyz[0] - b.xyz[0], a.xyz[1] - b.xyz[1], a.xyz[2] - b.xyz[2]);
}

/**
 * @brief operator * multiplies two vectors together
 * @param a is first vector
 * @param b is second vector
 * @return c is result vector
 */
float operator* (Vertex a, Vertex b)
{
    float c = a.xyz[0] * b.xyz[0] +
              a.xyz[1] * b.xyz[1] +
              a.xyz[2] * b.xyz[2];

    return c;
}

/**
 * @brief operator * multiplies a single value with a vector
 * @param s is skalar of type float
 * @param b is vector object
 * @return c is result vector
 */
Vertex operator* (float s, Vertex b)
{
    Vertex c = Vertex(
                        s*b.xyz[0],
                        s*b.xyz[1],
                        s*b.xyz[2]
                     );
    return c;
}

/**
 * @brief operator * multiplies a single value with a vector (mirrored)
 * @param s is skalar of type float
 * @param b is vector object
 * @return result vector
 */
Vertex operator* (Vertex b, float s)
{
    return s*b;
}

/**
 * @brief operator % calculates the cross product of two vertices
 * @param a first Vertex
 * @param b second Vertex
 * @return c result Vertex
 */
Vertex operator% (Vertex a, Vertex b)
{
    Vertex c;
    c.xyz[0] = a.xyz[1]*b.xyz[2] - a.xyz[2]*b.xyz[1];
    c.xyz[1] = a.xyz[2]*b.xyz[0] - a.xyz[0]*b.xyz[2];
    c.xyz[2] = a.xyz[0]*b.xyz[1] - a.xyz[1]*b.xyz[0];

    return c;
}

Vertex operator/ (Vertex a, float s)
{
    Vertex c = Vertex(
                        a.xyz[0]/s,
                        a.xyz[1]/s,
                        a.xyz[2]/s
                     );
    return c;
}

