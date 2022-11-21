// ���������������� ��������� ������������� ������

#include <iostream>

using namespace std;

enum ConsoleInputBBB { Creating, Acting };

// element
struct Element {
	int data;
	int index;
	Element* next;
};

// list
struct List {
	Element* first;
	Element* last;
};

char redColor[] = "\x1b[31;1m";			// red color for console interface
char supremeColor[] = "\x1b[39;49m";	// white color for console interface


// wr*te *nto l*st some sh*t sheeeeeeeeeeeeeeeesh
// create good list
List* CreateGList(int a[], int n, List* list) {
	if (n < 1) {
		cout << "wrong abobus number\n";
		system("pause");
		List* leNewBLiszt = new List;
		leNewBLiszt->first = NULL;
		return leNewBLiszt;
	}
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

// ����� ������� �������� � ������
int FindByValue(List* list, int value) {
	int counter = 0;
	Element* current = list->first;
	while (current && current->data != value && counter <= list->last->index) {
		current = current->next;
		counter++;
	}
	if (counter == list->last->index + 1) {
		return -1;
	}
	else {
		return current->index;
	}
}

// ������� � ����� ������
List* InsertToEnd(List* list, int data) {
	Element* now = new Element;
	now->data = data;
	now->index = list->last->index + 1;
	list->last->next = now;
	now->next = list->first;
	list->last = now;
	return list;
}

// �������� �������� �� �������
List* DeleteFromList(List* list, int index) {
	Element* now = list->first;

	if (index > list->last->index || index < list->first->index) return list;

	if (list->first == NULL) return list;
	if (list->first == list->last && list->first->index == index) {
		list->first = NULL;
		list->last = NULL;
		return list;//  ������ ����
	}
	if (list->first->index == index) {    //  ��������� ������ �������
		list->first = now->next;
		list->last->next = now->next;
		now = list->first;
		for (int j = 0; j <= list->last->index; j++) {
			now->index = now->index--;
			now = now->next;
		}
	}
	else if (list->last->index == index) {  //  ��������� ��������� �������
		if (list->first == list->last) {  //  ������ ������� ��������� � ���������
		  //list->first = now->next;
			delete list->first;
			return list;
		}
		while (now->next != list->last) now = now->next;
		now->next = list->first;
		delete list->last;
		list->last = now;
	}
	else {
		int i = 0;
		while (now->next->index != index) {
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

//������� ������
List* DeleteWholeList(List* list) {
	while (list->last != list->first) {
		list->first = list->first->next;
		delete list->last->next;
		list->last->next = list->first;
	}
	delete list->first;
	list = new List;
	list->first = NULL;
	return list;
}

// ���� ��� ���������� ������������
int ConsoleInterfaceInput(ConsoleInputBBB albhljafgh) {
	int variant;
	cin >> variant;
	if (albhljafgh == Creating) {
		while (variant != 1 && variant != 2) {
			cout << "������������ ��������. ������� �����: ";
			cin >> variant;
		}
	}
	else if (albhljafgh == Acting) {
		while (variant != 1 && variant != 2 && variant != 3 && variant != 4 && variant != 5 && variant != 6) {
			cout << "������������ ��������. ������� �����: ";
			cin >> variant;
		}
	}
	return variant;
}

// ���� ������� ��� ��������
List* ConsoleInterfaceDelete(List* list) {
	int index;
	cout << "������� ������ �������� ��� ��������:\n> ";
	cin >> index;
	if (index > list->last->index) {
		cout << redColor << "\n�������� ��� ����� �������� �� ����������.\n" << supremeColor;
		system("cls");
	}
	return DeleteFromList(list, index);
}

// ���� ��� ������� � ����� ������
List* ConsoleInterfaceInsertToEnd(List* list) {
	int data;
	cout << "������� ����� ��� �������:\n> ";
	cin >> data;
	return InsertToEnd(list, data);
}

// ���� ��� ������ �� ��������
int ConsoleInterfaceFindByValue(List* list) {
	int value;
	cout << "\n������� ���� ������\n> ";
	cin >> value;
	return FindByValue(list, value);
}

// ����� ������
void ConsoleInterfaceOutputList(List* list) {
	Element* current = list->first;
	cout << "index:\t";
	do {
		cout << current->index << "\t";
		current = current->next;
	} while (current->index != list->first->index);
	cout << "\nvalue:\t";
	current = list->first;
	do {
		cout << current->data << "\t";
		current = current->next;
	} while (current->index != list->first->index);
	cout << "\n";
}

// ��������� ��� ������������
void ConsoleInterface() {
	setlocale(LC_ALL, "rus");
	List* list = new List;
	list->first = NULL;
	list->last = NULL;
	int variant;
	int index;
	do {
		if (list->first != NULL) {		// ������ �����
			system("cls");
			ConsoleInterfaceOutputList(list);
			cout
				<< "\n��� �� ������ �������?\n"
				<< "1. ������� ���� ������ �� �����\n"
				<< "2. ����� � ������ ������� � �������� ���������\n"
				<< "3. �������� ������� � ����� ������\n"
				<< "4. ������� ������� �� ������� ������ � �������� ��������\n"
				<< "5. ������� ������\n"
				<< "6. ����� �� ���������\n"
				<< "> ";
			variant = ConsoleInterfaceInput(Acting);
			switch (variant) {
			case 1:
				ConsoleInterfaceOutputList(list);
				system("pause");
				break;
			case 2:
				index = ConsoleInterfaceFindByValue(list);
				if (index == -1)
					cout << redColor << "\n\t���������� ������� �� ������ � ������.\n" << supremeColor;
				else
					cout << "������� ������ � ������. ��� ������: " << redColor << index << supremeColor << endl;
				system("pause");
				break;
			case 3:
				list = ConsoleInterfaceInsertToEnd(list);
				break;
			case 4:
				list = ConsoleInterfaceDelete(list);
				break;
			case 5:
				list = DeleteWholeList(list);
				break;
			}
		}
		else {					// ������ �� �����
			system("cls");
			cout << "\t��� �� ������ �������?\n"
				<< "1. ������� ������\n"
				<< "2. ����� �� ���������\n"
				<< "> ";
			variant = ConsoleInterfaceInput(Creating);
			switch (variant)
			{
			case 1:
				int n;
				cout << "\n������� ���������� ��������� ������\n> ";
				cin >> n;
				int* arr = new int[n];
				cout << "\n������� " << redColor << n << supremeColor << " ������������� �����\n> ";
				for (int i = 0; i < n; i++) cin >> arr[i];
				list = CreateGList(arr, n, list);
				break;
			}
		}
	} while (variant != 6 && list->first != NULL || variant != 2 && list->first == NULL);
}



int main() {
	ConsoleInterface();
}