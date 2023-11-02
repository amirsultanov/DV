#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int long_word(string str){
    int word=0;
    int max=0;
    for(int i=0; i<str.size();++i){
        if(str[i] !=' '){
            word=word+1;
            if(word>max){
                max=word;
            }
        }
        if(str[i] == ' ' || i==str.size()-1){
            if(word>max){
                max=word;
            }
            word=0;
        }
    }
    return max;
}

string func(string str){
    int max=long_word(str);
    int word;
    int temp;
    for(int i=0; i<str.size();++i ){
        if(str[i] !=' '){
            word=word+1;
            if(word == max){
                temp=str[i];
                str[i]=str[i-max+1];
                str[i-max+1]=temp;
            }
        }
        if(str[i] == ' ' || i==str.size()-1){
            word=0;
        }
    }
    return str;
}

string reverse(string str){
    int temp;
    int n=str.size();
    for(int i=0; i<n/2;++i){
        temp=str[i];
        str[i] = str[n-i-1];
        str[n-i-1]=temp;
    }
    return str;
}

string delete_spaces(string str){
    string message;
    int flag=false;
    for(int i=0; i<str.size();++i){
        if(str [i] != ' ' ){
            message += str[i];
            flag = false;
        }
        else if(str[i] == ' ' && flag==false){
            message += ' ';
            flag = true;
        }

    }
    return message;
}
int main(){
    //Чтение данных их файла
    ifstream in("input.txt");
    int n;
    string str;
    if(in.is_open()){
        in >> n;
        while(in && in.get() != '\n');
        getline(in, str);
    }
    in.close();
    cout << n << " " << str;
    //Запись данных в файл
    ofstream out("output.txt");
    if(out.is_open()){
        out <<"\n"<<long_word(str);
        out <<"\n"<< reverse(str);
        out <<"\n"<< func(str);
    }
    return 0;
}