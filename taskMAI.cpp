#include <iostream>
#include<chrono> 

using namespace std;

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
int n;
cin >> n;
cout << factorial(n);
auto begin =chrono::steady_clock::now(); 
for(int i=0; i<10000; ++i){
    int a=0;
}
auto end = chrono::steady_clock::now();

auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);

cout << "Время работы алгоритма по формированию последовательности: " << elapsed_ms.count() << " (мкС)" << endl;
}