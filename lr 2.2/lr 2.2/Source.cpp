#include <iostream>
#include <fstream>

using namespace std;

// ФУНКЦИЯ ДЛЯ ВЫВОДОВ ОШИБКИ ПО КОДАМ
void Errors(int x) {
    switch (x) {
    case 0:
        cout << "Ошибка! Перезапустите программу и введите \"1\" или \"0\"!";
        exit(0);
    case 1:
        cout << "Ошибка! Файл не найден! " << endl;
        exit(0);
    case 2:
        cout << "Ошибка! Файл пустой! " << endl;
        exit(0);
    case 3:
        cout << "Ошибка! Количество строк должно быть больше нуля! " << endl;
        exit(0);
    case 4:
        cout << "Ошибка!Количество столбцов должно быть больше нуля!" << endl;
        exit(0);
    case 5:
        cout << "Ошибка! В файле недостаточно данных! " << endl;
        exit(0);
    case 6:
        cout << "Ошибка! В файле недостаточно элементов массива! " << endl;
        exit(0);
    }
}

// ФУНКЦИЯ ДЛЯ ВЫДЕЛЕНИЯ ПАМЯТИ ПОД МАТРИЦУ
int **memory_for_matrix(int row, int col) {
    int** arr = new int* [row];
    for (int i = 0; i < row; i++)
        arr[i] = new int[col];
    return arr;
}

// ФУНКЦИЯ ВВОДА МАТРИЦЫ С РУКИ
void input_matrix(int** arr, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> arr[i][j];
}

// ФУНКЦИЯ ВВОДА МАТРИЦЫ ИЗ ФАЙЛА
void matrix_from_file(int** arr, int row, int col, const string filename) {
    ifstream FN;
    int a[2];
    FN.open(filename);
    FN >> a[0] >> a[1];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) {
            FN >> arr[i][j];
            if (FN.eof())
                if (j != col-1)
                    Errors(6);
        }
}

// ФУНКЦИЯ ПЕЧАТИ МАТРИЦЫ
void print_matrix(int** arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << arr[i][j]<< "\t";
        cout << endl;
    }
}

// ФУНКЦИЯ ДЛЯ НАХОЖДЕНИЯ МАКСИМУМА
long long maxim(long long ber, long long ike) {
    if (ber > ike)
        return ber;
    else
        return ike;
}

// ФУНКЦИЯ ДЛЯ ННАХОЖДЕНИЯ ПРОИЗВЕДЕНИЙ СТРОК МАТРИЦЫ ПО ЗАДАНИЮ
void product(int** arr, int row, int col) {
    long long prod = 1;
    long long max_prod = 1;
    int sign = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == 0) {
                prod = 1;
                sign++;
                break;
            }
            prod = prod * arr[i][j];
        }
        if (sign == 0) {
            cout << "Произведение элементов " << i + 1 << " строки: " << prod << endl;
            max_prod = maxim(max_prod, prod);
        }
        prod = 1;
        sign = 0;
    }
    cout << "Максимальное произведение элементов строки, не содержащей ноль:    " << max_prod << endl << endl;
}

const string filename = "file.txt";
//const string filename = "test1.txt";
//const string filename = "test2.txt";
//const string filename = "err_test1.txt";
//const string filename = "err_test2.txt";
//const string filename = "no_file.txt";
//const string filename = "hollow_file.txt";
//const string filename = "err_test3.txt";
//const string filename = "err_test4.txt";

int main()
{
    setlocale(LC_ALL, "rus");
    system("color F0");
    int N, M;
    int fl;
    cout << "Введите \"0\", если хотите ввести данные с руки,  \"1\", если хотите считать их из файла" << endl;
    cin >> fl;
    ifstream fn;
    if (fl == 0) {
        cout << "Введите количество строк:  ";
        cin >> N;
        if (N == 0)
            Errors(3);
        cout << endl << "Введите количество столбцов:   ";
        cin >> M;
        if (M == 0)
            Errors(4);
        cout << endl;
    }
    else if (fl == 1) {
        fn.open(filename);
        if (!fn.is_open())
            Errors(1);
        if (fn.eof())
            Errors(2);
        fn >> N;
        if (fn.eof())
            Errors(5);
        if (N == 0)
            Errors(3);
        fn >> M;
        if (M == 0)
            Errors(4);
        if (fn.eof())
            Errors(5);
        cout << "Количество строк:  " << N << endl;
        cout << "Количество столбцов:  " << M << endl;
    }
    else {
        Errors(0);
        //goto 
    }
    // ВЫДЕЛЕНИЕ ПАМЯТИ ПОД МАТРИЦУ
    int** matrix = memory_for_matrix(N, M);

    // ЧТЕНИЕ МАТРИЦЫ С РУКИ ИЛИ ИЗ ФАЙЛА
    if (fl == 0) {
        cout << "Введите подряд " << N * M << " целых чисел, разделенных пробелом " << endl;
        input_matrix(matrix, N, M);
        cout << "Введенная матрица:" << endl;
        print_matrix(matrix, N, M);
    }
    else {
        matrix_from_file(matrix, N, M, filename);
        cout << "Полученная матрица:" << endl;
        print_matrix(matrix, N, M);
    }

    // РАССЧЕТ ПРОИЗВЕДЕНИЙ СТРОК МАТРИЦЫ ПО ЗАДАНИЮ
    product(matrix, N, M);
    system("pause");
}