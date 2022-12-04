#include <iostream>
#include <fstream>

using namespace std;

const string filename1 = "graph.txt";
const string filename2 = "graph2.txt";

void PrintMatrix(int*** matrix, int number_of_vertex) {
	for (int i = 0; i < number_of_vertex; i++) {
		for (int j = 0; j < number_of_vertex; j++) {
			cout << (*matrix)[i][j] << "\t";
		}
		cout << "\n";
	}
}

int ConsoleInterfaceSwitch() {
	int n;
	cout << "Ввести граф из файла с матрицей смежности или из файла с конденсационной матрицей инцидентности?\n1. Из файла с матрицей смежности\n2. Из файла с конденсационной матрицей инцидентности\n> ";
	do {
		cin >> n;
		if (n > 2 || n < 1) cout << "Набран неверный номер! Введите еще раз\n> ";
	} while (n > 2 || n < 1);
	return n;
}

int** ReworkMatrixIntoUnoriented(int** matrix, int number_of_vertex) {
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = i; j < number_of_vertex; j++) {
			if (matrix[i][j] < matrix[j][i]) matrix[i][j] = matrix[j][i];
			else matrix[j][i] = matrix[i][j];
		}
	return matrix;
}

int** FillZero(int** matrix, int number_of_vertex) {
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++)
			matrix[i][j] = 0;
	return matrix;
}

void ReadGraphFromAdjacencyMatrix(int*** matrix, int number_of_vertex) {
	ifstream input_graph;
	input_graph.open(filename1);
	int trash;
	input_graph >> trash;		// в trash идет первое число из файла graph.txt
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++) {
			input_graph >> (*matrix)[i][j];
		}
}

void ReadGraphFromIncidenceMatrix(int*** matrix, int number_of_vertex) {
	(*matrix) = new int* [number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		(*matrix)[i] = new int[number_of_vertex];
	ifstream input_graph;
	input_graph.open(filename2);
	(*matrix) = FillZero(*matrix, number_of_vertex);
	int v1, v2, n;
	while (!input_graph.eof()) {
		input_graph >> v1 >> v2 >> n;
		(*matrix)[v1 - 1][v2 - 1] = n;
	}
}


void FloydWarshellAlgorithm(int**matrix, int number_of_vertex){
	for (int k = 0; k < number_of_vertex; k++) {
		for (int i = 0; i < number_of_vertex; i++)
			for (int j = 0; j < number_of_vertex; j++) {
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		PrintMatrix(&matrix, number_of_vertex);
		cout << endl;
		//system("pause");
	}
	cout << "Матрица после выполнения алгоритма Флойда-Уоршелла:\n\n";
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++) {
			if (i == j || matrix[i][j] == 999) matrix[i][j] = 0;
		}
	PrintMatrix(&matrix, number_of_vertex);
};

void PrimaAlgorithm(int **matrix, int number_of_vertex){
	ReworkMatrixIntoUnoriented(matrix, number_of_vertex);
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++)
			if (matrix[i][j] == 0) matrix[i][j] = 999;
	cout << "\nНеориентированная матрица:\n";
	PrintMatrix(&matrix, number_of_vertex);
	int* selected = new int[number_of_vertex]; // массив выбранных вершин
	for (int i = 0; i < number_of_vertex; i++)
		selected[i] = false;
	selected[0] = true;
	int number = 0;
	int x, y;

	cout << "\nРебро:Вес ребра\n";
	while (number < number_of_vertex - 1) {
		int min = 1000;
		x = 0;
		y = 0;
		for(int  i = 0;i <number_of_vertex;i++)
			if(selected[i])
				for (int j = 0;j < number_of_vertex;j++)
					if(!selected[j] && matrix[i][j])
						if (min > matrix[i][j]) {
							min = matrix[i][j];
							x = i;
							y = j;
						}
		cout << "(" << x << "," << y << "):" << matrix[x][y] << "\n";
		selected[y] = true;
		number++;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int number_of_vertex;
	ifstream input_graph;
	input_graph.open(filename1);
	if (input_graph.fail()) {
		cout << "Ошибка открытия файла!";
		exit(-1);
	}
	input_graph >> number_of_vertex;
	int** matrix = new int* [number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		matrix[i] = new int[number_of_vertex];
	int n = ConsoleInterfaceSwitch();
	switch (n) {
	case 1:
		ReadGraphFromAdjacencyMatrix(&matrix, number_of_vertex);
		cout << "Считанная матрица:\n";
		PrintMatrix(&matrix, number_of_vertex);
		system("pause");

		break;
	case 2:
		ReadGraphFromIncidenceMatrix(&matrix, number_of_vertex);
		cout << "Считанная матрица:\n";
		PrintMatrix(&matrix, number_of_vertex);
		system("pause");

		break;
	default:
		break;
	}
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++)
			if (matrix[i][j] == 0) matrix[i][j] = 999;
	FloydWarshellAlgorithm(matrix, number_of_vertex);
	cout << "\n";
	system("pause");
	int** matrix2 = NULL;
	ReadGraphFromIncidenceMatrix(&matrix2, number_of_vertex);
	cout << "Матрица для алгоритма Прима:\n";
	PrintMatrix(&matrix2, number_of_vertex);
	PrimaAlgorithm(matrix2, number_of_vertex);
}