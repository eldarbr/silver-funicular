#include <iostream>
#include <ctime>

using namespace std;


void generate_ascending(float* arr, unsigned int length);
void generate_descending(float* arr, unsigned int length);
void generate_random(float* arr, unsigned int length);
void generate_sawtooth(float* arr, unsigned int length, float min = NULL, float max = NULL, float interval = NULL);
void generate_sinuous(float* arr, unsigned int length, float min = NULL, float max = NULL, float interval = NULL);
void generate_stepped(float* arr, unsigned int length, float min = NULL, float max = NULL, float interval = NULL);

int random(int min, int max);
int random();
float random_fl();
int random_sign();



int random() {
	return rand();
}

int random(int min, int max) {
	return min + (max - min) * random_fl();
}

float random_fl() {
	return rand() / float(RAND_MAX);
}

int random_sign() {
	int qqq = random();
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

// fast approximation of SINE function based on Taylor series
float sine(float x) {
	float pi = 3.1415;
	float result = 5040 * x;
	x = x * x * x;
	result -= 840 * x;
	x = x * x * x;
	result += 42 * x;
	x = x * x * x;
	result -= x;
	return result / 5040;
}

void generate_sinuous(float* arr, unsigned int length, float min, float max, float interval) {
	*(arr) = sin(0);
	int dobby = max - (min + max) / 2;
	for (int i = 1; i < length; i++) {
		*(arr + i) = sin(i)*dobby;
	}
}

void generate_stepped(float* arr, unsigned int length, float min, float max, float interval) {
	float step = (max - min) / (length/interval);
	cout << step << endl;
	*(arr) = min;
	int k = 0;
	int num = 1;
	for (int i = 1; i < length; i++) {
		float q = (rand() / 10000) * random_sign();
		*(arr + i) = *(arr + k) + q;
		cout << "=  " << q << endl;
		num++;
		if (num == interval) {
			num = 0;
			k = i + 1;
			*(arr + k) = *(arr + i) + step;
		}
	}
}
	

void switch_num(int num, int length, float* arr, int min, int max, int interval) {
	switch (num) {
		case 1:
			generate_ascending(arr, length);
			break;
		case 2:
			generate_descending(arr, length);
			break;
		case 3:
			generate_random(arr, length);
			break;
		case 4:
			generate_sawtooth(arr, length, min, max, interval);
			break;
		case 5:
			generate_sinuous(arr, length, min, max, interval);
			break;
		case 6:
			generate_stepped(arr, length, min, max, interval);
			break;
	}

}

int main()
{ 
	srand(time(NULL));
	setlocale(LC_ALL, "rus");


	cout << "КАКОЙ МАССИВ ХОТИТЕ СОЗДАТЬ?\n1.ВОЗРАСТАЮЩИЙ.\n2.УБЫВАЮЩИЙ.\n3.СЛУЧАЙНЫЙ.\n4.ПИЛООБРАЗНЫЙ.\n5.СИНУСОИДНЫЙ.\n6.СТУПЕНЧАТАЯ.\n";
	int num;
	cin >> num;
	int min;
	int max;
	int interval;
	int length;
	if (num > 3){
		cout << "ВВЕДИТЕ ДЛИНУ МАССИВА: ";
		cin >> length;
		cout << "ВВВЕДИТЕ НИЖНЮЮ ГРАНИЦУ: ";
		cin >> min;
		cout << "ВВЕДИТЕ ВЕРХНЮЮ ГРАНИЦУ: ";
		cin >> max;
		cout << "ВВЕДИТЕ ИНТЕРВАЛ: ";
		cin >> interval;
	}
	else {
		cout << "ВВЕДИТЕ ДЛИНУ МАССИВА: ";
		cin >> length;
	}
	float* arr = new float[length];
	switch_num(num, length, arr, min, max, interval);
	for (int i = 0; i < length; i++) cout  <<  arr[i] << "\n";
}
