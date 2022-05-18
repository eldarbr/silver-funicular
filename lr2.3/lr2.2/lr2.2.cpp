#include <iostream>
#include <iomanip>
#include <fstream>
#include <regex>

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


// вывод строк таблицы с закрытием таблицы
void PrintTable(int n, char m[], char k[], int kol, double gruz, bool last) {
    cout << "\t"
        << char(179) << setw(19) << setfill(char(255)) << n
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(0) << m
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(4) << k
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(4) << kol
        << setfill(char(255))
        << char(179) << setw(19) << setprecision(1) << gruz
        << setfill(char(255)) << char(179) << endl;
    if (last) {
        BottomTable();
    }
    else {
        BetweenTheRaws();
    }
}


// ФУНКЦИЯ ДЛЯ ВЫВОДОВ ОШИБКИ ПО КОДАМ
void Errors(int x) {
    setlocale(LC_ALL, "rus");
    switch (x) {
    case 1:
        cout << "Ошибка! Файл не найден!" << endl;
        exit(1);
    
    case 2:
        cout << "Ошибка! Неверная марка ЛА" << endl << endl;
        exit(2);

    case 3:
        cout << "Ошибка! Неверный бортовой номер" << endl << endl;
        exit(3);

    case 4:
        cout << "Ошибка! Неверное количество пассажиров" << endl << endl;
        exit(4);

    case 5:
        cout << "Ошибка! Неверное количество груза" << endl << endl;
        exit(5);
    }
}


// структура
struct aero {
    char m[8];
    char n[6];
    int kol;
    double gruz;
};


// проверка марки ЛА
bool valid_aircrafttype(char candidate[]) {
    regex r ("\\w{2}-\\d{3}\\w");
    return regex_match(candidate, r);
}


// проверка бортового номера
bool valid_aircraftnum(char candidate[]) {
    regex r("\\w-\\d+");
    return regex_match(candidate, r);
}


// проверка количества пассажиров
bool valid_passangernum(int candidate) {
    if (candidate >= 0) return true;
    else return false;
}


// проверка количества груза
bool valid_cargonum(double candidate) {
    if (candidate >= 0) return true;
    else return false;
}


// чтение структуры из файла
void str_from_file(const string file, aero* mas) {
    ifstream fil;
    fil.open(file);
    int M = 0;
    fil >> M;
    for (int i = 0; i < M; i++) {
        fil >> mas[i].m;
        if (!valid_aircrafttype(mas[i].m)) {
            cout << endl << mas[i].m << endl;
            Errors(2);
        }
        fil >> mas[i].n;
        if (!valid_aircraftnum(mas[i].n)) {
            cout << endl << mas[i].n << endl;
            Errors(3);
        }
        fil >> mas[i].kol;
        if (!valid_passangernum(mas[i].kol)) {
            cout << endl << mas[i].kol << endl;
            Errors(4);
        }
        fil >> mas[i].gruz;
        if (!valid_cargonum(mas[i].gruz)) {
            cout << endl << mas[i].gruz << endl;
            Errors(5);
        }
    }
}


// считывание бортовой номер
int num_from_struct(aero mas) {
    int number = atoi(&mas.n[2]);
    return number;
}


// сортировка структуры пузырьком по индексам
void sort_the_struct(aero* mas, int M, int *rar) {
    int Temp;
    for (int i = 0; i < M - 1; i++) {
        for (int j = M - 1; j > i; j--) {
            if (num_from_struct(mas[rar[j]]) < num_from_struct(mas[rar[j-1]])) {
                Temp = rar[j];
                rar[j] = rar[j - 1];
                rar[j - 1] = Temp;
            }
        }
    }
}


const string filename = "file.txt";

int main()
{
    int pas = 0;            // количество пассажиров
    double allgruz = 0;     // масса груза

    HeadTable();            // печать оглавления таблицы

    ifstream fn;            // создание переменной класса ifstream
    fn.open(filename);      // открытие файла
    if (!fn.is_open())      // ошибка не найденного файла
        Errors(1);

    int N;                  // количество строк данных в файле
    fn >> N;                // чтение количества строк данных в файле
    int* rar = new int[N];  // массив индексов для сортировки по индексам 
    for (int i = 0; i < N; i++)
        rar[i] = i;         // заполенение массива индексов
    aero* arr = new aero[N];
    str_from_file(filename, arr);
    bool last = 0;          // флаг конца таблицы
    sort_the_struct(arr, N, rar);   // сортировка структуры по индексам

    for (int i = 0; i < N; i++) {   // подсчет суммы и вывод таблицы
        int k;
        k = rar[i];
        pas += arr[k].kol;
        allgruz += arr[k].gruz;
        PrintTable(i + 1, arr[k].m, arr[k].n, arr[k].kol, arr[k].gruz, last);
        if (i == N - 2)
            last = 1;        
    }

    setlocale(LC_ALL, "rus");
    cout << "\n\tСуммарное количество пассажиров: " << pas << "\n\tСуммарный вес груза: " << setprecision(1) << allgruz << "\n\n";
    system("pause");
}
