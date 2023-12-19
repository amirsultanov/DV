#include <iostream>

using namespace std;

const int SIZE = 10;

int main()
{
    setlocale(LC_ALL, ".UTF8");
	int min;
	int minindex;
	int indbegin = 0;
	int temp;
	
	
	int a[SIZE][SIZE] = {
	{ 0,10, 0, 0,20, 0, 0,30, 0, 0},
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0,12, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
	{ 0, 0, 0, 1, 0, 0, 9,10, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 7, 0, 0,40},
	{ 0, 0, 0, 0, 0, 0, 0, 2,12,23},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};
	int d[SIZE];
	int v[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		d[i] = LONG_MAX;
		v[i] = 1;
	}
	d[0] = indbegin;

	// Шаг алгоритма
	do {
		minindex = LONG_MAX;
		min = LONG_MAX;
		for (int i = 0; i < SIZE; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{ 
				min = d[i];
				minindex = i;
			}
		}
		if (minindex != LONG_MAX)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (a[minindex][i] > 0)
				{
					temp = min + a[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} 
	while (minindex < LONG_MAX);

	cout << "Кратчайшие расстояния до вершин" << endl;
	for (int i = 0; i < SIZE; i++)
		cout <<  d[i]  << ' ';
	cout << endl;

	
	int pos[SIZE]; // массив посещенных вершин
	int end = SIZE - 1;
	pos[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = d[end]; // вес конечной вершины

	while (end != indbegin) // пока не дошли до начальной вершины
	{
		for (int i = 0; i < SIZE; i++) // просматриваем все вершины
			if (a[i][end] != 0)   
			{
				int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
				if (temp == d[i]) // если вес совпал с рассчитанным
				{                 // значит из этой вершины и был переход
					weight = temp; // сохраняем новый вес
					end = i;       // сохраняем предыдущую вершину
					pos[k] = i + 1; // и записываем ее в массив
					k++;
				}
			}
	}
	
	cout << "Вывод кратчайшего пути" << endl;
	for (int i = k - 1; i >= 0; i--)
		cout << pos[i] - 1 << '\t';
	return 0;
}