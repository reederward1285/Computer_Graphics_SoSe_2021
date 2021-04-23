#include "p1a_parser.h"
#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
p1a_Parser::p1a_Parser()
{

    class p1a_Parser
    {


        void ReadData( string fname) //fname = "F:\\CG21\\MeshOpenGL\\mesh1.obj";
        {
            ifstream file( fname);
            if (!file)
            {
               cout << "error opening file" << endl;
               return;
            }
            string key;
            float x, y, z;
            while(file)
               {
                   //getline( file, line);
                   file >> key >> x >> y >> z;
                   cout << key <<", "<< x <<", "<< y <<", "<< z << endl;
               }
            file.close();
       }

    };

}
