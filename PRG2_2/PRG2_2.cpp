// PRG2_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h> // Pouzivani bool v C
#include <string>
#include <iostream>

typedef struct {
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

void multiplyByNum(Matrix *matrix) {

}

Matrix addMatrix(Matrix matrix1, Matrix matrix2) {

}

Matrix multiplyMatrix(Matrix matrix1, Matrix matrix2) {

}

bool isDiagonal(Matrix matrix) {

}

void printMatrix(Matrix matrix) {

}

void saveTofile(Matrix matrix, char *filename) {

}

Matrix loadFromFile(char *filename) {

}

Matrix copyMatrix(Matrix src) {

}

int _tmain(int argc, _TCHAR* argv[])
{


	return 0;
}

