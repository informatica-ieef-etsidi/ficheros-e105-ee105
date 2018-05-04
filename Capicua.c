#include <stdio.h>

#define TAM 10

void pedirVector(int vector[], int dim);
int EsCapicua(int vector[], int dim);
int pedirN();
void EscribirVector(FILE * fichero,int vector[], int dim);

void main() {
	
	FILE * fichero;
	errno_t error;

	int vector[TAM], n = 0, i;
	char decision;

	error = fopen_s(&fichero, "vectores.txt", "w");  

	do {
		n = pedirN(n);

		pedirVector(vector, n);


		if (EsCapicua(vector, n)) {
			printf("Es capic%ca\n",163);
			EscribirVector(fichero,vector, n);
		}
		else
			printf("No es capic%ca\n",163);

	printf("%cQuieres escribir un nuevo vector? (s/n)",168);
	scanf_s("%c", &decision);

	} while (decision != 'n');
	
	fclose(fichero);

	system("pause");
}


void pedirVector(int vector[], int dim) {
	int i;
	for (i = 0; i < dim; i++) {
		printf("Introduce v[%d]  ", i + 1);
		scanf_s("%d", &vector[i]);
		getchar();
	}
}

int EsCapicua(int vector[], int dim) {

	int i, cont = 0;

	for (i = 0; i < dim / 2; i++) {
		if (vector[i] == vector[dim - 1 - i])
			cont++;
	}

	if (cont == dim / 2)
		return 1;

	return 0;
}
int pedirN() {
	int n;
	do {
		printf("Introduce un numero de elementos\n");
		scanf_s("%d", &n);
	} while (n <= 0);


	return n;
}
void EscribirVector(FILE * fichero ,int vector[], int dim) {
	
	int i;

	for (i = 0; i < dim; i++) {
		fprintf(fichero, "%d", vector[i]);
	}
	fprintf(fichero,"\n");
}