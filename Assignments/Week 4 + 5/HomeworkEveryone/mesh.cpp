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
    // empty constructor
}

/**
 * @brief Mesh::Mesh Constructor for calculating a mesh
 * @param pts vector with all Vertexes
 * @param tris vector with all Triangles
 */
Mesh::Mesh(vector<Vertex> pts, vector<Triangle> tris)
{
    this-> pts = pts;
    this-> tris = tris;

    //validate values
    this->validate();

    //for first subdivision
    connectAlg();
    linearSubdivisionAlg();
    //for second subdivision
    connectAlg();
    linearSubdivisionAlg();

}

/**
 * @brief Mesh::normalVector calculates normal vector of every Triangle
 */
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

/**
 * @brief Mesh::connectAlg finds neigbor Triangles of every Triangle and no. of triangles for every point
 */
void Mesh::connectAlg()
{
    //delete old no. of triangles for every point
    valences.clear();

    //fill vector of no. of triangles for every point with 0
    for(unsigned int i=0; i<pts.size(); i++){
        valences.push_back(0);
    }

    bool test1;
    bool test2;
    bool test3;
    //for every Triangle in tris find the 3 neighbor Triangles
    for(unsigned int t=0; t<tris.size(); t++){
        for(unsigned int tn=0; tn<tris.size(); tn++){
            //For first, second and third point of triangle test if it occurs in the other triangle
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
        //increase no. of triangles for the point of the triangle
        valences[tris[t].iv[0]] += 1;
        valences[tris[t].iv[1]] += 1;
        valences[tris[t].iv[2]] += 1;
    }

    //output results
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

/**
 * @brief Mesh::linearSubdivisionAlg calculates edge points
 */
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
    //triangle
    Triangle t;
    //triangle neigbor
    Triangle n;
    Vertex e = Vertex();

    //matrix indices of iv
    int mv[3][3] = {{1, 2, 0}, {2, 0, 1}, {0, 1, 2}};

    //for every triangle calculate edge points
    for(int i = 0; i < (int)tris.size(); i++)
    {
        t = tris[i];
        //for the 3 edge points of a triangle
        for(int j=0; j<3; j++)
        {
            i1 = mv[j][0];
            i2 = mv[j][1];
            i3 = mv[j][2];

            //neigbor Triangle
            n = tris[t.it[j]];

            //calculate edge point if index of triangle is smaller than index of neigbor
            //otherwise the edge point is already calculated
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

    //output results
    cout << "Triangle edge vertex index: " << endl;
    for(unsigned int i=0; i<tris.size(); i++){
        cout << "  Triangle " << i <<": ie = [ " << tris[i].ie[0] << "; "<< tris[i].ie[1] << "; " << tris[i].ie[2] << " ]" << endl;
    }

    createNewTriangles();
}

/**
 * @brief Mesh::createNewTriangles calculates smaller triangles with new corners
 */
void Mesh::createNewTriangles()
{
    vector<Triangle> trisnew;
    for(Triangle t: tris)
    {
        //calculate middle triangle
        Triangle t2 = Triangle(t.ie[0], t.ie[1], t.ie[2]);

        //calculate triangles around the middle triangle
        Triangle t0 = Triangle(t.ie[1], t.ie[0], t.iv[2]);
        Triangle t1 = Triangle(t.iv[0], t.ie[2], t.ie[1]);
        Triangle t3 = Triangle(t.ie[2], t.iv[1], t.ie[0]);        

        trisnew.push_back(t0);
        trisnew.push_back(t1);
        trisnew.push_back(t2);
        trisnew.push_back(t3);
    }
    tris = trisnew;

    normalVector();
}

/**
  * @brief Mesh::validate iterates through all containing values and checks for wrong values
  * @return boolean, true when all values correct else false
  *
  * @todo put function on top of the constructor in mesh class to avoid following calculation
  * problems of the ojects
  */
bool Mesh::validate()
{
    // check all points for NULL
    for(unsigned int i = 0; i <= this->pts.size(); i++)
    {
        // todo: which values are not allowed instead of NULL?
        if( this->pts[i].xyz[0] == NULL){

            cout << "ERROR wrong value: pts[" << i << "].x == NULL" << endl;

        } else if ( this->pts[i].xyz[1] == NULL) {

            cout << "ERROR wrong value: pts[" << i << "].y == NULL" << endl;

        } else if ( this->pts[i].xyz[2] == NULL) {

            cout << "ERROR wrong value: pts[" << i << "].z == NULL" << endl;
        }
   // cout << "Mesh::validate() successd" << endl;
    }

    /*
    for(unsigned int i = 0; i <= this->tris.size(); i++)
    {

    }
    */
}

/**
 * @brief Mesh::getNvec normal vector
 * @return nvec normal vector of every triangle
 */
vector<Vertex> Mesh::getNvec()
{
    return nvec;
}

/**
 * @brief Mesh::getPts points
 * @return pts all points
 */
vector<Vertex> Mesh::getPts()
{
    return pts;
}

/**
 * @brief Mesh::getTris triangles
 * @return tris all triangles
 */
vector<Triangle> Mesh::getTris()
{
    return tris;
}
