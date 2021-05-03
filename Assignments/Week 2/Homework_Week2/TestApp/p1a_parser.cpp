#pragma once
#include "p1a_parser.h"
#include <iostream>
#include <iostream>
#include "vertex.h"
#include "triangle.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void p1a_Parser::ReadData(string fname, vector<Vertex> points, vector<Face> faces) //fname = "F:\\CG21\\MeshOpenGL\\mesh1.obj";
{
    ifstream file(fname);

    if (!file)
    {
       cout << "error opening file" << endl;
       return;
    }

    string key;
    float x, y, z;

    while(file >> key >> x >> y >> z)
    {
        if (key == "v")
        {
            points.push_back(Vertex(x, y, z));
        }
        else if (key == "f")
        {
            faces.push_back(Face(x, y, z));
        }
        cout << key <<", "<< x <<", "<< y <<", "<< z << endl;
    }
    file.close();
}
