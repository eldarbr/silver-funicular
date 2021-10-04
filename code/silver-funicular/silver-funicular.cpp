#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	//Входной контроль
	float Eps;
	cout << "Введите Eps: ";
	cin >> Eps;
	if (Eps <= 0) {
		cout << "ОШИБКА! Eps должен быть больше 0!";
		return 0;
	}
	//Инициализация переменных
	double Sum = 0;
	int N = 1;
	//Рассчет суммы
	do {
		Sum += 1.0 / (N * (++N));
	} while ((1 - Sum) > Eps);
	//Вывод результатов
	cout << "Количество просумированных элементов N = " << N << endl;
	cout << "Сумма Sum = " << Sum << endl;
	cout << "Разность суммы и точного значения (1 - Sum) = " << (1 - Sum) << endl;
	return 1;
}
