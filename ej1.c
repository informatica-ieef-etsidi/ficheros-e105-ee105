#include <stdio.h>
#include <stdlib.h>

struct TPunto {
	float x;
	float y;
};

void main(){
	FILE * fichero;
	errno_t error;
	int npuntos, i, j;
	struct TPunto vector[8];
	float ymedio;

	error = fopen_s(&fichero, "signal.txt", "r");

	if (error == 0) {
		printf("Fichero abierto correctamente.\n");
	}
	else {
		printf("Ha habido un error %d al abrir el archivo.\n", error);
		system("Pause");
		return;
	}
	system("Pause");
	i = 0;
	npuntos = 0;
	while (fscanf_s(fichero, "%f", &vector[i].y) != EOF) {
		vector[i].x = (float)i;
		printf("%.0f %f\n", vector[i].x, vector[i].y);
		i++;
		npuntos++;
	}
	fclose(fichero);
	system("pause");

	error = fopen_s(&fichero, "signal_new.txt", "w");
	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}
	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		system("pause");
		return; 
	}
	j = 0;
	fprintf(fichero, "%f\n", vector[j].y);
	for (j = 0; j < (npuntos - 1); j) {
		ymedio = (vector[j].y + vector[j + 1].y)/2;
		fprintf(fichero, "%f\n", ymedio);
		j++;
		fprintf(fichero, "%f\n", vector[j].y);
	}
	fclose(fichero);
}