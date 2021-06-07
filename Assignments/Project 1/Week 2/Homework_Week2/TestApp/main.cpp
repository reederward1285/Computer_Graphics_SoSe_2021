#include "p1a_parser.h"
#include "triangle.h"
#include "vertex.h"
#include <iostream>
#include <vector>
#include <QApplication>
using namespace std;

int main()
{
    vector<Vertex> points;
    vector<Face> faces;

    string filepoints = "D:\\Dropbox\\Repos\\Computer_Graphics_SoSe_2021\\Assignments\\Objects\\tetra.obj";
    p1a_Parser test;
    test.ReadData(filepoints, points, faces);

    return 0;
}
