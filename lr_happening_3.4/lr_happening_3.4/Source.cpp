// Однонаправленный кольцевой целочисленный список

#include <iostream>

using namespace std;

const int n = 5;


struct Element { int data; Element* next; };


void searchInList() {

}

void recordIntoList(int a[], int n, Element* begin, Element* last) {
	
	int i = 0;
	while (n > 0) {
		if (!begin) {
			Element* elem = new Element;
			elem->data = a[i];
			i++;
			elem->next = NULL;
			begin = last = elem;
		}
		else {
			Element* elem = new Element;
			elem->data = a[i];
			i++;
			last->next = elem;
			last = elem;
		}
		n--;
	}
	last->next = begin;
}

char redBold[] = "\x1b[31;1m";
char normal[] = "\x1b[39;49m";

void printMenu() {
	system("cls");
	cout << redBold << "Что вы хотите сделать?\n";
	cout << "1. Перейти на следующий элемент в списке\n";
	cout << "2. Выйти из программы\n";
	cout << ">" << normal;
}



int main() {
	setlocale(LC_ALL, "rus");
	int A[n] = { 5,2,7,8,1 };
	/*int n;
	cout << "Введите n: ";
	cin >> n;
	cout << endl << "Введите массив: ";
	int* arr = new int[n];
	cout << endl;*/
	Element* begin = NULL;
	Element* last = NULL;
	
	printMenu();
}