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


class Vertex
{
public:
    float xyz[3];
    int w;
    Vertex();
    Vertex(float x, float y, float z);
    Vertex( float point[3]);
};

#endif // VERTEX_H
