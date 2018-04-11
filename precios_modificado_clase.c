//Desarrollador: Sandra Ures
//Programa que calcula el producto mas barato entre 3, teniendo en cuenta sus descuentos

#include <stdio.h>
#include <stdlib.h>

#define NUMPROD 50

struct producto {
	float precio;
	float descuento;
};

void main() {
	FILE * fichero;
	errno_t error;

	struct producto producto[NUMPROD];
	int i = 0, j;
	float minimo, aux;
	int nproductos = 0;

	// Los datos de los productos se leen de un fichero
	error = fopen_s(&fichero, "productos.txt", "r");

	if (error != 0) {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return;
	}

	i = 0;
	while (fscanf_s(fichero, "%f %f", &producto[i].precio, &producto[i].descuento) != EOF) {
		i++;
		nproductos++;
	}
	fclose(fichero);

	minimo = producto[0].precio * (100 - producto[0].descuento) / 100;
	j = 0;
	for (i = 1; i < nproductos; i++) {
		aux = producto[i].precio * (100 - producto[i].descuento) / 100;
		if (aux < minimo) {
			minimo = aux;
			j = i;
		}
	}

	printf("El producto mas barato es el %d con un precio de %.2f\n", j + 1, minimo);

	//Parte del fichero
	error = fopen_s(&fichero, "precios.txt", "w");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}
	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		system("pause");
		return;//sale del programa
	}

	fprintf(fichero, "%d\n", nproductos + 1);

	for (i = 0; i < nproductos; i++) {
		fprintf(fichero, "%.2f\t%.2f\t\n", producto[i].precio, producto[i].descuento);
	}
	fprintf(fichero, "%.2f\n", minimo);

	fclose(fichero);


	system("pause");
}
