#include <iostream>
#include <chrono> 
#include <fstream>
#include <random>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

random_device rd;
mt19937 gen(rd());

ofstream out;

int const IF_COUNT=0, SWAP_COUNT=1;
int shaker_count[2];
int merge_count[2];

void marktime(void(*func)(int*,int),string file_name,int* arr, int size){
    auto begin =chrono::steady_clock::now();
    func(arr, size);
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
    for(int i=0; i<size; ++i){
        arr[i]=i;
    }
}
void generate_by_descending(int* arr, int size){
    for(int i=0; i<size; ++i){
        arr[size-1-i]=i;
    }
}
void generate_by_random(int* arr, int size){
    for(int i=0; i<size; ++i){
        arr[i]=i;
    }
    shuffle(arr, arr+size, gen);//Перемешивание элементов массива
}

void save_to_file(int* arr, int size,string file_name){
    out.open(file_name,ios::app /*открывает файл до записи*/);
    if (out.is_open())
    {
        for(int i=0; i<size; ++i){
            out<< arr[i]<< " ";
        }
        out<<"\n";
    }
    out.close();
}
void bubbles_sort(int* arr, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size-1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j]; // создали дополнительную переменную
                arr[j] = arr[j + 1]; // меняем местами
                arr[j + 1] = temp; // значения элементов
            }
        }
        if(size==15){
            save_to_file(arr, size, "bubble_file.txt");
        }
    }
}
void sort_sheyk(int*arr, int size){
    int left=1;
    int right=size-1;
    int temp;
    shaker_count[SWAP_COUNT]=0;
    shaker_count[IF_COUNT]=0;
    while(right>=left){
        shaker_count[IF_COUNT] +=1;
        for(int i=right; i >=left; i--){
            shaker_count[IF_COUNT] +=2;
            if(arr[i-1] > arr[i]){
                shaker_count[SWAP_COUNT] +=1;
                temp=arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = temp;
            }
        }
        left++;
        for (int i = left; i <= right; i++){
            shaker_count[IF_COUNT] +=2;
            if(arr[i-1] > arr[i]){
                shaker_count[SWAP_COUNT] +=1;
                temp=arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = temp;
            }
        }
        right--;
        
        if(size==15){
            save_to_file(arr, size, "sheyk_file.txt");
        }
    }
    if(size == 15){
        save_to_file(shaker_count, 2, "shaker_count_file.txt");
    }
}
void merge(int* arr,int left, int mid, int right, int size){
    int it1 = 0;
    int it2 = 0;
    int result[right-left];
  
    while(left + it1 < mid && mid + it2 < right){
        merge_count[IF_COUNT] +=3;
        if (arr[left + it1] < arr[mid + it2]){
            merge_count[SWAP_COUNT] +=1;
            result[it1 + it2] = arr[left + it1];
            it1 += 1;
        }
        else{
            result[it1 + it2] = arr[mid + it2];
            it2 += 1;
        }
    }
    while (left + it1 < mid){
        merge_count[IF_COUNT] +=1;
        result[it1 + it2] = arr[left + it1];
        merge_count[SWAP_COUNT] +=1;
        it1 += 1;
    }
    while (mid + it2 < right){
        merge_count[IF_COUNT] +=1;
        result[it1 + it2] = arr[mid + it2];
        merge_count[SWAP_COUNT] +=1;
        it2 += 1;
    }
    for (int i = 0; i< it1 + it2; i++){
        merge_count[IF_COUNT] +=1;
        arr[left + i] = result[i];
        merge_count[SWAP_COUNT] +=1;
    }
    if(size==15){
        save_to_file(arr, 15, "merge_file.txt");
    }
}
void mergeSortIterative(int* arr, int size){
    merge_count[SWAP_COUNT]=0;
    merge_count[IF_COUNT]=0;
  for(int i = 1; i< size; i *= 2){
    merge_count[IF_COUNT] +=1;
        for (int j = 0; j<size - i; j += 2 * i){
            merge_count[IF_COUNT] +=1;
            merge(arr, j, j + i, min(j + 2 * i, size),size);
        } 
  } 
  if(size== 15){
    save_to_file(merge_count, 2, "merge_count_file.txt");
  } 
}
int main(){
    int arr[15];
    generate_by_ascending(arr,15);
    save_to_file(arr, 15, "arrays.txt");

    generate_by_descending(arr,15);
    save_to_file(arr, 15, "arrays.txt");

    mergeSortIterative(arr, 15);

    // generate_by_random(arr,15);
    // save_to_file(arr, 15, "arrays.txt");

    // bubbles_sort(arr,15);

    sort_sheyk(arr, 15);

}