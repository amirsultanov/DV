#include <iostream>

using namespace std;

int main(){
    int a[5][5];
    int c,b;
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            cin>> a[i][j];
        }
    }
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            if(a[i][j] == 1){
                if(i<2){
                    c=2-i;
                }
                else{
                    c=i-2;
                }
                if(j<2){
                    b=2-j;
                }
                else{
                    b=j-2;
                }
               cout <<b+c; 
            }
        }
    }
    
    return 0;
}
