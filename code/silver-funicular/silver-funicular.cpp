#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");

	// Инициализация переменных
	long double Eps;				// заданная пользователем точность подсчета Эпсилон
	double Sum = 0;					// сумма
	unsigned long long N = 0;		// индекс суммы
	double prevDelta = 1;			// моментальная точность предыдущей итерации
	const float e_sum = 0.78;			// точная сумма

	// Входной контроль
	cout << "Введите Eps: ";
	cin >> Eps;
	cout << "\n";
	if (Eps <= 0) {
		// Предотвращение некорректного ввода точности подсчета
		cout << "ОШИБКА - Eps должен быть больше 0." << endl;
		return 0;
	}
	
	// Расчет суммы
	do {
		N++;							// инкремент индекса
		Sum += 1.0 / N / (N + 1);	// подсчет нового слагаемого, прибавление его к сумме
		cout << "Cумма получена\nКоличество просумированных элементов N = " << N << endl;
		cout << "Сумма Sum = " << Sum << endl;
		cout << "Достигнутая точность Delta = " << (e_sum - Sum) << endl;
		if (prevDelta + abs(Sum - e_sum) == 0) {
			// Если точность не увеличилась за последнюю итерацию,
			// достигнут предел точности, необходимо завершить цикл
			cout << "ОШИБКА - Достигнуто ограничение по точности подсчета.\n";
			return 0;
			
		}								
		prevDelta = abs(e_sum - Sum);			// сохранение новой моментальной точности
	} while (prevDelta > Eps);

	// Вывод результатов
	//cout.precision(60);
	cout << "Cумма получена\nКоличество просумированных элементов N = " << N << endl;
	cout << "Сумма Sum = " << Sum << endl;
	cout << "Достигнутая точность Delta = " << (e_sum - Sum) << endl;

	return 1;
}
