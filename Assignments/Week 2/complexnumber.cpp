#include <iostream>
#include <queue>
#include <math.h>
#include <string>
#include "complexnumber.h"
using namespace std;

/**
 * Class to transcriped a string in format x5 + y3i to
 * real part x = 5, imaginary part y = 3 and z = sqrt( ((x)^2) + ((y)^2)) )
 *
 * Uses stoi() to convert String into integer.
 */
class ComplexNumber {
  public:
    int x; // realNumber
    int y; // imaginaryNumber
    double z; // absoluteNumber
    string complexNumber; // default format for complexNumber: z=x+iy
    ComplexNumber(string complexNumber) { // Constructor with parameters
      x = stoi(complexNumber.substr(complexNumber.find("x") + 1, complexNumber.find(" "))); // find place of x and adding 1
      y = stoi(complexNumber.substr(complexNumber.find("y") + 1, complexNumber.find("i")));
      z = sqrt(pow(x, 2) + pow(y,2));
   }
};

int main()
{
  ComplexNumber c1("x4+y2i");
  cout << "x: " << c1.x << ",\ny: " << c1.y << ",\nz: " <<  c1.z << "\n";
  return 0;
}
