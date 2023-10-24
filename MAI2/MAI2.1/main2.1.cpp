#include <iostream>
#include <vector>
#include <iostream>
#include <climits>
#include <cstdlib>
#include <unistd.h>
#include <fstream>

using namespace std;

const int MAX_INT=2147483647;

vector<vector<int>> read_matrix(string path){
    ifstream in(path);
    vector<vector<int>> matrix;
    int N;

    if (in.is_open()){
        in>>N;
        matrix.resize(N,vector<int>(N));
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                in >> matrix[i][j];
            }
        }
    }
    in.close();
    return matrix;
}

void write_matrix(string path, vector<vector<int>>matrix, int res, int min){
    ofstream out(path);
    int M= matrix.size() ;
    if (out.is_open())
    {
        for(int i=0; i<M; ++i){
            for(int j=0; j<M;++j){
                out<<matrix[i] [j]<<" ";
             }
        out<<"\n";
        }  
        out<<"\n"<<res;
        out<<"\n"<<min;
    }
    out.close();
}

int multiply_negatives(vector<vector<int>>matrix){
    int N=matrix.size();
    int res=1;
    for(int i{0}; i<N;++i){
        for(int j{0}; j<N; ++j){
            if(j>i && matrix[i][j]<0){
                res=res*matrix[i][j];
            }
        }
    }
    return res;
}
int find_min(vector<vector<int>>matrix){
    int N=matrix.size();
    int min=MAX_INT;
    for(int i=0; i<N;++i){
        for(int j=0; j<N;++j){
            if(matrix[i][j]<min){
                min=matrix[i][j];
            }
        }
    }
    return min;
}






int main(){
    vector<vector<int>> A=read_matrix("inputA.txt");
    int N=A.size();
    int RES1=multiply_negatives(A);
    int min1=find_min(A);
    write_matrix("outputA.txt",A,RES1,min1);
    
    vector<vector<int>> B=read_matrix("inputB.txt");
    int M=B.size();
    int RES2=multiply_negatives(B);
    int min2=find_min(B);
    write_matrix("outputB.txt",B, RES2,min2);
}