// ќднонаправленный кольцевой целочисленный список

#include <iostream>

using namespace std;

const int n = 5;

struct elem { int data; elem* next; };

struct List { elem* begin; elem* end; };

void searchInList() {

}

void recordIntoList(List* list, int *a[], int n) {
	List *ptr = new List;
	if (!list->begin)
		list->begin = ptr;
	else
		list->end->next = 

}

int main() {
	setlocale(LC_ALL, "rus");
	int n;
	cout << "¬ведите n: ";
	cin >> n;
	cout << endl << "¬ведите массив: ";
	int* arr = new int[n];
	cout << endl;
	elem* begin = NULL;
	elem* last = NULL;
	elem* list = NULL;
	
	
}