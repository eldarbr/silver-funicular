#include <iostream>
#include <windows.h>
#include <chrono>

using namespace std;

//void swap(int* arr, int i, int j) {
//	int temp;
//	temp = arr[i];
//	arr[i] = arr[j];
//	arr[j] = temp;
//}


char red[] = { 0x1b,'[','0',';','3','1','m',0 };
char normal[] = { 0x1b,'[','0',';','3','9','m',0 };

void generateIncreasing(int* arr, int n) {
	int step = rand();
	arr[0] = step;
	for (int i = 1; i < n; i++) arr[i] = arr[i - 1] + step;
}

void generateDecreasing(int* arr, int n) {
	int step = rand();
	arr[0] = step;
	for (int i = 1; i < n; i++) arr[i] = arr[i - 1] - step;
}

void generateRandom(int* arr, int n){
	for (int i = 0; i < n; i++) arr[i] = rand();
}

void printArrayWithColor(int* arr, int n, int k, int j) {
	for (int i = 0; i < n; i++) {
		if ((i == k || i == j) && k != j) {
			cout << red << arr[i] << "\t";
		}
		else {
			cout << normal << arr[i] << "\t";
		}
	}
	cout << endl;
}

void chooseSort(int* arr, int n) {
	int i, j, smallest, temp;
	for (i = 0; i < n-1; i++) {
		smallest = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[smallest])
				smallest = j;
		temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
		printArrayWithColor(arr, n, smallest, i);
	}
}

void ShellSort(int* arr, int n) {
	int i, j, step, temp;
	for (step = n / 2; step > 0; step /= 2) 
		for (i = step; i < n; i++) {
			temp = arr[i];
			for (j = i; j >= step; j -= step) {
				if (temp < arr[j - step]) arr[j] = arr[j - step];
				else break;
			}
			arr[j] = temp;
			printArrayWithColor(arr, n,i, j);
		}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "Введите количество элементов массива: ";
	cin >> n;
	int* arr = new int[n];
	int choose;
	cout << "Задать массив от руки?\n1.Да\n2.Нет\nВаш выбор: ";
	cin >> choose;
	cout << endl;
	for (int i = 0; i < n; i++) cin >> arr[i];
	system("cls");
	for (int i = 0; i < n; i++) cout << arr[i] << "\t";
	cout << endl;
	//chooseSort(arr, n);
	ShellSort(arr, n);
	for (int i = 0; i < n; i++) cout << normal << arr[i] << "\t";
}