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
	return static_cast<float>(rand()) / RAND_MAX;
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


int main()
{
	srand(time(NULL));

	int length;
	cout << "BBE4UTE 4/\\UNY MACCUBA: ";
	cin >> length;
	float* arr = new float[length];

	generate_descending(arr, length);
	for (int i = 0; i < length; i++) cout << arr[i] << "\n";

	return 0;
}
