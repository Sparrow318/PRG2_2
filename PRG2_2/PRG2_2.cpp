// PRG2_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h> // Pouzivani bool v C
#include <stdlib.h>

#define ARRAY_SIZE 100

typedef struct Matrix{
	int rows;  // matice (m,n) == (rows, cols)
	int cols;
	float **data;
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
	printf("Zadejte hodnoty (po radcich, oddelene mezerou):\n");
	for (int i = 0; i < matrix->rows; i++) {
		for (int j = 0; j < matrix->cols; j++)
			scanf_s("%f", &matrix->data[i][j]);
		fflush(stdin);
	}
}

void multiplyByNum(Matrix *matrix, float multiplier) {
	for (int i = 0; i < matrix->rows; i++)
		for (int j = 0; j < matrix->cols; j++)
			matrix->data[i][j] *= multiplier;
}

Matrix* addMatrix(Matrix matrix1, Matrix matrix2) {
	Matrix *m;

	if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
		printf("Matice musi mit stejne rozmery!");
		return NULL;
	}
	else {
		m = initMatrix(matrix1.rows, matrix1.cols);
		for (int i = 0; i < matrix1.rows; i++)
			for (int j = 0; j < matrix1.cols; j++)
				m->data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
	}
	return m;
}

Matrix* subtractMatrix(Matrix matrix1, Matrix matrix2) {
	Matrix *m;

	if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
		printf("Matice musi mit stejne rozmery!");
		return NULL;
	}
	else {
		m = initMatrix(matrix1.rows, matrix1.cols);
		for (int i = 0; i < matrix1.rows; i++)
		for (int j = 0; j < matrix1.cols; j++)
			m->data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
	}
	return m;
}

Matrix* multiplyMatrix(Matrix matrix1, Matrix matrix2) {
	Matrix *m;

	if (matrix1.cols != matrix2.rows) {
		printf("Zvolene matice nelze vynasobit!");
		return NULL;
	}
	else {
		m = initMatrix(matrix1.rows, matrix2.cols);
		for (int i = 0; i < m->rows; i++)
			for (int j = 0; j < m->cols; j++) {
				m->data[i][j] = 0;
				for (int k = 0; k < matrix1.cols; k++)
					m->data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
			}
	}
	return m;
}

bool isDiagonal(Matrix matrix) {
	if (matrix.cols != matrix.rows)
		return false;

	for (int i = 0; i < matrix.rows; i++)
		for (int j = 0; j < matrix.cols; j++) 
			if (i != j && matrix.data[i][j] != 0)
				return false;
			
	return true;
}

void printMatrix(Matrix matrix) {
	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.cols; j++)
			printf("%.2f ", matrix.data[i][j]);
		printf("\n");
	}
}

void saveTofile(Matrix matrix, char *filename) {
	FILE *file;
	errno_t err = fopen_s(&file, filename, "w");

	if (err) {
		printf("Nepodarilo se uloit matici.");
		return;
	}
	fprintf(file, "%d %d\n", matrix.rows, matrix.cols);
	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.cols; j++)
			fprintf(file, "%.2f ", matrix.data[i][j]);
		fprintf(file, "\n");
	}

	fclose(file);
	printf("Matice byla ulozena.");
}

Matrix* loadFromFile(char *filename) {
	FILE *file;
	errno_t err = fopen_s(&file, filename, "r");

	if (err) {
		printf("Nepodarilo se nacist matici.");
		return NULL;
	}
	
	int rows, cols;
	fscanf_s(file, "%d %d", &rows, &cols);
	Matrix *m;
	m = initMatrix(rows, cols);
	
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++)
			fscanf_s(file, "%f", &m->data[i][j]);
	}

	fclose(file);
	return m;
}

Matrix* copyMatrix(Matrix src) {
	Matrix *m;

	m = initMatrix(src.rows, src.cols);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			m->data[i][j] = src.data[i][j];

	return m;
}

void printAvailableMatrix(Matrix **matrix) {
	int i = 0;
	printf("Dostupne matice:\n");
	while (matrix[i] != NULL) {
		printf("%d. (%d, %d) ", i+1, matrix[i]->rows, matrix[i]->cols);
		i++;
	}
	printf("\n");
}

void freedomForMatrix(Matrix *matrix) {
	for (int i = 0; i < matrix->cols; i++)
		free(matrix->data[i]);
	free(matrix->data);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Matrix *matrix[ARRAY_SIZE];
	int matrixCounter = 0;
	int option, o, m1, m2;
	bool diagonal;
	char filename[20];

	for (int i = 0; i < ARRAY_SIZE; i++)
		matrix[i] = NULL;

	do {
		printMenu();
		scanf_s("%d", &option);
		system("cls");

		switch (option) {
		case 1:
			int rows, cols;
			printf("Zadejte pocet radku matice: ");
			scanf_s("%d", &rows);
			printf("Zadejte pocet sloupcu matice: ");
			scanf_s("%d", &cols);
			matrix[matrixCounter++] = initMatrix(rows, cols);
			fillMatrix(matrix[matrixCounter - 1]);
			break;
		case 2:
			float multiplier;
			printf("Vyberte matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &o);
			} while (o < 0 || o > matrixCounter);
			printf("nasobitel: ");
			scanf_s("%f", &multiplier);
			multiplyByNum(matrix[o - 1], multiplier);
			printf("Vysledna matice je:\n");
			printMatrix(*matrix[o - 1]);
			fflush(stdin);
			getchar();
			break;
		case 3: // scitani, odecitani
			printf("1. secist\n");
			printf("2. odecist\n");
			scanf_s("%d", &o);
			printf("Vyberte 1. matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &m1);
			} while (m1 < 0 || m1 > matrixCounter);

			printf("Vyberte 2. matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &m2);
			} while (m2 < 0 || m2 > matrixCounter);

			if (o == 1)
				matrix[matrixCounter] = addMatrix(*matrix[m1 - 1], *matrix[m2 - 1]);
			else
				matrix[matrixCounter] = subtractMatrix(*matrix[m1 - 1], *matrix[m2 - 1]);

			if (matrix[matrixCounter] != NULL) {
				printf("Vysledna matice je:\n");
				printMatrix(*matrix[matrixCounter]);
				matrixCounter++;
			}
			fflush(stdin);
			getchar();
			break;
		case 4: // nasobeni
			printf("Vyberte 1. matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &m1);
			} while (m1 < 0 || m1 > matrixCounter);

			printf("Vyberte 2. matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &m2);
			} while (m2 < 0 || m2 > matrixCounter);

			matrix[matrixCounter] = multiplyMatrix(*matrix[m1 - 1], *matrix[m2 - 1]);
			if (matrix[matrixCounter] != NULL) {
				printf("Vysledna matice je:\n");
				printMatrix(*matrix[matrixCounter]);
				matrixCounter++;
			}
			fflush(stdin);
			getchar();
			break;
		case 5: // diagonalni
			printf("Vyberte matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &o);
			} while (o < 0 || o > matrixCounter);

			diagonal = isDiagonal(*matrix[o - 1]);

			if (diagonal)
				printf("Matice je diagonalni.");
			else
				printf("Matice neni diagonalni.");

			fflush(stdin);
			getchar();
			break;
		case 6: // tisk
			printf("Vyberte matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &o);
			} while (o < 0 || o > matrixCounter);

			printMatrix(*matrix[o - 1]);
			fflush(stdin);
			getchar();
			break;
		case 7: // save
			printf("Vyberte matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &o);
			} while (o < 0 || o > matrixCounter);

			printf("Zadejte jmeno souboru: ");
			scanf_s("%s", &filename, 20);
			saveTofile(*matrix[o - 1], filename);

			fflush(stdin);
			getchar();
			break;
		case 8: // load
			printf("Zadejte jmeno souboru: ");
			scanf_s("%s", &filename, 20);

			matrix[matrixCounter] = loadFromFile(filename);
			if (matrix[matrixCounter] != NULL) {
				printf("Matice byla uspesne nactena.\n");
				printMatrix(*matrix[matrixCounter]);
				matrixCounter++;
			}

			fflush(stdin);
			getchar();
			break;
		case 9: // kopie
			printf("Vyberte matici\n");
			printAvailableMatrix(matrix);
			do {
				scanf_s("%d", &o);
			} while (o < 0 || o > matrixCounter);

			matrix[matrixCounter] = copyMatrix(*matrix[o - 1]);
			if (matrix[matrixCounter] != NULL) {
				printf("Kopie byla vytvorena:\n");
				printMatrix(*matrix[matrixCounter]);
				matrixCounter++;
			}
			fflush(stdin);
			getchar();
			break;
		default:
			break;
		}
		system("cls");
	} while (option != 10);

	for (int i = 0; i < matrixCounter; i++) {
		freedomForMatrix(matrix[i]);
		free(matrix[i]);
	}

	return 0;
}

