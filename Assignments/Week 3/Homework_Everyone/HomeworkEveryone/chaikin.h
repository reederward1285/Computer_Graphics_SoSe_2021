#ifndef CHAIKIN_H
#define CHAIKIN_H

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class Chaikin
{
public:
    Chaikin();
public:
    vector<vector<float>> ChaikinAlg(vector<float> xold, vector<float> yold, vector<float> zold);
};

#endif // CHAIKIN_H
