/***************************************************************\
*       КАФЕДРА № 304 1 КУРС  CPP  ЛАБОРАТОРНАЯ РАБОТА			*
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application						*
* Project Name  : lr3											*
* File Name     : lr3.cpp										*
* Language      : C/C++                                         *
* Programmer(s) : Багиров Э., Нуриев Н.                         *
* Modifyed By   :                                               *
* Created       : 11/28/21                                      *
* Last Revision : 1_/__/21                                      *
* Comment(s)    : Код к ЛР№3 - "Одномерные массивы"				*
*																*
\***************************************************************/

#include <iostream>
#include <fstream>

using namespace std;



void PrintArray(int array[], int length) {
	for (int i = 0; i < length; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");	// подключение русского языка
	system("color F0");				// приведение цвта консоли к каноничному

	/* ОБЪЯВЛЕНИЕ ПЕРЕМЕННЫХ */

	const int normal_length = 7;	// нормальная длина массива

	int N;							// первое входное число
	int M;							// второе входное число
	int VEC[normal_length];			// входной массив
	int NEWVEC[normal_length];		// создаваемый массив
	int neg;						// сумма отрицательных элементов VEC среди первых n
	int entireSum;					// полная сумма элементов массива NEWVEC
	int positiveSum;				// сумма отрицательных элементов NEWVEC среди первых n
	int negativeSum;				// сумма положительных элементов NEWVEC среди поледних m
	int minPosElementPosition;		// расположение наименьшего положительного элемента
	int minPosElementValue;			// значение наименьшего положительного элемента

	/* КОНЕЦ ОБЪЯВЛЕНИЕ ПЕРЕМЕННЫХ */


	/* ЧТЕНИЕ ФАЙЛА И ПРОВЕРКА ДАННЫХ */

	ifstream fl;					// создание объекта класса ifstream
	fl.open("lr3.txt");				// связывание объекта с файлом

	fl >> N;						// сохраниение первого входного числа в N

	// проверка на наличие данных в файле
	if (fl.eof()) {
		cout << "Ошибка: файл пуст.\n";
		return 1;
	}
	if (fl.fail()) //в файле не число
	{
		cout << "Ошибка: сбой при чтении файла.\n" << endl;
		fl.close();    //закрыть файл
		return 3;       //выход по ошибке
	}
	// проверка N
	if (N < 0 || N > 7) {
		cout << "Ошибка: значение N вне границ.\n";
		return 2;
	}

	fl >> M;						// сохраниение второго входного числа в M

	// проверка M
	if (M < 0 || M>7) {
		cout << "Ошибка: значение M вне границ.\n";
		return 2;
	}

	// взаимная проверка N, M
	if (N > M) {
		cout << "Ошибка: N должно быть не больше M.\n";
		return 3;
	}

	int length = 0;					// для подсчета количества элементов в массиве

	// считывание данных в массив VEC и сохранение его длины в length
	while (!fl.eof()) {
		fl >> VEC[length];
		length++;
	}

	if (length != normal_length) {
		cout << "Ошибка: длина массива должна быть равна 7.\n";
		return 4;
	}

	fl.close();						// отпуск файла

	PrintArray(VEC, length);		// эхо-печать входного массива

	/* КОНЕЦ ЧТЕНИЕ ФАЙЛА И ПРОВЕРКА ДАННЫХ */


	/* ФОРМИРОВАНИЕ МАССИВА NEWVEC */

	neg = 0;

	// нахождение суммы отрицательных элементов среди первых N
	for (int i = 0; i < N; i++) {
		if (VEC[i] < 0) {
			neg += VEC[i];
		}
	}

	// нахождение элементов массива NEWVEC
	for (int i = 0; i < normal_length; i++) {
		NEWVEC[i] = VEC[i] + neg;
	}

	/* КОНЕЦ ФОРМИРОВАНИЕ МАССИВА NEWVEC */


	/* ПОИСК СУММ */

	entireSum = 0;
	positiveSum = 0;
	negativeSum = 0;

	for (int i = 0; i < normal_length; i++) {

		entireSum += NEWVEC[i];		// прибавление любого элемента к полной сумме

		// проверка элемента на позицию и значение
		if (i < N && NEWVEC[i] > 0) {
			positiveSum += NEWVEC[i];
		}

		// проверка элемента на позицию и значение
		if (i >= normal_length - M && NEWVEC[i] < 0) {
			negativeSum += NEWVEC[i];
		}
	}

	/* КОНЕЦ ПОИСКА СУММ */


	/* ПЕЧАТЬ NEWVEC И СУММ*/

	PrintArray(NEWVEC, normal_length);
	cout << "entireSum: " << entireSum << "\n";
	cout << "positiveSum: " << positiveSum << "\n";
	cout << "negativeSum: " << negativeSum << "\n";

	/* КОНЕЦ ПЕЧАТЬ NEWVEC И СУММ*/


	/* ПОИСК НАИМЕНЬШЕГО ПОЛОЖИТЕЛЬНОГО */

	minPosElementPosition = -1;
	minPosElementValue = 0;

	for (int i = N;  i < M; i++) {
		if (NEWVEC[i] > 0) {
			if (NEWVEC[i] < minPosElementValue || minPosElementValue == 0) {
				minPosElementValue = NEWVEC[i];
				minPosElementPosition = i;
			}
		}
	}
	cout << "Наименьший положительный элемент в интервале [" << N << ";" << M << "):\n";
	if (minPosElementPosition != -1) {
		cout << "индекс - " << minPosElementPosition << "\nзначение - " << minPosElementValue << "\n";
	}
	else {
		cout << "В заданном интервале нет положительных элементов";
	}

	/* КОНЕЦ ПОИСК НАИМЕНЬШЕГО ПОЛОЖИТЕЛЬНОГО */

	return 0;
}

