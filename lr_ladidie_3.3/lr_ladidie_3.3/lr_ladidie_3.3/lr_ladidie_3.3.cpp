#include <iostream>
#include <chrono>

using namespace std;

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

void chooseSort(int* arr, int n, int numOfSwaps, int numOfComparisons) {
	int i, j, smallest, temp;
	int choose;
	numOfSwaps = 0;
	numOfComparisons = 0;
	cout << "Выводить сортировку построчно?(по умолчанию Нет)\n1.Да\n2.Нет\nВаш выбор: ";
	cin >> choose;
	switch (choose) {
	case 1:
		for (i = 0; i < n - 1; i++) {
			smallest = i;
			for (j = i + 1; j < n; j++)
				if (arr[j] < arr[smallest]) {
					smallest = j;
					numOfComparisons++;
				}
				else numOfComparisons++;
			if (i != smallest) {
				temp = arr[i];
				arr[i] = arr[smallest];
				arr[smallest] = temp;
				numOfSwaps++;
			}
			printArrayWithColor(arr, n, smallest, i);
		}
		break;
	default:
		for (i = 0; i < n - 1; i++) {
			smallest = i;
			for (j = i + 1; j < n; j++)
				if (arr[j] < arr[smallest]) {
					smallest = j;
					numOfComparisons++;
				}
				else numOfComparisons++;
			if (i != smallest) {
				temp = arr[i];
				arr[i] = arr[smallest];
				arr[smallest] = temp;
				numOfSwaps++;
			}
		}
		break;
	}
	cout << normal <<  "\nКоличество сравнений: " << numOfComparisons
		<< "\nКоличество пересылок: " << numOfSwaps << "\n";
}

void ShellSort(int* arr, int n, int numOfSwaps, int numOfComparisons) {
	int i, j, step, temp;
	int choose;
	numOfComparisons = 0;
	numOfSwaps = 0;
	cout << "Выводить сортировку построчно?(по умолчанию Нет)\n1.Да\n2.Нет\nВаш выбор: ";
	cin >> choose;
	switch (choose) {
	case 1:
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++) {
				temp = arr[i];
				for (j = i; j >= step; j -= step) {
					if (temp < arr[j - step]) {
						arr[j] = arr[j - step];
						numOfSwaps++;
						numOfComparisons++;
					}
					else {
						numOfComparisons++;
						break;
					}
				}
				arr[j] = temp;
				if(i!=j)
					numOfSwaps++;
				printArrayWithColor(arr, n, i, j);
			}
		break;
	default:
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++) {
				temp = arr[i];
				for (j = i; j >= step; j -= step) {
					if (temp < arr[j - step]) {
						arr[j] = arr[j - step];
						numOfComparisons++;
					}
					else {
						numOfComparisons++;
						break;
					}
				}
				arr[j] = temp;
				numOfSwaps++;
			}
		break;
	}
	cout << normal << "\nКоличество сравнений: " << numOfComparisons
		<< "\nКоличество пересылок: " << numOfSwaps << "\n";
}

void timeForSort(void (*function)(int* arr, int n, int numOfSwaps, int numOfComparisons), int* arr, int n, int numOfSwaps, int numOfComparisons) {
	auto startTime = chrono::steady_clock::now();
	function(arr, n, numOfSwaps, numOfComparisons);
	auto endTime = chrono::steady_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	cout << "\nВремя на сортировку (в мск): " << time.count() << "\n\n";
	cout << "Вывести отсортированный массив?(по умолчанию Нет)\n1.Да\n2.Нет\nВаш выбор: ";
	int choose4;
	cin >> choose4;
	switch (choose4) {
		case 1:
			cout << normal << "\nОтсортированный массив:\n";
			for (int i = 0; i < n; i++) cout << arr[i] << "\t";
			break;
		default:
			break;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int numOfSwaps = 0, numOfComparisons = 0;
	int n;
	cout << "Введите количество элементов массива: ";
	cin >> n;
	int* arr1 = new int[n];
	int* arr2 = new int[n];
	int choose;
	cout << "Задать массив от руки?(по умолчанию Нет)\n1.Да\n2.Нет\nВаш выбор: ";
	cin >> choose;
	cout << endl;

	switch (choose) {
		case 1:
			for (int i = 0; i < n; i++) cin >> arr1[i];
			for (int i = 0; i < n; i++) arr2[i] = arr1[i];
			break;
		default:
			int choose2;
			cout << "Какой массив вы хотите сгенерировать?\n1.Возрастающий\n2.Убывающий\n3.Рандомный\nВаш выбор: ";
			cin >> choose2;
			switch (choose2) {
			case 1:
				generateIncreasing(arr1, n);
				for (int i = 0; i < n; i++) arr2[i] = arr1[i];
				break;
			case 2:
				generateDecreasing(arr1, n);
				for (int i = 0; i < n; i++) arr2[i] = arr1[i];
				break;
			case 3:
				generateRandom(arr1, n);
				for (int i = 0; i < n; i++) arr2[i] = arr1[i];
				break;
			default:
				exit(-1);
			}
			break;
	}
	system("cls");

	int choose3;
	cout << "Вывести исходный массив?(по умолчанию Нет)\n1.Да\n2.Нет\nВаш выбор: ";
	cin >> choose3;
	switch (choose3) {
	case 1:
		cout << "Введенный массив:\n";
		for (int i = 0; i < n; i++) cout << arr1[i] << "\t";
		break;
	default:
		break;
	}

	cout << "\n\n\t\tСортировка выбором:\n\n";

	void (*fun)(int* arr, int n, int numOfSwaps, int numOfComparisons);
	fun = chooseSort;
	timeForSort(fun, arr1, n, numOfSwaps, numOfComparisons);

	cout << "\n\n\t\tСортировка Шелла:\n\n";
	fun = ShellSort;
	timeForSort(fun, arr2, n, numOfSwaps, numOfComparisons);

}