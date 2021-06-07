#pragma once
class Face
{
public:
    float x, y, z;

    Face::Face()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Face::Face(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

