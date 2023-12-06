#include <iostream>
#include <chrono> 
#include <fstream>
#include <random>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

//Создание генератора случайных чисел
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double> dist(0.0, 1.0);

ofstream out;//поток для вывода в файл

const int MAX_INT=2147483647;
int BLS_count = 0;
int SLS_count = 0;

int get_random_number(int min, int max)
{
  // Установить генератор случайных чисел
  srand(time(NULL));

  // Получить случайное число - формула
  int num = min + rand() % (max - min + 1);

  return num;
}
int better_linear_search(int* arr, int size, int key){
    BLS_count =0;
    for(int i=0; i<size; i++){
        if(arr[i] == key){
            BLS_count=BLS_count+2;
            return i;
        }
    }
    return -1;
}
int sentinel_linear_search(int* arr, int size, int key){
    SLS_count = 0;
    int i=0;
    int last = arr[size-1];
    arr[size-1] = key;

    while(arr[i] != key ){
        SLS_count= SLS_count+1;
        ++i;
    }

    arr[size-1] = last;

    if(arr[size-1]==key || i<size-1){
        SLS_count= SLS_count+1;
        return i;
    }
    return -1;
}
int ordered_array_search(int* arr, int size, int key){
    int i=0;
    int last = arr[size-1];
    arr[size-1] = MAX_INT;

    while(key > arr[i]){
        ++i;
    }

    arr[size-1] = MAX_INT;

    if(arr[size-1]==key || (i<size-1 && arr[i] == key)){
        return i;
    }
    return -1;
}

int binary_search(int* arr,int size, int key){
    int l = -1 ;                     // l, r — левая и правая границы
    int r = size;    
    while (l < r - 1){              // Запускаем цикл
        int m = (l + r) / 2 ;           // m — середина области поиска
        if(arr[m]== key){
            return m;
        }
        else if(arr[m] < key){
            l = m;
        }
        else{
            r = m;                // Сужение границ
        }
    }
    return -1;
}


//Функция для оценки характеристик алгоритмов
void marktime(int(*func)(int*,int,int),string file_name,int* arr, int size, int key){
    auto begin =chrono::steady_clock::now();
    func(arr, size, key);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    out.open(file_name, ios::app /*открывает файл до записи*/);
    if (out.is_open())
    {
        out << size<< ";" << elapsed_ms.count()<< ";\n";
    }
    out.close();

}
void generate_by_ascending(int* arr, int size){
    arr[0]=get_random_number(0,10);
    for(int i=1; i<size; ++i){
        arr[i]=arr[i-1]+get_random_number(0,10);
    }
}
void generate_by_random(int* arr, int size){
    for(int i=0; i<size; ++i){
        arr[i]=i;
    }
    shuffle(arr, arr+size, gen);//Перемешивание элементов массива
}
void save_counters(int size, string index){
    out.open("file_couters.csv", ios::app);
    if (out.is_open())
    {
        out << size<< ";"<< index << ";"<< BLS_count<< ";"<< SLS_count<< ";\n";
    }
    out.close();
}

int main(){
    int start, middle, end;
    for(int i=10000; i<=200000;  i=i+19000){
        int arr[i];
        
        generate_by_random(arr, i);
        start = arr[rand()% 1000];
        middle = arr[i/2-500+rand()%1001];
        end = arr[i-rand()%1000-1];
        marktime(better_linear_search,"bls_start.csv", arr, i, start);
        marktime(sentinel_linear_search,"sls_start.csv", arr, i, start);
        save_counters(i,"start_counter");
        marktime(better_linear_search,"bls_middle.csv", arr, i, middle);
        marktime(sentinel_linear_search,"sls_middle.csv", arr, i, middle);
        save_counters(i,"middle_counter");
        marktime(better_linear_search,"bls_end.csv", arr, i, end);
        marktime(sentinel_linear_search,"sls_end.csv", arr, i, end);
        save_counters(i,"end_counter");
        
        generate_by_ascending(arr, i);
        start = arr[rand()% 1000];
        middle = arr[i/2-500+rand()%1001];
        end = arr[i-rand()%1000-1];
        marktime(binary_search,"bs_start.csv", arr, i, start);
        marktime(binary_search,"bs_middle.csv", arr, i, middle);
        marktime(binary_search,"bs_end.csv", arr, i, end);
        marktime(ordered_array_search,"oas_start.csv", arr, i, start);
        marktime(ordered_array_search,"oas_middle.csv", arr, i, middle);
        marktime(ordered_array_search,"oas_end.csv", arr, i, end);
    }
}