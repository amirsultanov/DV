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

int sizes[4]={1000,10000, 50000, 100000};

int get_random_number(int min, int max)
{
  // Установить генератор случайных чисел
  srand(time(NULL));

  // Получить случайное число - формула
  int num = min + rand() % (max - min + 1);

  return num;
}

void marktime(void(*func)(int*,int),string file_name,int* arr, int size){
    auto begin =chrono::steady_clock::now();
    func(arr, size);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
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
void merge_sort_iterative(int* arr, int size){
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
    int k[15];
    generate_by_descending(k,15);
    sort_sheyk(k,15);
    generate_by_descending(k,15);
    merge_sort_iterative(k, 15);

    
    for(auto n: sizes){
        int arr[n];
        generate_by_ascending(arr, n);
        marktime(sort_sheyk, "sheyk_acsending.csv", arr, n);
        cout<<"sheyk_acsending.csv " <<n<<"\n";

        generate_by_descending(arr, n);
        marktime(sort_sheyk, "sheyk_decsending.csv", arr, n);
        cout<<"sheyk_decsending.csv " <<n<<"\n";

        generate_by_random(arr, n);
        marktime(sort_sheyk, "sheyk_random.csv", arr, n);
        cout<<"sheyk_random.csv " <<n<<"\n";

        generate_by_ascending(arr, n); 
        marktime(merge_sort_iterative, "merge_acsending.csv", arr, n);
        cout<<"merge_acsending.csv " <<n<<"\n";

        generate_by_descending(arr, n);
        marktime(merge_sort_iterative, "merge_decsending.csv", arr, n);
        cout<<"merge_decsending.csv " <<n<<"\n";

        generate_by_random(arr, n);
        marktime(merge_sort_iterative, "merge_random.csv", arr, n);
        cout<<"merge_random.csv " <<n<<"\n";
    }
}