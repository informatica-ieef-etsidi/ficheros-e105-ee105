// Desarrollador: Sergio Corredor
#include <stdio.h>
#define TAMVECTOR 50

struct producto {
	float coste, precio, beneficio;
	int cantidadVendida;
	char codigoBarras[TAMVECTOR];
};

void main() {
	
	FILE * fichero;
	errno_t error;

	struct producto mercancia[TAMVECTOR];
	float beneficioTotal=0;
	int i, n;
	
	printf("Introduzca el numero de productos en su tienda:");
	scanf_s("%d", &n);
	
	for (i=0; i<n; i++) {
		printf("Introduzca el codigo de barras del producto %d:", i + 1);
		scanf_s("%s", mercancia[i].codigoBarras, TAMVECTOR);
		printf("Introduzca su coste:");
		scanf_s("%f", &mercancia[i].coste);
		printf("Introduzca su precio:");
		scanf_s("%f", &mercancia[i].precio);
		printf("Introduzca la cantidad de veces que se vendio:");
		scanf_s("%d", &mercancia[i].cantidadVendida);
	}
	
	for (i = 0; i < n; i++) {
		mercancia[i].beneficio = mercancia[i].cantidadVendida*(mercancia[i].precio - mercancia[i].coste);
	}
	
	for (i = 0; i < n; i++) {
		printf("El producto con codigo de barras %s aporto un beneficio de %f euros.\n", mercancia[i].codigoBarras, mercancia[i].beneficio);
	}
	
	for (i = 0; i < n; i++) {
		beneficioTotal += mercancia[i].beneficio;
	}
	
	printf("El beneficio total fue de %f euros.\n", beneficioTotal);

	error = fopen_s(&fichero, "beneficios.txt", "w");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}
	
	else {
		printf("Se ha producido el error %d al abrir el fichero.\n", error);
		system("pause");
		return;
	}

	fprintf(fichero, "%d\n", n);

	for (i = 0; i < n; i++) {
		fprintf(fichero, "%s\t%.2f\n", mercancia[i].codigoBarras, mercancia[i].beneficio, TAMVECTOR);
	}
	
	fprintf(fichero, "%.2f\n", beneficioTotal);

	fclose(fichero);
	
	system("pause");
}
