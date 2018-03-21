#include <stdio.h> 
#include <stdlib.h>
#define TAM 100
// errno_t fopen_s (FILE ** fichero, char nombre[], char modo[]);
// int fclose (FILE * pf);

struct TPunto {
	float x;
	float y;
};

void main() {

	FILE * fichero;
	errno_t error;
	int npuntos, i;
	// Vector de puntos
	struct TPunto vectorPuntos[TAM];

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
		fscanf_s(fichero, "%f %f", &vectorPuntos[i].x, &vectorPuntos[i].y);
		printf("x = %f, y = %f\n", vectorPuntos[i].x, vectorPuntos[i].y);
	}
	// Tercer paso: cerrar el fichero
	fclose(fichero);


}