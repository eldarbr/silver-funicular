// Однонаправленный кольцевой целочисленный список

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
		cout << "Некорректное значение. Введите снова: ";
		cin >> variant;
	}
	return variant;
}

//******************************************************************//
//						ЗАПИСЬ В СПИСОК							    //
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
//				ПОИСК ИНДЕКСА ЭЛЕМЕНТА В СПИСКЕ					   //
//*****************************************************************//
int findIndexInList(Element* now) {
	int key;
	int counter = 0;
	cout << "\nВведите ключ поиска\n> ";
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
//					ВСТАВКА В КОНЕЦ СПИСКА						   //
//******************************************************************//
List* push(List* list) {
	int number;
	cout << "Введите число для вставки:\n> ";
	cin >> number;
	Element* now = new Element;
	now->data = number;
	now->index = list->last->index + 1;
	list->last->next = now;
	now->next = list->first;
	return list;
}

//******************************************************************//
//				УДАЛЕНИЕ ЭЛЕМЕНТА ПОД ЗАДАННЫМ НОМЕРОМ				//
//******************************************************************//
List* deleteByIndex(List* list) {
	Element* now = list->first;
	int number;
	cout << "Введите номер элемента для удаления:\n> ";
	cin >> number;
	if (number > list->last->index) {
		cout << red << "\nЭлемента под таким номером не существует.\n" << normal;
		system("cls");
	}
	if (list->first == NULL) return NULL;		//  список пуст
	if (list->first->index == number) {		//  удаляется первый элемент
		list->first = now->next;
	}
	else if (list->last->index == number) {	//  удаляется последний элемент
		if (list->first == list->last) {	//  первый элемент совпадает с последним
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
//						РЕАЛИЗАЦИЯ МЕНЮ							    //
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
		if (now != NULL) {		// список задан
			system("cls");
			cout << "\tТекущий элемент: " << red << now->data << normal << "; с индексом: " << red << now->index << "\n\n" << normal
			 << "\tЧто вы хотите сделать?\n"
			 << "1. Перейти на следующий элемент в списке\n"
			 << "2. Найти в списке элемент с заданным значением\n"
			 << "3. Вставить элемент в конец списка\n"
			 << "4. Удалить элемент из позиции списка с заданным  номером\n"
			 << "5. Удалить список\n"
			 << "6. Выход из программы\n"
			 << "> ";
			variant = getVariant();
			switch (variant) {
			case 1:
				now = now->next;
				break;
			case 2:
				index = findIndexInList(now);
				if (index == -1)
					cout << red << "\n\tПодходящий элемент не найден в списке.\n" << normal;
				else
					cout << "Элемент найден в списке. Его индекс: " << red << index << normal << endl;
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
		else {					// список не задан
			system("cls");
			cout << "\tЧто вы хотите сделать?\n"
			 << "1. Создать список\n"
			 << "2. Выход из программы\n"
			 << "> ";
			variant = getVariant();
			switch (variant)
			{
			case 1:
				int n;
				cout << "\nВведите количество элементов списка\n> ";
				cin >> n;
				int* arr = new int[n];
				cout << "\nВведите " << red << n << normal << " целочисленных чисел\n> ";
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