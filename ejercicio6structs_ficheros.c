#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 3
struct empleado {
	int codigo;//5 numeros
	char categoria;//A, B y C
	double sueldo;
	float horas;//suponemos horas semanales
};
/*Ejercicio 6:
FICHERO CON LOS DATOS DEL EMPLEADO, SE GENERA OTRO FICHERO CON EL CÓDIGO DEL EMPLEADO Y EL SUELDO FINAL SEMANAL Y ANUAL. SE SUPONE QUE NO SE SABE EL NÚMERO DE EMPLEADOS.
Define la estructura struct empleado con los campos codigo de empleado, categoria, sueldo y
horas trabajadas. Escribe un programa que lea los datos de un empleado (código, categoría y
horas trabajadas) y calcule el sueldo según esta tabla:
Categoría A → 27.5 €/h.
Categoría B → 20 €/h.
Categoría C → 18.2 €/h.*/
void main() {
	FILE * entrada;
	errno_t error;
	error = fopen_s(&entrada, "empleados.txt", "r");
	if (error == 0) {
		printf("El fichero se ha abierto correctamente \n");
	}
	else {
		printf("ERROR %d", error);
		return;
	}
	struct empleado empleados[N];
	int i;
	i = 0;
	while (fscanf(entrada, "%d %c %f", &empleados[i].codigo, &empleados[i].categoria, &empleados[i].horas) != EOF) {
		i++;
	}//Guardamos datos de empleados del fichero en un vector de estructuras, suponiendo que no sabemos el número concreto de empleados.
	fclose(entrada);//cerramos el fichero de entrada.

					//Genramos el fichero de escritura donde aparecerá el sueldo semanal y el código del empleado 

	FILE * salida;
	salida = fopen("sueldo.txt", "w");


	for (i = 0;i < N;i++) {
		if (empleados[i].categoria == 'A' || empleados[i].categoria == 'a') {
			empleados[i].sueldo = 27.5*empleados[i].horas;
		}
		if (empleados[i].categoria == 'B' || empleados[i].categoria == 'b') {
			empleados[i].sueldo = 20.0*empleados[i].horas;
		}
		if (empleados[i].categoria == 'C' || empleados[i].categoria == 'c') {
			empleados[i].sueldo = 18.2*empleados[i].horas;
		}
	}

	//calculamos sueldo de cada empleado.
	fprintf(salida, "EL SUELDO SEMANAL ES:\n");
	for (i = 0;i < N;i++) {
		fprintf(salida, "%d. Codigo de empleado: %d\tSueldo: %.2f \n", i + 1, empleados[i].codigo, empleados[i].sueldo);
	}
	//Sueldo anual.
	for (i = 0;i < N;i++) {
		empleados[i].sueldo = empleados[i].sueldo*(365.0 / 7.0);
	}

	fprintf(salida, "EL SUELDO ANUAL ES:\n");
	for (i = 0;i < N;i++) {
		fprintf(salida, "%d. Codigo de empleado: %d\tSueldo: %.2f \n", i + 1, empleados[i].codigo, empleados[i].sueldo);
	}

	fclose(salida);//cerramos el fichero de salida.
	system("PAUSE");
}