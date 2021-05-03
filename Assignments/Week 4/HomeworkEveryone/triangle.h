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
    int iv[3]; // vertex indices
    int it[3]; // adjacent triangle indices
    int ie[3]; // edge vertex indices
    Triangle();
    Triangle( int i[3]);
    Triangle( int i, int j, int k);
};

#endif // TRIANGLE_H
