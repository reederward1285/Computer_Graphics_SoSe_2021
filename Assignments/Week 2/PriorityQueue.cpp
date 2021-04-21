// Priority Queue Example
// Author: MHB
// Date: 10.2017

#include <iostream>
#include <queue>
#include <math.h>
#include "complexnumber.h"
using namespace std;

void print(priority_queue< ComplexNumber, vector<ComplexNumber>, ComplexNumber.Compare() > Q)
{
  // print sorted list
  cout << "The sorted list is:" << endl;

  while (Q.size() > 0)
  {
    cout << Q.top() << endl;
    Q.pop(); // remove element from queue
  }
}

int main() // sorting integers using a priority queue
{
  // Make a for loop to call the ComplexNumber constructor
  cout << "Please input a list of complex numbers." << endl;
  cout << "Press enter in-between entering each complex number, " << endl;
  cout << "and when you are finished simply hit enter twice." << endl;
  cout << endl;

  // priority queue with integers in decreasing order
  priority_queue< ComplexNumber, vector<ComplexNumber>, ComplexNumber.Compare() > Q; // also use "greater"

  string inputComplex;
  cin >> inputComplex;

  // fill queue with data
  while (inputComplex != "")
  {
      Q.push(ComplexNumber(inputComplex));

      // read in the next line
      cin >> inputComplex;
  }
  cout << endl;
}
