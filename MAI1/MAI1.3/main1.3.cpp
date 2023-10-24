#include <iostream>
#include <climits>
#include <cstdlib>
#include <unistd.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("input.txt");
    int M, GRN;
    int VEC[8];
    
    if (in.is_open())
    {
        in>> M >> GRN;
        for(int i=0; i<8;++i){
            in >> VEC[i];
        }
    }
    in.close(); 

    int NEWVEC[10];
    int temp_sum = 0;
    for (int i = 0; i<10;++i){
        temp_sum += VEC[8-1-i];
        NEWVEC[i]= temp_sum;
    }
    NEWVEC[8]=GRN;
    int ABS_SUM=0;
    for(int i=0; i<M;++i){
        ABS_SUM +=abs(VEC[i]);
        NEWVEC[9]=ABS_SUM;
    }
    int TOTAL_SUM=0;
    for(int i=0;i<10;++i){
        TOTAL_SUM +=NEWVEC[i];
    }
    // for(int i=0;i<10;++i){
    //     cout<<NEWVEC[i]<<" ";
    // }
    // cout<<'\n'<<TOTAL_SUM;
    int POS, VALUE;
    int min = 32767;
    for(int i=0; i<10;++i){
        if(NEWVEC[i]<min){
          POS=i; 
          VALUE=NEWVEC[i];
          min = NEWVEC[i];
        }
    }

     ofstream out("output.txt");
    if (out.is_open())
    {
        for(int i=0;i<10;++i){
            out<<NEWVEC[i]<<" ";
        }
        out <<'\n'<<TOTAL_SUM;
        out<<"\n"<<POS<<" "<<VALUE;
    }
    out.close();
    // 
    // sleep(10);cout<<"\n"<<POS<<" "<<VALUE;
}
    