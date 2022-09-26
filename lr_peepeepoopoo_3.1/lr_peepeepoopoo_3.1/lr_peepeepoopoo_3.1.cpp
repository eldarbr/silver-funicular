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
	float mid = (max + min) / 2;
	float step = mid / interval;
	int k = 0;
	*(arr) = mid;
	for (int i = 1; i < length; i++) {
		*(arr + i) = *(arr + i - 1) + pow(-1, k) * step;
		if (arr[i]+ pow(-1, k) * step < min || arr[i]+ pow(-1, k) * step > max)
			k++;
	}
}

void generate_stepped(float* arr, unsigned int length, float min, float max, float interval) {
	float step = (max - min) / interval;
	*(arr) = min;
	int k = 0;
	int num = 2;
	for (int i = 1; i < length; i++) {
		float q = random(0, (max - min) / 10) * random_sign();
		*(arr + i) = *(arr + k) + q;
		cout << " " << q;
		num++;
		if (num == interval) {
			num = 1;
			k = i + 1;
			*(arr + k) = *(arr + i) + step;
		}
	}
}
	

int main()
{ 
	srand(time(NULL));
	setlocale(LC_ALL, "rus");


	cout << "КАКОЙ МАССИВ ХОТИТЕ СОЗДАТЬ?\n1.ВОЗРАСТАЮЩИЙ.\n2.УБЫВАЮЩИЙ.\n3.СЛУЧАЙНЫЙ.\n4.ПИЛООБРАЗНЫЙ.\n5.СИНУСОИДНЫЙ.\n6.СТУПЕНЧАТАЯ.";
	int length;
	int min;
	int max;
	int interval;
	cout << "BBE4UTE 4/\\UNY MACCUBA: ";
	cin >> length;
	float* arr = new float[length];
	cout << "ВВВЕДИТЕ НИЖНЮЮ ГРАНИЦУ: ";
	cin >> min;
	cout << "ВВЕДИТЕ ВЕРХНЮЮ ГРАНИЦУ: ";
	cin >> max;
	cout << "ВВЕДИТЕ ИНТЕРВАЛ: ";
	cin >> interval;
	generate_stepped(arr, length, min, max, interval);
	//generate_sinuous(arr, length, min, max, interval);
	cout.precision(5);
	for (int i = 0; i < length; i++) cout  <<  arr[i] << "\n";
	//cout << sine(-.5236) << endl << sine(.5236) << endl;
	return 0;
}
