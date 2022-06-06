#include<iostream> 
#include <cmath> 
#include <cstring>
#include <fstream>  
#include <stdlib.h>
//#include "mkl.cpp"
//#include "openblas.cpp"
//#include "multpthread.cpp"
#include <chrono>
#include <algorithm>
#include "dnn_weights.h"
#include "libaudio.h"
using namespace std;
using namespace std::chrono;


int main(int argc, char *argv[])
{

    if(argc==3)
    {
    	string labels[12] = {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};

    
    pred_t top_three_struct[3];
    pred_t* p = top_three_struct;

    libaudioAPI(argv[1], p);

    std::ofstream outfile;
    outfile.open(argv[2], std::ios_base::app); // append instead of overwrite
    outfile << argv[1] << " "<< labels[top_three_struct[0].label]<< " "<< labels[top_three_struct[1].label]<< " "<< labels[top_three_struct[2].label]<< " "<< top_three_struct[0].prob<< " "<< top_three_struct[1].prob<< " "<< top_three_struct[2].prob <<endl;
    }
    else
    {
    	cout<<"Please enter the arguments in the correct format as per README.txt\n";
    }
    

    return 0;

    //output 3c257192_nohash_3, 'stop', 'stop',1.87E-18,1.11E-06,4.26E-11,1.71E-09,1.97E-05,2.22E-10,1.37E-08,2.72E-13,4.19E-10,2.77E-06,0.9999764,1.13E-08
}
