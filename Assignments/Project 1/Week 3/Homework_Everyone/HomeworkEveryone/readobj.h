/**
 * @file readobj.h
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */


#ifndef READOBJ_H
#define READOBJ_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class ReadObj
{
public:
    ReadObj();
public:
    vector<vector<float>> ReadPoints( string fname);
    void ReadTriangle( string fname);
};

#endif // READOBJ_H
