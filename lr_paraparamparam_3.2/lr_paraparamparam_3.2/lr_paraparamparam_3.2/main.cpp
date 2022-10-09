#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void InsSort();
int BLS();
int SLS();
int T();
int B();
int timeToWork();


void InsSort(int* arr, int length) {
	int count = 0;
	int temp;
	for (int i = 1; i < length; i++)
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
			count++;
			temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
		}
}

int BLS(int* arr, int length, int key) {
	for (int i = 0; i < length; i++)
		if (arr[i] == key)
			return i;
	return -1;					// NOT FOUND
}

int SLS(int* arr, int length, int key) {
	int last = arr[length-1];	// last element of the arr
	arr[length - 1] = key;		// last element become key
	int i = 0;
	while (arr[i] != key)
		i++;
	arr[length - 1] = last;		// put the last element back
	if (i < length-1 || arr[length - 1] == key)
		return i;
	return -1;					// NOT FOUND

}

int T(int* arr, int length, int key) {
	for (int i = 0; i < length; i++)
		if (arr[i] == key)
			return i;
	return -1;					// NOT FOUND
}

int B(int* arr, int length, int key) {
	int p = 0;
	int r = length-1;
	int q = 0;
	while (true) {
		int q = (p + r) / 2;
		if (key < arr[q]) r = q - 1;
		else if (key > arr[q]) p = q + 1;
		else return q;
		if (p > r) return -1;	// NOT FOUND
	}
}

int main() {
	srand(0);
	setlocale(LC_ALL, "rus");

	int length;
	cout << "Введите длину массива: ";
	cin >> length;
	cout << endl;

	int* arr = new int[length];
	for (int i = 0; i < length; i++) arr[i] = rand();

	int key;
	cout << "Введите ключ поиска: ";
	cin >> key;
	int pick;
	cout << endl << "Хотите вставить ключ в массив?\n1.Да\n2.Нет\nВаш выбор: ";
	cin >> pick;
	if (pick == 1) {
		int indexForKey;
		cout << endl << "Введите индекс, в который вставить ключ поиска: ";
		cin >> indexForKey;
		cout << endl;
		arr[indexForKey] = key;
	}

	int indexToFound;

	auto startTime = chrono::steady_clock::now();
	indexToFound = BLS(arr, length, key);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "\nЭлемент не найден в поиске BLS.\n" << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "Результат работы алгоритма поиска BLS: " << indexToFound << endl << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}

	startTime = chrono::steady_clock::now();
	indexToFound = SLS(arr, length, key);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "Элемент не найден в поиске SLS.\n" << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "Результат работы алгоритма поиска SLS: " << indexToFound << endl << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}

	startTime = chrono::steady_clock::now();
	InsSort(arr, length);		// insert sort for T and B
	auto endTime = chrono::steady_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
	cout << "Время сортировки: " << time.count() << " мкс.\n";
	//for (int i = 0; i < length; i++) cout << arr[i] << endl;

	startTime = chrono::steady_clock::now();
	indexToFound = T(arr, length, key);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "Элемент не найден в поиске T.\n" << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "Результат работы алгоритма поиска T: " << indexToFound << endl << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}

	startTime = chrono::steady_clock::now();
	indexToFound = B(arr, length, key);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "Элемент не найден в поиске B.\n" << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "Результат работы алгоритма поиска B: " << indexToFound << endl << "\tАлгоритм выполнился за " << time.count() << " мкс.\n";
	}
}