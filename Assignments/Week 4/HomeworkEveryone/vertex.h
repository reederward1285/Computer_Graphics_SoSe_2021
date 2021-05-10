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
    float xyz[3];
    int w;
    
    Vertex();
    Vertex(float x, float y, float z);
    Vertex( float point[3]);
    
    void print(string description= "Vertex = ");

    friend Vertex operator+ (Vertex a, Vertex b);
    friend Vertex operator- (Vertex a, Vertex b);
    friend float operator* (Vertex a, Vertex b);
    friend Vertex operator* (float s, Vertex b);
    friend Vertex operator* (Vertex a, float s);
    friend Vertex operator%(Vertex a, Vertex b);

    void operator*=(float a);
    void operator+=(Vertex a);
    float beta_n(int n);
};

#endif // VERTEX_H
