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
	bool interrupted = false;		// флаг, указывающий на выход из цикла до достижения необходимой точности

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
		Sum += 1.0 / N / (N + 1);		// подсчет нового слагаемого, прибавление его к сумме
		if (prevDelta + Sum - 1 == 0) { 
			interrupted = true;			// Если точность не увеличилась за последнюю итерацию,
			break;						// достигнут предел точности, необходимо завершить цикл
		}								
		prevDelta = 1 - Sum;			// сохранение новой моментальной точности
	} while (prevDelta > Eps);

	// Вывод результатов
	cout.precision(60);
	if (interrupted) {
		cout << fixed << "Достигнуто ограничение по точности подсчета\nРазность достигнутой точности Delta и Eps = " << 1 - Sum - Eps << endl << endl;
	}
	cout << "Cумма получена\nКоличество просумированных элементов N = " << N << endl;
	cout << "Сумма Sum = " << Sum << endl;
	cout << fixed << "Достигнутая точность Delta = " << (1 - Sum) << endl;

	return 1;
}
