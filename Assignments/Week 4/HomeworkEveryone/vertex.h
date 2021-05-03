/**
 * @file vertex.h
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

class Vertex
{
public:
    // class members
    float xyz[3];
    int w;
    // class constructor
    Vertex();
    Vertex(float x, float y, float z);
    Vertex( float point[3]);
    // class methods
    void print(string description = "Vertex = ");
    // class friends
    friend Vertex operator* (float a, Vertex b); // product between scalat and vector
    friend Vertex operator* (Vertex b, float a); // mirrored calc above
    friend Vertex operator* (Vertex a, Vertex b); // scalar product
    friend Vertex operator+(Vertex a, Vertex b);
    friend Vertex operator%(Vertex a, Vertex b);
    friend Vertex operator-(Vertex a, Vertex b);
};

#endif // VERTEX_H
