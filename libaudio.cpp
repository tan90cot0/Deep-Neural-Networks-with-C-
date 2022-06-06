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
using namespace std;
using namespace std::chrono;

typedef struct{
    int label;
    float prob;
}pred_t;


void fileInp(float *vector, string filename, int n)
{

    ifstream file(filename);
    string data = "";
    if (file.is_open())  
    {   
            int i = 0;
            while(getline(file, data,' '))
                vector[i++]= stod(data);
            file.close();
    }  
   else
   {
       cout << "File not found."<<endl; 
       exit(0);
   }     
}

void matmul(float *result, float *A, float *B, int rows_A, int columns_A, int columns_B)
{
    float A2d[rows_A][columns_A];
    float B2d[columns_A][columns_B];
    for(int i = 0;i<columns_A;i++)
        for(int j = 0;j<rows_A;j++)
            A2d[j][i] = A[columns_A*j+i];

    for(int i = 0;i<columns_A;i++)
        for(int j = 0;j<columns_B;j++)
            B2d[i][j] = B[columns_B*i+j];

    for(int i = 0;i<rows_A;i++)
        for(int j = 0;j<columns_B;j++)
        {
            float sum = 0;
            for(int k = 0;k<columns_A;k++)
                    sum+=A2d[i][k]*B2d[k][j];
            result[columns_B*i+j] = sum;
        }
}

void row_to_col(float *A, int rows_A, int columns_A)
{
    float A2d[rows_A][columns_A];
    for(int i = 0;i<columns_A;i++)
        for(int j = 0;j<rows_A;j++)
            A2d[j][i] = A[columns_A*j+i];
    for(int i = 0;i<columns_A;i++)
        for(int j = 0;j<rows_A;j++)
            A[rows_A*i+j] = A2d[j][i];
}



void add_bias(float *result, float *input, float *bias, int n)
{
    for(int i = 0;i<n;i++)
        result[i] = input[i]+bias[i];
}

void relu(float *result, float*input, int mn)
{
    for(int i = 0;i<mn;i++)
    {
        if(input[i]<0)
            result[i] = 0;
        else
            result[i] = input[i];
    }       
}

float denominator(float *input, int n)
{
    float denom = 0;
    for(int i = 0;i<n;i++)
        denom+=exp(input[i]);
    return denom;
}

void softmax(float *result, float *input, int n)
{
    float denom = denominator(input, n);
    for(int i = 0;i<n;i++)
        result[i] = exp(input[i])/denom;
}

/*void print_arr(float *arr, int n)
{
    for(int i = 0;i<n;i++)
        cout<<arr[i]<<endl;
}*/

int find(float *arr, float x)
{
    int i =0;
    for(;i<12;i++)
        if(arr[i]==x)
            break;
    return i;
}

void arg_top_three(float *arr, int *top_three)
{
    float arr_copy[12];
    for(int i = 0;i<12;i++)
        arr_copy[i] = arr[i];
    sort(arr_copy, arr_copy+12);
    for(int i = 0;i<3;i++)
        top_three[i] = find(arr, arr_copy[11-i]);
}

pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred){

	float weights10[] = IP1_WT;
    float biases1[] = IP1_BIAS;
    float weights21[] = IP2_WT;  
    float biases2[] = IP2_BIAS; 
    float weights32[] = IP3_WT;  
    float biases3[] = IP3_BIAS; 
    float weights43[] = IP4_WT;  
    float biases4[] = IP4_BIAS; 

    float layer0[250];
    float layer1[144];
    float layer2[144];
    float layer3[144];
    float layer4[12];

    float temp144[144];
    float temp12[12];
    int top_three[3];
    

   // string labels[12] = {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    
    string filename = "";
    const char* q = audiofeatures;
    while (*q != '\0'){
    	filename += *q;
    	q++;
    }

    //name of input file example = "mfcc_features/3c257192_nohash_3.txt"
    fileInp(layer0, filename, 250);                //layer0 initialised

    //row_to_col(layer0,1,250);
    //row_to_col(weights10,250,144);
    
    //matmul_mkl(temp144, layer0, weights10, 1, 250, 144);
    matmul(temp144, layer0, weights10, 1, 250, 144);
    add_bias(temp144, temp144, biases1, 144);
    relu(layer1, temp144, 144);
    
    //row_to_col(layer1,1,144);
    //row_to_col(weights21,144,144);

    //matmul_mkl(temp144, layer1, weights21, 1, 144, 144);
    matmul(temp144, layer1, weights21, 1, 144, 144);
    add_bias(temp144, temp144, biases2, 144);
    relu(layer2, temp144, 144);
    
    //row_to_col(layer2,1,144);
    //row_to_col(weights32,144,144);
    
    //matmul_mkl(temp144, layer2, weights32, 1, 144, 144);
    matmul(temp144, layer2, weights32, 1, 144, 144);
    add_bias(temp144, temp144, biases3, 144);
    relu(layer3, temp144, 144);
    
    //row_to_col(layer3,1,144);
    //row_to_col(weights43,144,12);
    
    //matmul_mkl(temp12, layer3, weights43, 1, 144, 12);
    matmul(temp12, layer3, weights43, 1, 144, 12);
    add_bias(temp12, temp12, biases4, 12);
    softmax(layer4, temp12, 12);
    
    arg_top_three(layer4, top_three);
    
    for (int i=0; i<3; i++){
    	(pred + i)->label = top_three[i];
    	(pred + i)->prob = layer4[top_three[i]];
    }
	return pred;

}


