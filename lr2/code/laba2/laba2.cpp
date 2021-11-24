/*******************************************************\
*   C++ наш, сущий в памяти!                            *
*   да компилируется код Твой;                          *
*   да приидет царствие Софта Твоего;                   *
*   да будут действительны указатели Твои               *
*   и в ОЗУ, как на жестком диске;                      *
*   массив наш насущный подавай нам на каждый день;     *
*   и прости нам варнинги наши,                         *
*   как и мы избавляемся от ошибок наших;               *
*   и не введи нас в бесконечный цикл,                  *
*   но избавь нас от винды.                             *
*   Ибо Твое есть Царство и сила и слава во веки.       *
*   Энтер.                                              *
\*******************************************************/


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
    setlocale(LC_ALL, "Russian"); // подключение русского языка
    system("color F0");

    cout << power(sin(4), 2) << "\n";

    //Инициализация переменных
    double A;   // начало отрезка
    double B;   // конец отрезка
    int N;      // количество интервалов, на которое делится отрезок [A;B]
    double h;   // шаг
    double x;   // приращение
    int i;      // индекс приращения
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
    if (A != B) {
        cout << "Введите N - количество разделений отрезка [A;B]: \t";
        cin >> N;
        if (N <= 0) {
            cout << "\nОШИБКА! N должно быть больше 0! ";
            return 1;
        }
        h = (B - A) / N; // Расчет величины шага
    }
    else {
        // Если входной отрезок есть точка, изменить количество разделений
        N = 0;
        h = 0;
    }
    
    // Подготовка таблицы
    setlocale(LC_ALL, "C"); // отключение русского языка
    if (!debug) HeadTable();

    for (i = 0; i <= N; i++) { //посторная печать таблицы в цикле
        x = A + i * h;
        PrintTable(x, i, N, debug);
    }

    return 0;
}
