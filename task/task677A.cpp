#include <iostream>

using namespace std;

int main(){
    int ht = 0, sl = 0;;
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); ++i){
        if(s[i] >= 'a'){
            ht=ht+1;
            }
        else{
            sl=sl+1;
            }
    }
    if(sl > ht){
        for(int i = 0; i < s.size(); ++i)
            if(s[i] >= 'a')
                s[i]-=32;
    }
    else{
        for(int i = 0; i < s.size(); ++i)
            if(s[i] >= 'A' && s[i] <= 'Z')
                s[i]+=32;
    }
    cout << s;
}