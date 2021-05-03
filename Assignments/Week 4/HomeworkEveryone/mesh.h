#ifndef MESH_H
#define MESH_H
#include "vertex.h"
#include "triangle.h"
#include <vector>


class mesh
{
public:
    mesh();
    vector <Vertex> pts;
    vector <int> valences;
    vector <Triangle> tris;
    Vertex nvec; // normal vector (check later if this is still needed)
};

#endif // MESH_H
