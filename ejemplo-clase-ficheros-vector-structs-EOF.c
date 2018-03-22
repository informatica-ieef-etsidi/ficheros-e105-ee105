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
	int npuntos = 0, i;
	// Vector de puntos
	struct TPunto vectorPuntos[TAM];

	// Primer paso: abrir el fichero
	error = fopen_s(&fichero, "puntos-EOF.txt", "r");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}
	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return; // return sale del programa
	}
	// Segundo paso: leer el fichero
	i = 0;
	while (fscanf_s(fichero, "%f %f", &vectorPuntos[i].x, &vectorPuntos[i].y) != EOF) {
		printf("x = %f, y = %f\n", vectorPuntos[i].x, vectorPuntos[i].y);
		i++;
		npuntos++;
	}
	// Tercer paso: cerrar el fichero
	fclose(fichero);

	// Guarda un nuevo punto en el vector
	printf("Introduce x e y del nuevo punto\n");
	scanf_s("%f %f", &vectorPuntos[npuntos].x, &vectorPuntos[npuntos].y);
	// Se incrementa el numero de puntos
	npuntos++;

	// Codigo que aumenta en 0.5 todas las coordenadas x
	for (i = 0; i < npuntos; i++) {
		vectorPuntos[i].x = vectorPuntos[i].x + 0.5;
	}

	// Antes del salir del programa, hay que grabar los datos en 
	// el fichero

	// Primer paso: abrir el fichero en modo escritura
	error = fopen_s(&fichero, "puntos-EOF.txt", "w");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}
	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return; // return sale del programa
	}
	// Segundo paso: escribir los datos en el fichero

	for (i = 0; i < npuntos; i++) {
		fprintf(fichero, "%f\t%f\n", vectorPuntos[i].x, vectorPuntos[i].y);
	}
	// Tercer paso: cerrar el fichero
	fclose(fichero);

}