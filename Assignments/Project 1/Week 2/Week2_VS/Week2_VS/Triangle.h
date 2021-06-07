#include "Vertex.h"
#include "Face.h"

class Triangle
{
public:
	Vertex x, y, z;
	Face one, two, three, four;

	Triangle(Vertex _x, Vertex _y, Vertex _z, Face _one, Face _two, Face _three, Face _four)
	{
		x = _x;
		y = _y;
		z = _z;
		one = _one;
		two = _two;
		three = _three;
		four = _four;
	}
};

