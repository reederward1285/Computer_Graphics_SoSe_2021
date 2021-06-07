// Priority Queue Example with Data Structure for Fractions
// Author: Majbrit
// Date: 19.4.2021

#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

// class representing fractions of integers
class complex{
public:
    int real, imag;

    complex(); // empty constructor
    complex( int a, int b); // constructor with initialization

    friend bool operator<( complex x, complex y); // less operator
};

complex::complex(){}; // empty constructor

complex::complex( int a, int b){ // constructor with initialization
    real = a;
    imag = b;
}

bool operator<( complex x, complex y){ // less operator
    return pow(x.real,2) + pow((float)x.imag,2) < pow(y.real,2) + pow((float)y.imag,2);
}

int main()
{
    const int n=5; // number of data elements
    int real[n] = {4, 4, 4, 2, 2};
    int imag[n]  = {5, 7, 9, 3, 6};
    complex b;

    // queue containing fractions
    priority_queue< complex, vector<complex>, less<complex> > Q;

    // fill queue with data
    cout << "The input list is:" << endl;
    for( int i=0; i<n; i++){
        b = complex( real[i], imag[i]);
        Q.push( b);
        cout << b.real << "+" << b.imag << "i" << endl;
    }
    cout << endl;

    // print sorted list
    cout << "The sorted list is:" << endl;
    while( Q.size() > 0)
    {
        cout << Q.top().real << "+" << Q.top().imag  << "i" << endl;
        Q.pop(); // remove element from queue
    }
}
