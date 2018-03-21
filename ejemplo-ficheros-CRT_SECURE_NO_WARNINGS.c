#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 

// FILE * fopen (char nombre[], char modo[]);
// int fclose (FILE * pf);

void main() {

	FILE * fichero, *fsalida;
	int vx[100], vy[100], i = 0, dim;

	fichero = fopen("datos.txt", "r");

	if (fichero == NULL) {
		printf("Error en fopen\n");
		return;
	}
	// OPERACIONES DE LECTURA (fscanf)
	while (fscanf(fichero, "%d %d", &vx[i], &vy[i]) != EOF) {
		printf("x = %d, y = %d\n", vx[i], vy[i]);
		i++;
	}
	fclose(fichero);

	dim = i;

	printf("Introduce x e y del nuevo punto\n");
	scanf("%d %d", &vx[dim], &vy[dim]);
	dim++;

	// SALVAD LOS DATOS AL FICHERO
	fichero = fopen("datos.txt", "w");

	for (i = 0; i < dim; i++)
		fprintf(fichero, "%d %d\n", vx[i] + 1, vy[i] + 1);

	fclose(fichero);
}