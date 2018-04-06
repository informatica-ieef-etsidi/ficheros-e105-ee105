//DESARROLLADOR: ALFONSO PINTO
//EL PROGRAMA MUESTRA LAS PUNTUACIONES DE CINCO JUGADORES EN UN JUEGO CUALQUIERA. TAMBIEN SE PUEDE 
//MODIFICAR LAS PUNTUACIONES EN EL MISMO FICHERO. ASI EN LA PROXIMA APERTURA SE HABRAN GUARDADO LAS QUE HEMOS INTRODUCIDO


#include<stdio.h>
#include<string.h>
#define N 5
 



void main() {
	int puntos[N];

	int i;
	int k;
	int h;
	int salir;

	FILE *fichero;
	errno_t error;

	error = fopen_s(&fichero, "Puntuaciones.txt", "r"); //ABRIMOS EL FICHERO
	if (error == 0) {
		printf("Inicializando el programa... \n");
	}
	else {
		printf("Ha habido un error al iniciar el programa...");
		return;
	}

	for (i = 0; i < N; i++) {    //LEEMOS TODA LA INFORMACION DEL FICHERO Y LA PASAMOS AL VECTOR PUNTOS
		fscanf_s(fichero, "%d", &puntos[i]);
	}
	fclose(fichero);


	do {
		salir = 1;
		printf("Bienvenido, que desea hacer: \n");
		printf("Consultar puntuaiones globales-Pulse 1 \n");
		printf("Modificar puntuaciones globales-Pulse 2 \n");
		printf("Salir-Pulse 3 \n");
		scanf_s("%d", &k);

		switch (k) {
		case 1:
			for (i = 0; i < N; i++) {
				printf("El jugador %d lleva %d puntos \n", i + 1, puntos[i]);
			}
			system("pause");
			break;
		case 2:

			for (i = 0; i < N; i++) {
				printf("Introduce el incremento de puntos del jugador %d:", i + 1);
				scanf_s("%d", &h);
				puntos[i] = puntos[i] + h;
			}

			error = fopen_s(&fichero, "Puntuaciones.txt", "w"); //ABRIMOS DE NUEVO EL MISMO FICHERO EN MODO LECTURA
			if (error == 0) {
				printf("Inicializando el programa... \n");
			}
			else {
				printf("Ha habido un error al iniciar el programa...");
				return;
			}
			for (i = 0; i < N; i++) {   //ESCRIBO LOS NUEVOS VALORES DE LOS PUNTOS
				fprintf(fichero, "%d \n", puntos[i]);
			}
			fclose(fichero);

			break;

		case 3:
			salir = 0;
		default:
			break;
		}
		system("cls");
	} while (salir);
	system("pause");
}