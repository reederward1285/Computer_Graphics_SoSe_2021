#include "readobj.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ReadObj::ReadObj()
{

}

vector<vector<float>> ReadObj:: ReadPoints( string fname){
    vector<vector<float>> vecpoints;
    vector<float> xpoints;
    vector<float> ypoints;
    vector<float> zpoints;

    ifstream file( fname);

    //Error message if data cannot be read in
    if (!file) {
        cout << "error opening file" << endl;
        return vecpoints;
    }
    string key;
    float x, y, z;
    while( file >> key >> x >> y >> z){
        //getline( file, line);
        //Output of the data for vertex and faces on the console

        cout << key <<", "<< x <<", "<< y <<", "<< z << endl;

        //Saving the data in objects of the Vertex and Triangle class
        //Insert objects into the corresponding vectors
        if (key.compare("v")==0) {
            xpoints.push_back(x);
            ypoints.push_back(y);
            zpoints.push_back(z);

        }
    }
    vecpoints.push_back(xpoints);
    vecpoints.push_back(ypoints);
    vecpoints.push_back(zpoints);
    file.close();

    //cout <<"ReadPoints"<< endl;
    return vecpoints;
}


