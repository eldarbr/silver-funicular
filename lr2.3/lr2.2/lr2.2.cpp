#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


// псевдографика - заголовок таблицы
void HeadTable() {
    cout << "\t"
        << char(218) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(194) << setfill(char(196)) << setw(20)
        << char(191) << endl;
    cout << "\t"
        << char(179) << setfill(' ') << setw(19) << "#"
        << char(179) << setfill(' ') << setw(19) << "marka LA"
        << char(179) << setfill(' ') << setw(19) << "bort number"
        << char(179) << setfill(' ') << setw(19) << "pas"
        << char(179) << setfill(' ') << setw(19) << "massa"
        << char(179) << endl;
    cout << "\t"
        << char(195) << setfill(char(196)) << setw(20)
        << char(197) << setfill(char(196)) << setw(20)
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
        << char(197) << setfill(char(196)) << setw(20)
        << char(180) << endl;
}

// вывод строк таблицы с автоматическим закрытием таблицы
void PrintTable(int n, char m[], char k[], int kol, double gruz, bool last) {
    cout << "\t" << char(179) << setw(19) << setfill(char(255)) << n
        << char(179) << setw(19) << setprecision(4) << m
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(4) << k
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(4) << kol
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(4) << gruz
        << setfill(char(255)) << char(179) << endl;
    if (last) {
        BottomTable();
    }
    else {
        BetweenTheRaws();
    }
}

// структура
struct aero {
    char m[7];
    char n[6];
    int kol;
    double gruz;
};

// чтение структуры из файла
void str_from_file(const string file, aero* mas) {
    ifstream fil;
    fil.open(file);
    int M = 0;
    fil >> M;
    for (int i = 0; i < M; i++) {
        fil >> mas[i].m;
        fil >> mas[i].n;
        fil >> mas[i].kol;
        fil >> mas[i].gruz;
    }
}

// бортовой номер
int num_from_struct(aero mas) {
    int number = atoi(&mas.n[2]);
    return number;
}

// сортировка структуры пузырьком
void sort_the_struct(aero* mas, int M) {
    aero Temp;
    int exch;
    for (int i = 0; i < M-1; i++) {
        for (int j = M-1; j > i; j--){
            if (num_from_struct(mas[j]) < num_from_struct(mas[j - 1])) {
                Temp = mas[j];
                mas[j] = mas[j - 1];
                mas[j - 1] = Temp;
            }
        }
    }
}

const string filename = "file.txt";

int main()
{
    int pas = 0;
    double allgruz = 0;
    HeadTable();
    ifstream fn;
    fn.open(filename);
    int N;
    fn >> N;
    aero* arr = new aero[N];
    str_from_file(filename, arr);
    bool last = 0;
    sort_the_struct(arr, N);
    for (int i = 0; i < N; i++) {
        pas += arr[i].kol;
        allgruz += arr[i].gruz;
        PrintTable(i + 1, arr[i].m, arr[i].n, arr[i].kol, arr[i].gruz, last);
        if (i == N - 2)
            last = 1;
    }
}
