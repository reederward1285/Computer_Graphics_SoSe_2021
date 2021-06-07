/**
 * @file triangle.cpp
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

//NEW
#include "triangle.h"


Triangle::Triangle()
{

}
Triangle::Triangle(int firstIndex, int secondIndex, int thirdIndex) {
    this->firstIndex = firstIndex;
    this->secondIndex = secondIndex;
    this->thirdIndex = thirdIndex;
}
