#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;


void generate_ascending(float* arr, unsigned int length);
void generate_descending(float* arr, unsigned int length);
void generate_random(float* arr, unsigned int length);
void generate_sawtooth(float* arr, unsigned int length, float min, float max, float interval);
void generate_sinuous(float* arr, unsigned int length, float min, float max);
void generate_stepped(float* arr, unsigned int length, float min, float max, float interval);

int random(int min, int max);
float random_fl();
int random_sign();



int random(int min, int max) {
	return min + (max - min) * random_fl();
}

float random_fl() {
	return rand() / float(RAND_MAX);
}

int random_sign() {
	int qqq = rand();
	if (qqq > RAND_MAX / 2)
		return 1;
	else
		return -1;
}

void generate_ascending(float* arr, unsigned int length) {
	for (int i = 0; i < length; i++) {
		*(arr + i) = random(0, 1000 * random(0, 3) * random_fl());
		if (i > 0) {
			*(arr + i) += *(arr + i - 1);
		}
	}
}

void generate_descending(float* arr, unsigned int length){
	for (int i = 0; i < length; i++) {
		*(arr + i) = random(-1000 * random(0,3) * random_fl(), 0);
		if (i > 0) {
			*(arr + i) += *(arr + i - 1);
		}
	}
}

void generate_random(float* arr, unsigned int length) {
	for (int i = 0; i < length; i++) {
		*(arr + i) = random(-10000 * random(0, 3) * random_fl(), 10000 * random(0, 3) * random_fl());
	}
}

void generate_sawtooth(float* arr, unsigned int length, float min, float max, float interval) {
	float step = (max - min) / interval;
	int num = 1;
	*(arr) = min;
	for (int i = 1; i < length; i++) {
		*(arr + i) = *(arr + i - 1) + step;
		num++;
		if (num == interval) {
			i++;
			*(arr + i) = min;
			num = 1;
		}		
	}
}

void generate_sinuous(float* arr, unsigned int length, float min, float max) {
	float scar = (min + max) / 2;
	float dobby = max - scar;
	for (int i = 0; i < length; i++) {
		*(arr + i) = sin(i) * dobby + scar;
	}
}

void generate_stepped(float* arr, unsigned int length, float min, float max, float interval) {
	float step = (max - min) / (length/interval-1);
	*(arr) = min;
	int k = 0;
	int num = 1;
	for (int i = 1; i < length; i++) {
		float q = (rand() / 10000) * random_sign();
		*(arr + i) = *(arr + k) + q;
		num++;
		if (num == interval) {
			num = 0;
			k = i + 1;
			*(arr + k) = *(arr + i) + step;
		}
	}
}
	

void switch_num(int num, int length, float* arr) {
	int min;
	int max;
	int interval;
	unsigned int start_time;
	unsigned int end_time;
	unsigned int search_time;

	switch (num) {
		case 1:
			start_time = clock();
			generate_ascending(arr, length);
			search_time = clock() - start_time;
			cout << "ВРЕМЯ РАБОТЫ: " << search_time << endl;
			break;
		case 2:
			start_time = clock();
			generate_descending(arr, length);
			search_time = clock() - start_time;
			cout << "ВРЕМЯ РАБОТЫ: " << search_time << endl;
			break;
		case 3:
			start_time = clock();
			generate_random(arr, length);
			search_time = clock() - start_time;
			cout << "ВРЕМЯ РАБОТЫ: " << search_time << endl;
			break;
		case 4:
			cout << "ВВВЕДИТЕ НИЖНЮЮ ГРАНИЦУ: ";
			cin >> min;
			cout << "ВВЕДИТЕ ВЕРХНЮЮ ГРАНИЦУ: ";
			cin >> max;
			cout << "ВВЕДИТЕ ИНТЕРВАЛ: ";
			cin >> interval;
			start_time = clock();
			generate_sawtooth(arr, length, min, max, interval);
			search_time = clock() - start_time;
			cout << "ВРЕМЯ РАБОТЫ: " << search_time << endl;
			break;
		case 5:
			cout << "ВВВЕДИТЕ НИЖНЮЮ ГРАНИЦУ: ";
			cin >> min;
			cout << "ВВЕДИТЕ ВЕРХНЮЮ ГРАНИЦУ: ";
			cin >> max;
			start_time = clock();
			generate_sinuous(arr, length, min, max);
			search_time = clock() - start_time;
			cout << "ВРЕМЯ РАБОТЫ: " << search_time << endl;
			break;
		case 6:
			cout << "ВВВЕДИТЕ НИЖНЮЮ ГРАНИЦУ: ";
			cin >> min;
			cout << "ВВЕДИТЕ ВЕРХНЮЮ ГРАНИЦУ: ";
			cin >> max;
			cout << "ВВЕДИТЕ ИНТЕРВАЛ: ";
			cin >> interval;
			start_time = clock();
			generate_stepped(arr, length, min, max, interval);
			search_time = clock() - start_time;
			cout << "ВРЕМЯ РАБОТЫ: " << search_time << endl;
			break;
	}

}


const string filename = "file.txt";

int main()
{ 
	srand(time(NULL));
	setlocale(LC_ALL, "rus");

	ofstream fout(filename);
	cout << "КАКОЙ МАССИВ ХОТИТЕ СОЗДАТЬ?\n1.ВОЗРАСТАЮЩИЙ\n2.УБЫВАЮЩИЙ\n3.СЛУЧАЙНЫЙ\n4.ПИЛООБРАЗНЫЙ\n5.СИНУСОИДНЫЙ\n6.СТУПЕНЧАТЫЙ\nВаш выбор: ";
	int num;
	cin >> num;
	cout << endl;
	int min;
	int max;
	int interval;
	int length;
	system("cls");
	cout << "ВВЕДИТЕ ДЛИНУ МАССИВА: ";
	cin >> length;
	float* arr = new float[length];
	switch_num(num, length, arr);
	if (length < 150 || length > 200) {
		int var;
		cout << "ВЫВЕСТИ МАТРИЦУ:\n1.ДА\n2.НЕТ\nОТВЕТ: ";
		cin >> var;
		cout << "\n";
		if (var == 1)
			for (int i = 0; i < length; i++)
				cout << arr[i] << "\n";
		else
			return 0;
	}
	else {
		for (int i = 0; i < length; i++) {
			cout << arr[i] << "\n";
			fout << arr[i] << "\n";
		}
	}
}
