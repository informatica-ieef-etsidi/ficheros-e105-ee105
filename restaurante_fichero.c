//Paula Arellano
/*Programa que gestiona las mesas de un restaurante: va asociado a un fichero donde esta guardado el menu. Al iniciar el programa,
se abre el fichero con el menu y los comensales eligen el numero de la comida y la bebida que van a pedir. Estos datos se guardan en 
un vector dentro de una estructura y se calcula el precio de lo que han comido. El vector de estructuras se guarda en el fichero */

#include<stdio.h>
#include<stdlib.h>
#define NMESAS 2

struct mesas {
	int numero;
	int comensales;
	float cuenta;
	int comida[30];
	int bebida[30];

};

void main() {
	FILE * fichero;
	errno_t error;
	struct mesas restaurante[NMESAS];
	char menu;
	int i, j;

	//ABRIR EL FICHERO EN MODO LECTURA
	
	error = fopen_s(&fichero, "restaurante.txt", "r");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}

	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return; 
	}

	//LEER E IMPRIMIR EL FICHERO
	while ((menu = fgetc(fichero)) != EOF)
		printf("%c", menu);

	printf("\n");

	//CERRAR EL FICHERO
	fclose(fichero);


			//PEDIDO DEL RESTAURANTE: GUARDA LOS DATOS EN UNA ESTRUCTURA
	for (i = 0; i < NMESAS; i++) {
		printf("\nNumero de mesa: ");
		scanf_s("%d", &restaurante[i].numero);
		printf("Numero de comensales: ");
		scanf_s("%d", &restaurante[i].comensales);

		for (j = 0; j < restaurante[i].comensales; j++) {
			printf("Introduzca numero de comida del comensal %d: ", j + 1);
			scanf_s("%d", &restaurante[i].comida[j]);
			printf("Introduzca numero de bebida del comensal %d: ", j + 1);
			scanf_s("%d", &restaurante[i].bebida[j]);
		}
	}

	for (i = 0; i < NMESAS; i++) {
		restaurante[i].cuenta = 0;
		for (j = 0; j < restaurante[i].comensales; j++) {
			switch (restaurante[i].comida[j]) {
			case 1:
				restaurante[i].cuenta = restaurante[i].cuenta + 4;
				break;
			case 2:
				restaurante[i].cuenta = restaurante[i].cuenta + 5;
				break;
			case 3:
				restaurante[i].cuenta = restaurante[i].cuenta + 4;
				break;
			case 4:
				restaurante[i].cuenta = restaurante[i].cuenta + 3;
			}

			switch (restaurante[i].bebida[j]) {
			case 1:
				restaurante[i].cuenta = restaurante[i].cuenta + 1;
				break;
			case 2:
				restaurante[i].cuenta = restaurante[i].cuenta + 1.5;
				break;
			case 3:
				restaurante[i].cuenta = restaurante[i].cuenta + 1.25;
				break;
			case 4:
				restaurante[i].cuenta = restaurante[i].cuenta + 1;
			}
		}

	}

	for (i = 0; i < NMESAS; i++) {
		printf("Numero de mesa: %d\n", restaurante[i].numero);
		printf(" Comensales: %d\n", restaurante[i].comensales);
		printf(" Comida: ");
		for (j = 0; j < restaurante[i].comensales; j++) {
			printf("%d, ", restaurante[i].comida[j]);
		}
		printf("\n Bebida: ");
		for (j = 0; j < restaurante[i].comensales; j++) {
			printf("%d, ", restaurante[i].bebida[j]);
		}
		printf("\n Importe: %.2f\n", restaurante[i].cuenta);
	}


	//ABRIR EL FICHERO EN MODO ESCRITURA (ADD)

	error = fopen_s(&fichero, "restaurante.txt", "a"); 

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}

	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return; 
	}

	//GUARDO ESTRUCTUA EN EL FICHERO

	for (i = 0; i < NMESAS; i++) {
		fprintf(fichero, "\nNumero de mesa: %d\n", restaurante[i].numero);
		fprintf(fichero, " Comensales:%d\n", restaurante[i].comensales);
		for (j = 0; j < restaurante[i].comensales; j++) {
			fprintf(fichero, "   Comensal %d: comida- %d  /  bebida- %d\n", j, restaurante[i].comida[j], restaurante[i].bebida[j]);
		}
		fprintf(fichero, " Importe: %f\n", restaurante[i].cuenta);
	}

	//CERRAR EL FICHERO
	fclose(fichero);

	system("PAUSE");
}