// PRG2_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h> // Pouzivani bool v C
#include <stdlib.h>
#include <malloc.h>

#define ARRAY_SIZE 100

typedef struct Matrix{
	int rows;  // matice (m,n) == (rows, cols)
	int cols;
	float **data;
	char name;
} Matrix;

void printMenu() {
	printf("1. Vytvorit matici\n");
	printf("2. Vynasobit matici cislem\n");
	printf("3. Secist/odecist matice\n");
	printf("4. Vynasobit matice\n");
	printf("5. Je diagonalni?\n");
	printf("6. Vytisknout matici\n");
	printf("7. Ulozit matici do souboru\n");
	printf("8. Nacist matice ze souboru\n");
	printf("9. Vytvorit kopii matice\n");
	printf("10. KONEC\n");
}

Matrix *initMatrix(int rows, int cols) {
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	m->rows = rows;
	m->cols = cols;
	m->data = (float **)malloc(rows*sizeof(float));
	for (int i = 0; i < rows; i++)
		m->data[i] = (float *)malloc(cols*sizeof(float));

	return m;
}

void fillMatrix(Matrix *matrix) {
	printf("Oznaceni matice (1 znak): ");
	scanf_s("%c", &matrix->name);
	fflush(stdin);
	printf("Zadejte hodnoty (po radcich, oddelene mezerou):\n");
	for (int i = 0; i < matrix->rows; i++) {
		for (int j = 0; j < matrix->cols; j++)
			scanf_s("%f", &matrix->data[i][j]);
		fflush(stdin);
	}
}

void multiplyByNum(Matrix *matrix, float multiplier) {
	for (int i = 0; i < matrix->rows; i++)
		for (int j = 0; i < matrix->cols; j++)
			matrix->data[i][j] * multiplier;
}

Matrix* addMatrix(Matrix matrix1, Matrix matrix2) {
	Matrix *m;

	if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
		printf("Matice musi mit stejne rozmery!");
		return;
	}
	else {
		m->name = 'S';
		m = initMatrix(matrix1.rows, matrix1.cols);
		for (int i = 0; i < matrix1.rows; i++)
			for (int j = 0; i < matrix1.cols; j++)
				m->data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
	}
	return m;
}

Matrix* multiplyMatrix(Matrix matrix1, Matrix matrix2) {
	Matrix *m;

	if (matrix1.cols != matrix2.rows) {
		printf("Zvolene matice nelze vynasobit!");
		return;
	}
	else {
		m->name = 'M';
		m = initMatrix(matrix1.rows, matrix2.cols);
		for (int i = 0; i < m->rows; i++)
			for (int j = 0; i < m->cols; j++) {
				m->data[i][j] = 0;
				for (int k = 0; k < matrix1.cols; j++)
					m->data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
			}
	}
	return m;
}

//bool isDiagonal(Matrix matrix) {
//
//}
//
//void printMatrix(Matrix matrix) {
//
//}
//
//void saveTofile(Matrix matrix, char *filename) {
//
//}
//
//Matrix loadFromFile(char *filename) {
//
//}
//
//Matrix copyMatrix(Matrix src) {
//
//}

int _tmain(int argc, _TCHAR* argv[])
{
	Matrix *matrix[ARRAY_SIZE];

	matrix[0] = createMatrix(2, 2);

	printf("%f ", matrix[0]->data[0][0]);
	printf("%f\n", matrix[0]->data[0][1]);
	printf("%f ", matrix[0]->data[1][0]);
	printf("%f", matrix[0]->data[1][1]);

	return 0;
}

