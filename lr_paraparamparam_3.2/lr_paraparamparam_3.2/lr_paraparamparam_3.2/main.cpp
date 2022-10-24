#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void InsSort();
int BLS();
int SLS();
int T();
int B();



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

int BLS(int* arr, int length, int key, int* comparisons) {
	*comparisons = 0;
	for (int i = 0; i < length; i++) {
		(*comparisons)++;
		if (arr[i] == key)
			return i;
	}
	return -1;					// NOT FOUND
}

int SLS(int* arr, int length, int key, int* comparisons) {
	*comparisons = 0;
	int last = arr[length-1];	
	arr[length - 1] = key;		
	int i = 0;
	while (arr[i] != key) {
		(*comparisons)++;
		i++;
	}
	(*comparisons)++; // ������ ��������� ����� ������ �� while
	arr[length - 1] = last;	
	(*comparisons)++; // ������ ��������� ����������� ��������� �������
	if (i < length - 1) {
		return i;
	}
	(*comparisons)++; // ������ ��������� ���������� �������� � ������
	if (arr[length - 1] == key) {
		return i;
	}
	return -1;					// NOT FOUND

}

int T(int* arr, int length, int key) {
	arr[length] = 2147483647;
	int i = 0;
	while (key > arr[i]) i++;
	if (arr[i] == key) return i;
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
	cout << "������� ����� �������: ";
	cin >> length;
	cout << endl;

	int* arr = new int[length + 1];
	for (int i = 0; i < length; i++) arr[i] = rand();

	int key;
	cout << "������� ���� ������: ";
	cin >> key;
	int pick;
	int indexForKey;
	int tmp;
	cout << endl << "������ �������� ���� � ������?\n1.��\n2.���\n��� �����: ";
	cin >> pick;
	if (pick == 1) {
		cout << endl << "������� ������, � ������� �������� ���� ������: ";
		cin >> indexForKey;
		cout << endl;
		tmp = arr[indexForKey];
		arr[indexForKey] = key;
	}

	int indexToFound;
	int comparisons;

	auto startTime = chrono::steady_clock::now();
	indexToFound = BLS(arr, length, key, &comparisons);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "\n������� �� ������ � ������ BLS.\n" << "\t�������� ���������� �� " << time.count() << " ���.\n";
		cout << "���� ������� " << comparisons << " ���������\n\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "��������� ������ ��������� ������ BLS: " << indexToFound << endl << "\t�������� ���������� �� " << time.count() << " ���.\n";
		cout << "���� ������� " << comparisons << " ���������\n\n";
	}

	startTime = chrono::steady_clock::now();
	indexToFound = SLS(arr, length, key, &comparisons);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "������� �� ������ � ������ SLS.\n" << "\t�������� ���������� �� " << time.count() << " ���.\n";
		cout << "���� ������� " << comparisons << " ���������\n\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "��������� ������ ��������� ������ SLS: " << indexToFound << endl << "\t�������� ���������� �� " << time.count() << " ���.\n";
		cout << "���� ������� " << comparisons << " ���������\n\n";
	}

	startTime = chrono::steady_clock::now();
	InsSort(arr, length);		
	auto endTime = chrono::steady_clock::now();	
	auto time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
	cout << "\n����� ����������: " << time.count() << " ���.\n\n";

	startTime = chrono::steady_clock::now();
	indexToFound = T(arr, length, key);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "\n������� �� ������ � ������ T.\n" << "\t�������� ���������� �� " << time.count() << " ���.\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "\n��������� ������ ��������� ������ T: " << indexToFound << endl << "\t�������� ���������� �� " << time.count() << " ���.\n";
	}

	startTime = chrono::steady_clock::now();
	indexToFound = B(arr, length, key);
	if (indexToFound == -1) {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "\n������� �� ������ � ������ B.\n" << "\t�������� ���������� �� " << time.count() << " ���.\n";
	}
	else {
		auto endTime = chrono::steady_clock::now();
		time = chrono::duration_cast<chrono::microseconds>(endTime-startTime);
		cout << "\n��������� ������ ��������� ������ B: " << indexToFound << endl << "\t�������� ���������� �� " << time.count() << " ���.\n";
	}
}