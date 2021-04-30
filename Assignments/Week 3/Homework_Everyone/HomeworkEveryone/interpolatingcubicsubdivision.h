#ifndef INTERPOLATINGCUBICSUBDIVISION_H
#define INTERPOLATINGCUBICSUBDIVISION_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class InterpolatingCubicSubdivision
{
public:
    InterpolatingCubicSubdivision();
public:
    vector<vector<float>> CubicAlg(vector<float> xold, vector<float> yold, vector<float> zold);
};

#endif // INTERPOLATINGCUBICSUBDIVISION_H
