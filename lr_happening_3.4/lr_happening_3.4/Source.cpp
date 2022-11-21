// Однонаправленный кольцевой целочисленный список

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

// поиск индекса элемента в списке
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

// вставка в конец списка
List* InsertToEnd(List* list, int data) {
	Element* now = new Element;
	now->data = data;
	now->index = list->last->index + 1;
	list->last->next = now;
	now->next = list->first;
	list->last = now;
	return list;
}

// удаление элемента по индексу
List* DeleteFromList(List* list, int index) {
	Element* now = list->first;

	if (index > list->last->index || index < list->first->index) return list;

	if (list->first == NULL) return list;
	if (list->first == list->last && list->first->index == index) {
		list->first = NULL;
		list->last = NULL;
		return list;//  список пуст
	}
	if (list->first->index == index) {    //  удаляется первый элемент
		list->first = now->next;
		list->last->next = now->next;
		now = list->first;
		for (int j = 0; j <= list->last->index; j++) {
			now->index = now->index--;
			now = now->next;
		}
	}
	else if (list->last->index == index) {  //  удаляется последний элемент
		if (list->first == list->last) {  //  первый элемент совпадает с последним
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

//удаляем листок
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

// ввод для интерфейса пользователя
int ConsoleInterfaceInput(ConsoleInputBBB albhljafgh) {
	int variant;
	cin >> variant;
	if (albhljafgh == Creating) {
		while (variant != 1 && variant != 2) {
			cout << "Некорректное значение. Введите снова: ";
			cin >> variant;
		}
	}
	else if (albhljafgh == Acting) {
		while (variant != 1 && variant != 2 && variant != 3 && variant != 4 && variant != 5 && variant != 6) {
			cout << "Некорректное значение. Введите снова: ";
			cin >> variant;
		}
	}
	return variant;
}

// ввод индекса для удаления
List* ConsoleInterfaceDelete(List* list) {
	int index;
	cout << "Введите индекс элемента для удаления:\n> ";
	cin >> index;
	if (index > list->last->index) {
		cout << redColor << "\nЭлемента под таким индексом не существует.\n" << supremeColor;
		system("cls");
	}
	return DeleteFromList(list, index);
}

// ввод для вставки в конец списка
List* ConsoleInterfaceInsertToEnd(List* list) {
	int data;
	cout << "Введите число для вставки:\n> ";
	cin >> data;
	return InsertToEnd(list, data);
}

// ввод для поиска по значению
int ConsoleInterfaceFindByValue(List* list) {
	int value;
	cout << "\nВведите ключ поиска\n> ";
	cin >> value;
	return FindByValue(list, value);
}

// вывод списка
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

// интерфейс для пользователя
void ConsoleInterface() {
	setlocale(LC_ALL, "rus");
	List* list = new List;
	list->first = NULL;
	list->last = NULL;
	int variant;
	int index;
	do {
		if (list->first != NULL) {		// список задан
			system("cls");
			ConsoleInterfaceOutputList(list);
			cout
				<< "\nЧто вы хотите сделать?\n"
				<< "1. Вывести весь список на экран\n"
				<< "2. Найти в списке элемент с заданным значением\n"
				<< "3. Вставить элемент в конец списка\n"
				<< "4. Удалить элемент из позиции списка с заданным индексом\n"
				<< "5. Удалить список\n"
				<< "6. Выход из программы\n"
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
					cout << redColor << "\n\tПодходящий элемент не найден в списке.\n" << supremeColor;
				else
					cout << "Элемент найден в списке. Его индекс: " << redColor << index << supremeColor << endl;
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
		else {					// список не задан
			system("cls");
			cout << "\tЧто вы хотите сделать?\n"
				<< "1. Создать список\n"
				<< "2. Выход из программы\n"
				<< "> ";
			variant = ConsoleInterfaceInput(Creating);
			switch (variant)
			{
			case 1:
				int n;
				cout << "\nВведите количество элементов списка\n> ";
				cin >> n;
				int* arr = new int[n];
				cout << "\nВведите " << redColor << n << supremeColor << " целочисленных чисел\n> ";
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