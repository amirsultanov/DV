#include <iostream>
#include<chrono> 

using namespace std;

int main(){
int n;
cin >> n;
auto begin =chrono::steady_clock::now(); 

auto end = chrono::steady_clock::now();

auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);

cout << "Время работы алгоритма по формированию последовательности: " << elapsed_ms.count() << " (мкС)" << endl;
}