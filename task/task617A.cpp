#include <iostream>

using namespace std;

int main(){
    int x;
    cin >> x;
    int n=0;
    while(x){
        if(x > 4){
            x-=5;
            ++n;
        }
        else if(x > 3){
            x-=4;
            ++n;
        }
        else if(x > 2){
            x-=3;
            ++n;
        }
        else if(x > 1){
            x-=2;
            ++n;
        }
        else if(x > 0){
            x-=1;
            ++n;
        }
    }
    cout<< n;
    return 0;
}