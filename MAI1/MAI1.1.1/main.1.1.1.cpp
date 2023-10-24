#include <iostream>
#include <string>

using namespace std;

void wordm(string str){
    string word;
    bool flag=false;
    for(int i=0; i<str.size(); ++i){
        if(str [i] != ' '){
            word += str[i];
            if (str[i] == 'e'){
                flag = true;
            }  
        }
        else if(str[i] == ' '){
            if(flag == true){
                cout << word<< " ";
            }
            flag = false;
            word = "";
        }
    }
}

int main(){
    string str;
    getline(cin,str);
    wordm(str);
}