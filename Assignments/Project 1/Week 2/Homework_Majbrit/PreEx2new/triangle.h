/**
 * @file triangle.h
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H


class Triangle
{
public:
    int firstIndex, secondIndex, thirdIndex;
    Triangle();
    Triangle(int firstIndex, int secondIndex, int thirdIndex);
};

#endif // TRIANGLE_H
