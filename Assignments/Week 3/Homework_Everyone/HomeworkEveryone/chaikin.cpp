/**
 * @file chaikin.cpp
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

#include "chaikin.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

Chaikin::Chaikin()
{

}

vector<vector<float>> Chaikin:: ChaikinAlg(vector<float> xold, vector<float> yold, vector<float> zold) {
    //vector matrix for the points calculated in the algorithm
    vector<vector<float>> xyznew;
    vector <float> xnew;
    vector <float> ynew;
    vector <float> znew;

    //---calculate mask---
    //size of the matrix
    int columns = xold.size();
    int lines = (columns-1)*2;
    float matrix[lines][columns];
    //fill martrix with 0
    for( int i=0; i<lines; i++) {
        for( int j=0; j<columns; j++) {
            matrix[i][j] = 0;
        }
    }
    //fill center of the matrix
    int c = columns-2;
    int l = (lines-3)*2;
    int i=2;
    int j=1;
    while( i<l) {
        while(  j<c) {
            matrix[i][j] = 0.75;
            matrix[i][j+1] = 0.25;
            matrix[i+1][j] = 0.25;
            matrix[i+1][j+1] = 0.75;
            j=j+1;
            break;
        }
        i=i+2;
    }
    //fill first two and last two lines of the matrix
    matrix[0][0] = 1.0;
    matrix[1][1] = 0.5;
    matrix[1][0] = 0.5;
    matrix[lines-1][columns-1] = 1.0;
    matrix[lines-2][columns-1] = 0.5;
    matrix[lines-2][columns-2] = 0.5;

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
