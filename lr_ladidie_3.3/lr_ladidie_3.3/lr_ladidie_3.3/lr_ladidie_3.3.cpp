#include <iostream>

using namespace std;

void ShellSort();
void ChooseSort();


void swap(int* arr, int i) {
	int temp;
	temp = arr[i];
	arr[i] = arr[i - 1];
	arr[i - 1] = temp;
}

int main()
{
	
}