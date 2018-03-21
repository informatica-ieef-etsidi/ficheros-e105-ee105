#include <stdio.h> 
#include <stdlib.h>

// errno_t fopen_s (FILE ** fichero, char nombre[], char modo[]);
// int fclose (FILE * pf);

void main() {

	FILE * fichero;
	errno_t error;
	int npuntos, i;
	float x, y;

	// Primer paso: abrir el fichero
	error = fopen_s(&fichero, "puntos.txt", "r");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}
	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return; // return sale del programa
	}
	// Segundo paso: leer el fichero
	fscanf_s(fichero, "%d", &npuntos);
	printf("Hay %d puntos en el fichero\n", npuntos);

	for (i = 0; i < npuntos; i++) {
		fscanf_s(fichero, "%f %f", &x, &y);
		printf("x = %f, y = %f\n", x, y);
	}
	// Tercer paso: cerrar el fichero
	fclose(fichero);
}