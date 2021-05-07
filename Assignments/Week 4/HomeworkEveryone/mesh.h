#ifndef MESH_H
#define MESH_H
#include "vertex.h"
#include "triangle.h"
#include <vector>
#include <stdbool.h>


class Mesh
{
public:
    Mesh();
    Mesh(vector<Vertex> pts, vector<Triangle> tris);
    void normalVector();
    void connectAlg();
    void linearSubdivisionAlg();
    void createNewTriangles();
    bool validate(); // used to validate correctnes of containing values
    vector<Vertex> getNvec();
    vector<Vertex> getPts();
    vector<Triangle> getTris();
    vector <Vertex> pts;
    vector <int> valences;
    vector <Triangle> tris;
    vector <Vertex> nvec; // normal vector (check later if this is still needed)
};

#endif // MESH_H
