/**
 * @file interpolatingcubicsubdivision.h
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

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
    vector<vector<float>> cubicAlg(vector<float> xold, vector<float> yold, vector<float> zold);
};

#endif // INTERPOLATINGCUBICSUBDIVISION_H
