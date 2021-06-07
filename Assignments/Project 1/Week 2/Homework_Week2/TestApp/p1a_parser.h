#ifndef P1A_PARSER_H
#define P1A_PARSER_H
#pragma once

#include "triangle.h"
#include "vertex.h"
#include "face.h"
#include <string>
#include <vector>
using namespace std;


class p1a_Parser
{
public:
    p1a_Parser(void)
    {

    }
    void ReadData(string fname, vector<Vertex> points, vector<Face> faces);
};

#endif // P1A_PARSER_H
