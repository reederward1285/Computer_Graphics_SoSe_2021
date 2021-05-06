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

    connectAlg();
    linearSubdivisionAlg();
    connectAlg();
    linearSubdivisionAlg();

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

    valences.clear();
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
        cout << "  Vertex " << i << ": " << valences[i];

    }
    cout << endl;
    cout << "Neighbor triangles of triangles (First triangle has index 0): " << endl;
    for(unsigned int i=0; i<tris.size(); i++){
        cout << "  Triangle " << i << ": " ;
        tris[i].printNeigbors();
    }
}

void Mesh::linearSubdivisionAlg()
{
    /*
    //---with formula---
    //variable for new Vertex
    Vertex d = Vertex();
    bool test1;
    bool test2;
    bool test3;
    */

    int i1;
    int i2;
    int i3;
    Triangle t;
    Triangle n;
    Vertex e = Vertex();

    //matrix ...
    int mv[3][3] = {{1, 2, 0}, {2, 0, 1}, {0, 1, 2}};

    for(unsigned int i = 0; i < tris.size(); i++)
    {
        t = tris[i];
        for(int j=0; j<3; j++)
        {
            i1 = mv[j][0];
            i2 = mv[j][1];
            i3 = mv[j][2];

            //neigbor Triangle
            n = tris[t.it[j]];

            if(i<t.it[j])
            {
                /*
                //---with formula---
                //find Vertex in neigbor Triangle that is not in Triangle t
                test1 = t.iv[i1]==n.iv[0] || t.iv[i2]==n.iv[0];
                test2 = t.iv[i1]==n.iv[1] || t.iv[i2]==n.iv[1];
                test3 = t.iv[i1]==n.iv[2] || t.iv[i2]==n.iv[2];

                if(!test1)
                {
                    d = pts[n.iv[0]];
                }else if(!test2)
                {
                    d = pts[n.iv[1]];
                }else if(!test3)
                {
                    d = pts[n.iv[2]];
                }

                cout<< "hier "<<endl;
                d.print();

                //with formula
                e = (pts[t.iv[i3]] + 3*pts[t.iv[i1]] + 3*pts[t.iv[i2]] +d) * 0.125;
                */

                //edge vertices
                e = (pts[t.iv[i1]] + pts[t.iv[i2]]) * 0.5;

                tris[i].ie[j] = pts.size();
                pts.push_back(e);


                //fill ie in neighbor Triangle
                if(i==n.it[0])
                {
                    tris[t.it[j]].ie[0] = pts.size()-1;
                }else if(i==n.it[1])
                {
                    tris[t.it[j]].ie[1] = pts.size()-1;
                }else if(i==n.it[2])
                {
                    tris[t.it[j]].ie[2] = pts.size()-1;
                }
            }
        }
    }


    cout << "Triangle edge vertex index: " << endl;
    for(unsigned int i=0; i<tris.size(); i++){
        cout << "   Triangle " << i <<": ie = [ " << tris[i].ie[0] << "; "<< tris[i].ie[1] << "; " << tris[i].ie[2] << " ]" << endl;
    }


    createNewTriangles();

}

void Mesh::createNewTriangles()
{
    vector<Triangle> trisnew;
    for(Triangle t: tris)
    {

        Triangle t0 = Triangle(t.ie[1], t.ie[0], t.iv[2]);
        Triangle t1 = Triangle(t.iv[0], t.ie[2], t.ie[1]);
        Triangle t3 = Triangle(t.ie[2], t.iv[1], t.ie[0]);

        Triangle t2 = Triangle(t.ie[0], t.ie[1], t.ie[2]);

        trisnew.push_back(t0);
        trisnew.push_back(t1);
        trisnew.push_back(t2);
        trisnew.push_back(t3);
    }
    tris = trisnew;

    normalVector();
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
