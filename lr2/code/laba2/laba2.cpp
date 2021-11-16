#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


// псевдографика - заголовок таблицы
void HeadTable() {
    cout << "\t"
        << char(218) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(191) << endl;
    cout << "\t"
        << char(179)  << setfill(' ') << setw(19)<< "#"
        << char(179)  << setfill(' ') << setw(19)<< "x"
        << char(179)  << setfill(' ') << setw(19)<< "F(x)"
        << char(179)  << setfill(' ') << setw(19)<< "G(x)"
        << char(179) << endl;
    cout << "\t"
        << char(195) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setw(20)
        << char(197) << setw(20) << char(180) << endl;
    cout.setf(ios::showpoint | ios::fixed);

}

// псевдографика - завершение таблицы
void BottomTable() {
    cout << "\t"
        << char(192) << setfill(char(196)) << setw(20)
        << char(193) << setfill(char(196)) << setw(20)
        << char(193) << setfill(char(196)) << setw(20)
        << char(193) << setfill(char(196)) << setw(20)
        << char(217) << endl;
}

// псевдографика - тело таблицы
void  BetweenTheRaws() {
    cout << "\t"
        << char(195) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(180) << endl;
}

// расчет значения функции F(x) в точке x
double F(double x) {
    return pow(x - 1, 3);
}

// расчет значения функции G(x) в точке x
double G(double x) {
    return pow(x + 5, 3) / (1 + pow(sin(x), 2));
}

// вывод строк таблицы с автоматическим закрытием таблицы
void PrintTable(double x, int i, int N, bool debug = false) {
    if (debug) {
        cout << x << "\t" << F(x) << "\t" << G(x) << endl;
    }
    else {
        cout << "\t" << char(179) << setw(19) << setfill(char(255)) << i
            << char(179) << setw(19) << setprecision(4) << x
            << setfill(char(255))
            << char(179) << setw(19) << setprecision(4) << F(x)
            << setfill(char(255))
            << char(179) << setw(19) << setprecision(4) << G(x)
            << setfill(char(255)) << char(179) << endl;
        if (i != N)
            BetweenTheRaws();
        else
            BottomTable();
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    system("color F0");

    //Инициализация переменных
    double A;
    double B;
    int N;
    double h;
    double x;
    int i;
    bool debug = false;

    // Ввод и проверка данных
    cout << "Введите А - координату начала отрезка [A;B]: \t";
    cin >> A;
    cout << "Введите B - координату конца отрезка [A;B]: \t";
    cin >> B;

    if (A > B) {
        cout << "\nОШИБКА! А должен быть меньше или равен В!";
        return 1;
    }
    cout << "Введите N - количество интервалов, на которые разделен отрезок [A;B]: \t";
    cin >> N;
    if (N <= 0) {
        cout << "\nОШИБКА! N должно быть больше 0! ";
        return 1;
    }

    // Подготовка таблицы
    setlocale(LC_ALL, "C");
    if (!debug) HeadTable();

    h = (B - A) / N; //Рассчет величины шага

    for (i = 0; i <= N; i++) {
        x = A + i * h;
        PrintTable(x, i, N, debug);
    }
    return 0;
}



