/**
 * @file interpolatingcubicsubdivision.cpp
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

#include "interpolatingcubicsubdivision.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

InterpolatingCubicSubdivision::InterpolatingCubicSubdivision()
{

}

vector<vector<float>> InterpolatingCubicSubdivision::cubicAlg(vector<float> xold, vector<float> yold, vector<float> zold) {
    //vector matrix for the points calculated in the algorithm
    vector<vector<float>> xyznew;
    vector <float> xnew;
    vector <float> ynew;
    vector <float> znew;

    //---calculate mask---
    //size of the matrix
    int columns = xold.size();
    int lines = (columns-1)*2+1;
    float matrix[lines][columns];
    //fill martrix with 0
    for( int i=0; i<lines; i++) {
        for( int j=0; j<columns; j++) {
            matrix[i][j] = 0;
        }
    }
    //fill center of the matrix
    int c = columns-1;
    int l = (lines-3)*2;
    int i=2;
    int j=0;
    while( i<l) {
        while(  j<c) {
            matrix[i][j+1] = 1;
            matrix[i+1][j] = -0.0625;
            matrix[i+1][j+1] = 0.5625;
            matrix[i+1][j+2] = 0.5625;
            matrix[i+1][j+3] = -0.0625;
            j=j+1;
            break;
        }
        i=i+2;
    }
    //fill first two and last two lines of the matrix
    matrix[0][0] = 1.0;
    matrix[1][0] = 0.375;
    matrix[1][1] = 0.75;
    matrix[1][2] = -0.125;
    matrix[lines-1][columns-1] = 1.0;
    matrix[lines-2][columns-1] = 0.375;
    matrix[lines-2][columns-2] = 0.75;
    matrix[lines-2][columns-3] = -0.125;
    matrix[lines-3][columns-2] = 1.0;

    //---matrix multiplication---
    float xproduct = 0;
    float yproduct = 0;
    float zproduct = 0;
    for( int i=0; i<lines; i++) {
        xproduct = 0;
        yproduct = 0;
        zproduct = 0;
        for( int j=0; j<columns; j++) {
            //calculate x,y and z of one new point
            xproduct += matrix[i][j]*xold[j];
            yproduct += matrix[i][j]*yold[j];
            zproduct += matrix[i][j]*zold[j];
        }
        //insert new coordinates in vectors
        xnew.push_back(xproduct);
        ynew.push_back(yproduct);
        znew.push_back(zproduct);
    }
    xyznew.push_back(xnew);
    xyznew.push_back(ynew);
    xyznew.push_back(znew);

    //return calculated points
    return xyznew;
}
