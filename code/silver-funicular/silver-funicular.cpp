#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	//Входной контроль
	long double Eps;
	cout << "Введите Eps: ";
	cin >> Eps;
	if (Eps <= 0) {
		cout << "ОШИБКА! Eps должен быть больше 0!";
		return 0;
	}
	//Инициализация переменных
	double Sum = 0;
	unsigned long N = 1;
	//Рассчет суммы
	do {
		// cout << Sum << " " << N << "\n";
		Sum += (long double)(1.0 / (unsigned long)((N * (unsigned long)(N + 1))));
		N++;
		if (Sum > 1) {
			cout.precision(10005);
			cout << "warn sum > 1! " << Sum << " " << N << "\n";
		}
	} while ((1 - Sum) > Eps);
	//Вывод результатов
	cout << "Количество просумированных элементов N = " << N << endl;
	cout << "Сумма Sum = " << Sum << endl;
	cout << "Разность суммы и точного значения (1 - Sum) = " << (1 - Sum) << endl;
	return 1;
}
