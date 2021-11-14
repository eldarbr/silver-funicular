#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void HeadTable() {
    cout << "\t"
        << char(218) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(191) << endl;
    cout << "\t"
        << char(179) << setw(19) << "#" << setfill(' ')
        << char(179) << setw(19) << "x" << setfill(' ')
        << char(179) << setw(19) << "F(x)" << setfill(' ')
        << char(179) << setw(19) << "G(x)" << setfill(' ')
        << char(179) << endl;
    cout << "\t"
        << char(195) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setw(20)
        << char(197) << setw(20) << char(180) << endl;
    cout.setf(ios::showpoint | ios::fixed);

}

void BottomTable() {
    cout << "\t"
        << char(192) << setfill(char(196)) << setw(20)
        << char(193) << setfill(char(196)) << setw(20)
        << char(193) << setfill(char(196)) << setw(20)
        << char(193) << setfill(char(196)) << setw(20)
        << char(217) << endl;
}

void  BetweenTheRaw() {
    cout << "\t"
        << char(195) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
        << char(180) << endl;
}

double F(double x) {
    return pow(x - 1, 3);
}

double G(double x) {
    return pow(x + 5, 3) / (1 + pow(sin(x), 2));
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

    //Ввод входных данных
    cout << "Введите А - координату начала отрезка [A;B]: \t";
    cin >> A;
    cout << "Введите B - координату конца отрезка [A;B]: \t";
    cin >> B;
    cout << "Введите N - количество интервалов, на которые разделен отрезок [A;B]: \t";
    cin >> N;
    setlocale(LC_ALL, "C");
    h = (B - A) / N; //Рассчет величины шага
    HeadTable();
    for (i = 0; i <= N; i++) {
        x = A + i * h;
        //cout << x << "\t" << F(x) << "\t" << G(x) << endl;
        
        cout << "\t" << char(179) << setw(19) << setfill(char(255)) << i
            << char(179) << setw(19) << setprecision(4) << x
            << setfill(char(255))
            << char(179) << setw(19) << setprecision(4) << F(x)
            << setfill(char(255))
            << char(179) << setw(19) << setprecision(4) << G(x)
            << setfill(char(255)) << char(179) << endl;
        if (i!=N)
            BetweenTheRaw();
    }
    BottomTable();
    return 0;
}



