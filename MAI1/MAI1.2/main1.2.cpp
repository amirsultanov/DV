/*******************************************************************************
*                       Лабораторная работа №2                                *
*-----------------------------------------------------------------------------*
* Project Type  : Win64 Console Application                                   *
* Project Name  : Символьные данные                                           *
* File Name     : main1.2.cpp                                                 *
* Programmer(s) : Султанов А.А.                                               *
* Modifyed By   :                                                             *
* Created       : 10/10/2023                                                  *
* Last Revision : 10/10/2023                                                  *
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/*******************************************************************************/
/*                   О С Н О В Н А Я     П Р О Г Р А М М А                     */
/*******************************************************************************/
//Функция для определения длины максимального слова
int long_word(string str){
    int word=0;//Количество символов в текущем слове
    int max=0;//Максимальное количество символов в словах
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
//Сжатие повторяющихся пробелов до единичного 
string delete_spaces(string str){
    string message;//переменная с результатом
    bool flag=false;
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
    //Чтение данных из файла
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

/*******************    К О Н Е Ц      П Р О Г Р А М М Ы    ********************/