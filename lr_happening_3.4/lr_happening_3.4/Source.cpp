// ���������������� ��������� ������������� ������

#include <iostream>

using namespace std;


struct Element { int data; int index; Element* next; };

struct List { Element* first; Element* last; };

char red[] = "\x1b[31;1m";
char normal[] = "\x1b[39;49m";

int getVariant() {
	int variant;
	cin >> variant;

	while (variant != 1 && variant != 2 && variant!= 3 && variant !=4 && variant !=5 && variant !=6) {
		cout << "������������ ��������. ������� �����: ";
		cin >> variant;
	}
	return variant;
}

//******************************************************************//
//						������ � ������							    //
//******************************************************************//
List* recordIntoList(int a[], int n, List* list) {
	list->first = NULL;
	list->last = NULL;
	Element* now = NULL;
	for (int i = 0; i < n; i++) {
		list->last = new Element;
		list->last->data = a[i];
		list->last->index = i;
		if (list->first == NULL) {
			list->last->next = NULL;
			list->first = list->last;
		}
		else {
			now = list->first;
			while (now != 0) {
				if (now->next == NULL) {
					list->last->next = NULL;
					now->next = list->last;
					break;
				}
				now = now->next;
			}
		}
	}
	list->last->next = list->first;
	return list;
}


//*****************************************************************//
//				����� ������� �������� � ������					   //
//*****************************************************************//
int findIndexInList(Element* now) {
	int key;
	int counter = 0;
	cout << "\n������� ���� ������\n> ";
	cin >> key;
	while (now && now->data != key && counter < 5) {
		now = now->next;
		counter++;
	}
	if (counter == 5) {
		return -1;
	}
	return now->index;
}


//******************************************************************//
//					������� � ����� ������						   //
//******************************************************************//
List* push(List* list) {
	int number;
	cout << "������� ����� ��� �������:\n> ";
	cin >> number;
	Element* now = new Element;
	now->data = number;
	now->index = list->last->index + 1;
	list->last->next = now;
	now->next = list->first;
	return list;
}

//******************************************************************//
//				�������� �������� ��� �������� �������				//
//******************************************************************//
List* deleteByIndex(List* list) {
	Element* now = list->first;
	int number;
	cout << "������� ����� �������� ��� ��������:\n> ";
	cin >> number;
	if (number > list->last->index) {
		cout << red << "\n�������� ��� ����� ������� �� ����������.\n" << normal;
		system("cls");
	}
	if (list->first == NULL) return NULL;		//  ������ ����
	if (list->first->index == number) {		//  ��������� ������ �������
		list->first = now->next;
	}
	else if (list->last->index == number) {	//  ��������� ��������� �������
		if (list->first == list->last) {	//  ������ ������� ��������� � ���������
			list->first = now->next;
		}
		while (now->next != list->last) now = now->next;
		now->next = list->first;
		delete list->last;
		list->last = now;
	}
	else {
		int i = 0;
		while (now->next->index != number) {
			now = now->next;
			i++;
		}
		now->next = now->next->next;
		for (int j = i + 1; j < list->last->index; j++) {
			now->next->index = now->next->index - 1;
			now = now->next;
		}
	}
	return list;
}

//******************************************************************//
//						���������� ����							    //
//******************************************************************//
void menuRealisation() {
	setlocale(LC_ALL, "rus");
	List* list = new List;
	list->first = NULL;
	list->last = NULL;
	int variant;
	int index;
	Element* now = list->first;
	do {
		if (now != NULL) {		// ������ �����
			system("cls");
			cout << "\t������� �������: " << red << now->data << normal << "; � ��������: " << red << now->index << "\n\n" << normal
			 << "\t��� �� ������ �������?\n"
			 << "1. ������� �� ��������� ������� � ������\n"
			 << "2. ����� � ������ ������� � �������� ���������\n"
			 << "3. �������� ������� � ����� ������\n"
			 << "4. ������� ������� �� ������� ������ � ��������  �������\n"
			 << "5. ������� ������\n"
			 << "6. ����� �� ���������\n"
			 << "> ";
			variant = getVariant();
			switch (variant) {
			case 1:
				now = now->next;
				break;
			case 2:
				index = findIndexInList(now);
				if (index == -1)
					cout << red << "\n\t���������� ������� �� ������ � ������.\n" << normal;
				else
					cout << "������� ������ � ������. ��� ������: " << red << index << normal << endl;
				system("pause");
				break;
			case 3:
				list = push(list);
				break;
			case 4:
				list = deleteByIndex(list);
			case 5:
				now = list->first->next;
				for (int i = 0; i < list->last->index; i++) {
					delete list->first;
					list->first = now;
					now = list->first->next;
				}
				now = NULL;
			}
		}
		else {					// ������ �� �����
			system("cls");
			cout << "\t��� �� ������ �������?\n"
			 << "1. ������� ������\n"
			 << "2. ����� �� ���������\n"
			 << "> ";
			variant = getVariant();
			switch (variant)
			{
			case 1:
				int n;
				cout << "\n������� ���������� ��������� ������\n> ";
				cin >> n;
				int* arr = new int[n];
				cout << "\n������� " << red << n << normal << " ������������� �����\n> ";
				for (int i = 0; i < n; i++) cin >> arr[i];
				list = recordIntoList(arr, n, list);
				break;
			}
			now = list->first;
		}
	} while (variant != 6 && now != NULL || variant != 2 && now == NULL);
}

int main() {
	menuRealisation();
}