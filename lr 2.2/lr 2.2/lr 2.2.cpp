#include <iostream>
#include <fstream>

using namespace std;

void Errors(int x) {
    switch (x) {
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
    }
}

int maxim(int ber, int ike) {
    if (ber > ike)
        return ber;
    else
        return ike;
}

const string filename = "file.txt";

int main()
{
    setlocale(LC_ALL, "rus");
    system("color F0");
    int N, M;
    int fl;
    ifstream fn;
    fn.open(filename);
    cout << "Введите \"0\", если хотите ввести данные с руки,  \"1\", если хотите считать их из файла" << endl;
    cin >> fl;
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
        if (!fn.is_open())
            Errors(1);
        if (fn.eof())
            Errors(2);
        fn >> N >> M;
        if (N == 0)
            Errors(3);
        if (M == 0)
            Errors(4);
        cout << "Количество строк:  " << N << endl;
        cout << "Количество столбцов:  " << M << endl;
    }

    int** matrix = new int*[N];
    for (int i = 0; i < N; i++)
        matrix[i] = new int[M];
    if (fl == 0) {
        cout << "Введите подряд " << N * M << " целых чисел, разделенных пробелом " << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> matrix[i][j];
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                fn >> matrix[i][j];
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    cout << endl << endl << "           ЗАDАНИЕ 1           " << endl;
    int dis = 1;
    int max_dis = 0;
    int sign=0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] == 0) {
                dis = 1;
                sign++;
                break;
            }
            dis = dis * matrix[i][j];
        }
        if (sign == 0) {
            cout << "Произведение элементов " << i+1 << " строки: " << dis << endl;
            max_dis = maxim(max_dis, dis);
        }
        dis = 1;
        sign = 0;
    }
    cout << endl << endl << "           ЗАDАНИЕ 2           " << endl;
    cout << "Максимальное произведение элементов строки, не содержащей ноль:    " << max_dis << endl << endl;;
    system("pause");
}