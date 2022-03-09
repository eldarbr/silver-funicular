#include <iostream>
using namespace std;

// НАХОЖДЕНИЕ ДЛИНЫ СТРОКИ
int get_str_length(char a[]) {
    int length = 0;
    char last_read = a[0];
    while (last_read != '\0') {
        length += 1;
        last_read = a[length];
    }
    return length;
}

// НАХОЖДЕНИЕ ДЛИНЫ МАССИВА ЧИСЕЛ
int get_array_lenght(int arr[]) {
    return sizeof(arr) / sizeof(*arr);
}

// ПРОВЕРКА НАЛИЧИЯ ЭЛЕМЕНТА В МАССИВЕ
bool index_in_array(int index, int arr[]) {
    for (int i = 0; i < get_array_lenght(arr); i++) {
        if (arr[i] == index) return true;
    }
    return false;
}

// ВЫВОД СТРОКИ С ПОДЧЕРКИВАНИЕМ СИМВОЛОВ ПО ИНДЕКСАМ
void print_with_highlits(char str[], int highlight_index[]) {
    int length = get_str_length(str);
    for (int i = 0; i < length; i++) {
        if (index_in_array(i, highlight_index)) {
            cout << "\x1b[4m" << str[i] << "\x1b[0m";
        }
        else {
            cout << str[i];
        }
    }
}


int main()
{

}
