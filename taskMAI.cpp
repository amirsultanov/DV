#include <iostream>
#include<chrono> 
#include <fstream>

using namespace std;

ofstream out("results.txt");      

void marktime(int(*func)(int), int a, string func_name){
    auto begin =chrono::steady_clock::now();
    func(a);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
    if (out.is_open())
    {
        out << "Время работы функции " << func_name << ": "<< elapsed_ms.count() << " (мкС)" << endl;
    }

}

int factorial_line(int a){
    int result=1;
    for(int i=1; i<=a; ++i){
        result=result*i;
    }
    return result;
}

int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(){
    setlocale(LC_ALL, ".UTF8");
    marktime(factorial,1000,"factorial");
    marktime(factorial_line,1000,"factorial_line");
    out.close(); 
}