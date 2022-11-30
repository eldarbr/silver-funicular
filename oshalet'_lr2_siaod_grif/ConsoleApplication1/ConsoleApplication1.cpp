#include <iostream>
#include <fstream>
#define INF INT_MAX

using namespace std;

const string filename = "graph.txt";

void PrintMatrix(int** matrix, int number_of_vertex) {
	for (int i = 0; i < number_of_vertex; i++) {
		for (int j = 0; j < number_of_vertex; j++)
			cout << matrix[i][j] << "\t";
		cout << "\n";
	}
}

void FloydWarshellAlgorithm(int**matrix, int number_of_vertex){
	for (int k = 0; k < number_of_vertex; k++) {
		for (int i = 0; i < number_of_vertex; i++)
			for (int j = 0; j < number_of_vertex; j++) {
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		PrintMatrix(matrix, number_of_vertex);
		cout << endl;
		//system("pause");
	}
};

int main()
{
	ifstream input_graph;
	input_graph.open(filename);
	if (input_graph.fail()) {
		cout << "Ошибка открытия файла!";
		exit(-1);
	}
	int number_of_vertex;
	input_graph >> number_of_vertex;
	int** matrix = new int* [number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		matrix[i] = new int[number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++)
			input_graph >> matrix[i][j];
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++)
			if (matrix[i][j] == 0) matrix[i][j] = 101;
	FloydWarshellAlgorithm(matrix, number_of_vertex);
}