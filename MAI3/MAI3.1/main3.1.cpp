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

//Функция для оценки характеристик алгоритмов
void marktime_int(void(*func)(int),string file_name, int size){
    auto begin =chrono::steady_clock::now();
    func(size);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
    out.open(file_name, ios::app /*открывает файл до записи*/);
    if (out.is_open())
    {
        out << size<< ";" << elapsed_ms.count()<< ";\n";
    }
    out.close();

}
void marktime_double(void(*func)(int),string file_name, int size){
    auto begin =chrono::steady_clock::now();
    func(size);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
    out.open(file_name, ios::app);
    if (out.is_open())
    {
        out << size<< ";" << elapsed_ms.count()<< ";\n";
    }
    out.close();
}
void generate_by_ascending_int(int size){
    int a;
    for(int i=0; i<size; ++i){
        a=i;
    }
}
void generate_by_ascending_double(int size){
    double a;
    for(int i=0; i<size; ++i){
        a=i+dist(gen);
    }
}
void generate_by_descending_int(int size){
    int a;
    for(int i=0; i<size; ++i){
        a=i;
    }
}
void generate_by_descending_double(int size){
    double a;
    for(int i=0; i<size; ++i){
        a=i+dist(gen);
    }
}
// void generate_by_random_int(int size){
//     int a;
//     for(int i=0; i<size; ++i){
//         a=i;
//     }
// }
// void generate_by_random_double(int size){
//     double a;
//     for(int i=0; i<size; ++i){
//         a=i+dist(gen);
//     }
// }
void generate_by_sin_int(int size){
    int a;
    for(int i=0; i<size; ++i){
        double radian=(i*M_PI)/180;
        double y=sin(radian);
        int withoutdouble = int(y*1000);
        a=withoutdouble;
    }
}
void generate_by_sin_double( int size){
    double a;
    for(int i=0; i<size; ++i){
        double radian=(i*M_PI)/180;
        double y=sin(radian);
        a=y*1000;
    }
}
//Функция упорядоченная по возрастанию для целых чисел
void generate_by_ascending(int* arr, int size){
    for(int i=0; i<size; ++i){
        arr[i]=i;
    }
}
//Функция упорядоченная по возрастанию  для дробных чисел
void generate_by_ascending(double* arr, int size){
    for(int i=0; i<size; ++i){
        arr[i]=i+dist(gen);
    }
}
//Функция упорядоченная по убыванию  для целых чисел
void generate_by_descending(int* arr, int size){
    for(int i=0; i<size; ++i){
        arr[size-1-i]=i;
    }
}
//Функция упорядоченная по убыванию  для дробных чисел
void generate_by_descending(double* arr, int size){
    for(int i=0; i<size; ++i){
        arr[size-1-i]=i+dist(gen);
    }
}
//Функция случайной последовательности для целых чисел
void generate_by_random(int* arr, int size){
    for(int i=0; i<size; ++i){
        arr[i]=i;
    }
    shuffle(arr, arr+size, gen);//Перемешивание элементов массива
}
//Функция случайной последовательности для дробных чисел
void generate_by_random(double* arr, int size){
    for(int i=0; i<size; ++i){
        arr[i]=i+dist(gen);
    }
    shuffle(arr, arr+size, gen);//Перемешивание элементов массива
}
//Функция частично упорядоченная "синусоидальная"  для целых
void generate_by_sin(int* arr, int size){
    for(int i=0; i<size; ++i){
        double radian=(i*M_PI)/180;
        double y=sin(radian);
        int withoutdouble = int(y*1000);
        arr[i]=withoutdouble;
    }
}
//Функция частично упорядоченная "синусоидально"  для дробных чисел
void generate_by_sin(double* arr, int size){
    for(int i=0; i<size; ++i){
        double radian=(i*M_PI)/180;
        double y=sin(radian);
        arr[i]=y*1000;
    }
}

void save_to_file(int* arr, int size, string file_name){
    out.open(file_name);
    if(out.is_open()){
        for(int i=0; i<size; ++i){
            out<< i<< ";" << arr[i] << ";\n";
        }
    }
    out.close();
}

void save_to_file(double* arr, int size, string file_name){
    out.open(file_name);
    if(out.is_open()){
        for(int i=0; i<size; ++i){
            out<< i<< ";" << arr[i] << ";\n";
        }
    }
    out.close();
}

int main(){
    int r[1000];
    double d[1000];
    
    generate_by_ascending(r,1000);
    save_to_file(r, 1000, "int_by_ascending.csv");

    generate_by_ascending(d,1000);
    save_to_file(d, 1000, "double_by_ascending.csv");

    generate_by_descending(r,1000);
    save_to_file(r, 1000, "int_by_descending.csv");

    generate_by_descending(d,1000);
    save_to_file(d, 1000, "double_by_descending.csv");
    
    generate_by_random(r,1000);
    save_to_file(r, 1000, "int_by_random.csv");

    generate_by_random(d,1000);
    save_to_file(d, 1000, "double_by_random.csv");
    
    generate_by_sin(r,1000);
    save_to_file(r, 1000, "int_by_sin.csv");

    generate_by_sin(d,1000);
    save_to_file(d, 1000, "double_by_sin.csv");

    for(int i=500000; i<=5000000; i=i+500000){
        marktime_int(generate_by_ascending_int, "generate_by_ascending_int.csv", i);
        marktime_double(generate_by_ascending_double, "generate_by_ascending_double.csv", i);
        marktime_int(generate_by_descending_int, "generate_by_descending_int.csv", i);
        marktime_double(generate_by_descending_double, "generate_by_descending_double.csv", i);
        marktime_int(generate_by_sin_int, "generate_by_sin_int.csv", i);
        marktime_double(generate_by_sin_double, "generate_by_sin_double.csv", i);

    }
}