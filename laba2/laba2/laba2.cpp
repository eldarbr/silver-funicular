#include <iostream>
#include <cmath>
#include "laba2.h"

using namespace std;

double F(double x) {
    return pow(x - 1, 3);
}

double G(double x) {
    return pow(x + 5, 3) / (1 + pow(sin(x), 2));
}

int main()
{
    setlocale(LC_ALL, "Russian");

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

    h = (B - A) / N; //Рассчет величины шага

    for (i = 0; i <= N; i++) {
        x = A + i * h;
        cout << x << "\t" << F(x) << "\t" << G(x) << endl;
    }

    return 0;
}



