#include <stdio.h>
struct Cliente {

	int codcuenta;
	int numcuenta;
	float saldocuenta;
 };
void main() {
	

	FILE * fichero;
	errno_t error;
	struct Cliente persona = { 0 };
	int opcion;
	int cuenta = 0;
	float transfer;
	float transfer2;
	error = fopen_s(&fichero, "cuenta.txt", "w");
	if (error != 0) {
		printf("ERROR");
		system("pause");
		return;
	}
	while (1) {


		printf("Bienvenido al banco.\n");
		printf("Escoja una opcion\n");
		printf("1.Apertura de cuenta\n");
		printf("2.Anotacion	de transferencia a su favor\n");
		printf("3. Efectuar	transferencia, cargando	a la cuenta del	cliente\n");
		printf("4. Salir.\n");
		scanf_s("%d", &opcion);
		getchar();
		system("pause");
		system("cls");
		switch (opcion) {
		case 1:
			if (cuenta == 0) {
				printf("Su nueva cuenta es la 1234567\n");
				fprintf(fichero,"cuenta : 1234567\n");
				persona.numcuenta = 1234567;
				printf("Su codigo es 1234\n");
				persona.codcuenta = 1234;
				fprintf(fichero, "codigo : 1234\n");
				printf("Cual es el saldo que desea meter\n");
				scanf_s("%f", &persona.saldocuenta);
				fprintf(fichero, "saldo: %f\n", persona.saldocuenta);
				printf("cuenta creada correctamente\n");
				cuenta=1;
				system("pause");
				system("cls");
			}
			else {
				printf("cuenta ya existente");
			}
			break;
		case 2:
			if (cuenta == 1) {
				printf("Cual es el valor de la transferencia\n");
				scanf_s("%f", &transfer);
				printf("transfiriendo....");
				fprintf(fichero, "transferencia:%f\n", transfer);
				persona.saldocuenta = persona.saldocuenta + transfer;
				printf("su sueldo actual es %.2f", persona.saldocuenta);
				system("pause");
				system("cls");
			}
			else {
				printf("no existe cuenta\n");
				system("pause");
				system("cls");
			}
			break;

		case 3:
			if (cuenta == 1) {
				printf("cuanto desea transferir\n");
				scanf_s("%f", &transfer2);
				if (transfer2 > persona.saldocuenta) {
					printf("Saldo menor que lo que desea transferir");
					system("pause");
					system("cls");
					break;
				}
				else {
					printf("transfiriendo..\n");
					fprintf(fichero, "transferencia:%f\n", transfer2);
					persona.saldocuenta = persona.saldocuenta - transfer2;
					printf("su saldo actual es %.2f\n", persona.saldocuenta);
					system("pause");
					system("cls");
				}
			}
			else {
				printf("no existe cuenta\n");
				system("pause");
				system("cls");
			}
			break;
		case 4:
			fprintf(fichero, "Saldo final:%f",persona.saldocuenta);
			fclose(fichero);
			system("pause");
			return;
		default:
			printf("Opcion no valida\n");
			system("pause");
			system("cls");
		

		}
	}
	system("pause");
}