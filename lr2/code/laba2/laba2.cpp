/****************************************************************\
*       КАФЕДРА № 304 1 КУРС  CPP  ЛАБОРАТОРНАЯ РАБОТА           *
*----------------------------------------------------------------*
* Project Type  : Win32 Console Application                      *
* Project Name  : laba2                                          *
* File Name     : laba2.cpp                                      *
* Language      : C/C++                                          *
* Programmer(s) : Багиров Э., Нуриев Н.                          *
* Modifyed By   :                                                *
* Created       : 11/10/21                                       *
* Last Revision : 11/24/21                                       *
* Comment(s)    : Код к ЛР№2 - "Табулирование функций"           *
\****************************************************************/


#include <iostream>
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
void BetweenTheRaws() {
    cout << "\t"
        << char(195) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(180) << endl;
}

// имплемантация возведения числа в степень
double power(double a, int n) {
    double b = a;
    for (int i = 1; i < n; i++) {
        b *= a;
    }
    return b;
}

// расчет значения функции F(x) в точке x
double F(double x) {
    return power(x - 1, 3);
}

// расчет значения функции G(x) в точке x
double G(double x) {
    return power(x + 5, 3) / (1 + power(sin(x), 2));
}

// вывод строк таблицы с автоматическим закрытием таблицы
void PrintTable(int n, double x, double f, double g, bool last) {
    cout << "\t" << char(179) << setw(19) << setfill(char(255)) << n
        << char(179) << setw(19) << setprecision(4) << x
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(4) << f
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(4) << g
        << setfill(char(255)) << char(179) << endl;
    if (last) {
        BottomTable();
    }
    else {
        BetweenTheRaws();
    }
}


int main()
{
    setlocale(LC_ALL, "Russian"); // подключение русского языка
    system("color F0");


    //Инициализация переменных
    double A;   // начало отрезка
    double B;   // конец отрезка
    int N;      // количество интервалов, на которое делится отрезок [A;B]
    double h;   // шаг
    double x;   // аргумент приращения
    int i;      // индекс приращения

    // Ввод и проверка данных
    cout << "Введите А - координату начала отрезка [A;B]: \t";
    cin >> A;
    cout << "Введите B - координату конца отрезка [A;B]: \t";
    cin >> B;

    if (A > B) {
        cout << "\nОШИБКА! А должен быть меньше или равен В!";
        return 1;           // выход из программы возвращением кода 1
    }
    if (A != B) {
        cout << "Введите N - количество разделений отрезка [A;B]: \t";
        cin >> N;
        if (N <= 0) {
            cout << "\nОШИБКА! N должно быть больше 0! ";
            return 2;       // выход из программы возвращением кода 2
        }
        h = (B - A) / N;    // Расчет величины шага
    }
    else {
        // Если входной отрезок есть точка, изменить количество разделений
        N = 0;
        h = 0;
    }
    
    cout << "Величина шага h = " << h << "\n";

    // Подготовка таблицы
    setlocale(LC_ALL, "C");     // отключение русского языка
    HeadTable();                // вывод заголовка таблицы

    for (i = 0; i <= N; i++) {  // посторная печать таблицы в цикле
        x = A + i * h;          // вычисление инкремируемой переменной
        double Fx = F(x);       // расчет значения функции F(x) в точке x
        double Gx = G(x);       // расчет значения функции G(x) в точке x
        bool last = i == N;     // флаг последней итерации цикла

        // функции-принтеру передаются значения:
        // i - индекс итерации
        // x - аргумент приращения
        // Fx - значение функции F(x) в точке x
        // Gx - значение функции G(x) в точке x
        // last - флаг последней итерации цикла
        PrintTable(i, x, Fx, Gx, last);
    }

    return 0;                   // выход из программы возвращением кода 0
}
