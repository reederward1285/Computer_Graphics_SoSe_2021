#include "mesh.h"

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



Mesh::Mesh()
{

}

Mesh::Mesh(vector<Vertex> pts, vector<Triangle> tris)
{
    this-> pts = pts;
    this-> tris = tris;
    normalVector();
    connectAlg();
}

void Mesh::normalVector()
{
    //Variables
    //for indeces of the vertexes
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;

    //for normal vector
    Vertex normalvec;
    //for edge vector
    Vertex edge1;
    Vertex edge2;

    for(unsigned int i=0; i<tris.size(); i++){
        //read indices
        t1 = tris[i].iv[0];
        t2 = tris[i].iv[1];
        t3 = tris[i].iv[2];

        //Calculate vectors of the edges
        edge1 = pts[t2]-pts[t1];
        edge2 = pts[t3]-pts[t1];

        //Calculate normal vector
        normalvec = edge1%edge2;

        //save normal vector in Triangle class
        tris[i].nvec = normalvec;

        //save normal vector in Mesh class vector
        nvec.push_back(normalvec);
    }
}

void Mesh::connectAlg()
{
    //valences!!!
    //int neigbors[pts.size()];
    for(unsigned int i=0; i<pts.size(); i++){
        valences.push_back(0);
    }
    bool test1;
    bool test2;
    bool test3;
    for(unsigned int t=0; t<tris.size(); t++){
        for(unsigned int tn=0; tn<tris.size(); tn++){
            test1 = (tris[t].iv[0]==tris[tn].iv[0] || tris[t].iv[0]==tris[tn].iv[1] || tris[t].iv[0]==tris[tn].iv[2]);
            test2 = (tris[t].iv[1]==tris[tn].iv[0] || tris[t].iv[1]==tris[tn].iv[1] || tris[t].iv[1]==tris[tn].iv[2]);
            test3 = (tris[t].iv[2]==tris[tn].iv[0] || tris[t].iv[2]==tris[tn].iv[1] || tris[t].iv[2]==tris[tn].iv[2]);
            //find t0!=t containing b and c (CG21_1 page 19)
            if(test2 && test3 && !test1){
                tris[t].it[0]=tn;
            }
            //find t1!=t containing c and a (CG21_1 page 19)
            if(test3 && test1 && !test2){
                tris[t].it[1]=tn;
            }
            //find t2!=t containing a and b (CG21_1 page 19)
            if(test1 && test2 && !test3){
                tris[t].it[2]=tn;
            }
        }
        valences[tris[t].iv[0]] += 1;
        valences[tris[t].iv[1]] += 1;
        valences[tris[t].iv[2]] += 1;
    }

    cout << "Valence list (First vertex has index 0):" << endl;
    for(unsigned int i=0; i<pts.size(); i++){
        cout << "  Vertex" << i << ": " << valences[i];

    }
    cout << endl;
    cout << "Neighbor triangles of triangles (First triangle has index 0): " << endl;
    for(Triangle tri: tris){
        tri.printNeigbors();
    }


}

vector<Vertex> Mesh::getNvec()
{
    return nvec;
}

vector<Vertex> Mesh::getPts()
{
    return pts;
}

vector<Triangle> Mesh::getTris()
{
    return tris;
}
