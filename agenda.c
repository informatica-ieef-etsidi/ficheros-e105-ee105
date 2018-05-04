//Desarrollador: Javier Redondo
//programa que gestiona una agenda y almacena los contactos en un fichero (contactos.txt) y el agno para calcular la edad en otro fichero (agno.txt)

#include <stdio.h>
#define TAM 100

struct fecha {
	int dia;
	int mes;
	int agno;
};
struct agenda {
	char nombre[TAM];
	int telefono;
	struct fecha cumpleagnos;
};

void main() {
	FILE *Fagenda;
	FILE *Fagno;
	errno_t error;
	struct agenda persona[TAM];
	struct agenda temp;
	int cumple[TAM];
	char opcion;
	int agno;
	int s = 0, i = 0, j, k;
	int no_es;

	//lee los ficheros para saber que agno es y almacena en memoria los contactos existentes
	error = fopen_s(&Fagno, "agno.txt", "r");
	if (error != 0) {
		printf("Fichero no abierto correctamente\n");
		system("pause");
		return;
	}
	fscanf_s(Fagno, "%d", &agno);
	fclose(Fagno);
	error = fopen_s(&Fagenda, "contactos.txt", "r");
	if (error != 0) {
		printf("Fichero no abierto correctamente\n");
		system("pause");
		return;
	}

	while (fscanf_s(Fagenda, "%s", &persona[i].nombre,100)!=EOF) {
		fscanf_s(Fagenda, "%d %d %d %d", &persona[i].telefono, &persona[i].cumpleagnos.dia, &persona[i].cumpleagnos.mes, &persona[i].cumpleagnos.agno);
		i++;
	}
	fclose(Fagenda);
	do {
		printf("N-->Busqueda por nombre\n");
		printf("F-->Busqueda por fecha de cumpleagnos\n");
		printf("A-->Hemos cambiado de agno?\n");
		printf("C-->Contacto nuevo\n");
		printf("S-->Salir\n");
		scanf_s("%c", &opcion);
		getchar();
		switch(opcion) {
		case 'C':
		case 'c':
			do {//rellena la agenda con contactos
				printf("Introduzca sus contactos:\n");
				printf("Nombre: ");
				gets(persona[i].nombre);
				printf("Telefono: ");
				scanf_s("%d", &persona[i].telefono);  
				printf("Fecha de nacimiento\nDia: ");
				scanf_s("%d", &persona[i].cumpleagnos.dia);
				printf("Mes: ");
				scanf_s("%d", &persona[i].cumpleagnos.mes);
				printf("Agno: ");
				scanf_s("%d", &persona[i].cumpleagnos.agno);
				printf("Otro contacto?\ns->Si\nOtra techa para cambiar a la pantalla del menu\n");
				getchar();
				scanf_s("%c", &opcion);
				getchar();
				i++;
				system("cls");
			} while ((opcion == 's') || (opcion =='S')); 
			break;
		case 'N':
		case 'n':
			system("cls");
			printf("Nombre: ");
			gets(temp.nombre);
			for (j = 0; j <= i; j++) {
				k = 0;
				no_es = 0;
				while ((persona[j].nombre[k] != '\0') && (temp.nombre[k]!='\0')) {
					if (persona[j].nombre[k] != temp.nombre[k]) {
						no_es++;
						break;
					}
					else if (((persona[j].nombre[k] != '\0') && (temp.nombre[k] == '\0')) || ((persona[j].nombre[k] == '\0') && (temp.nombre[k] != '\0'))) {
						no_es++;
						break;
					}
					k++;	
				}
				if (no_es == 0) {
					break;
				}
			}
			if ((j > i) && (no_es == 1)) {
				printf("Nombre no encontrado\n");
			}
			else {
				system("cls");
				printf("Nombre: %s\nTlf: %d\nCumple %d agnos el %d/%d\n", persona[j].nombre, persona[j].telefono, (agno - persona[j].cumpleagnos.agno), persona[j].cumpleagnos.dia, persona[j].cumpleagnos.mes);
				system("pause");
				system("cls");
			}
			break;
		case 'F':
		case 'f':
			printf("Introduzca la fecha:\nDia: ");
			scanf_s("%d", &temp.cumpleagnos.dia);
			printf("Mes: ");
			scanf_s("%d", &temp.cumpleagnos.mes);
			getchar();
			for (j = 0; j < TAM; j++) {
				cumple[j] = -1;
			}
			k = 0;
			for (j = 0; j <= i; j++) {
				if ((temp.cumpleagnos.dia == persona[j].cumpleagnos.dia) && (temp.cumpleagnos.mes == persona[j].cumpleagnos.mes)) {
					cumple[k] = j;
					k++;
				}
			}
			if (k == 0) {
				printf("No se ha encontrado a nadie.\n");
				system("pause");
			}
			else {
				printf("Los contactos encontrados son:\n");
				j = 0;
				while (cumple[j] != -1) {
					printf("Nombre: %s\nTlf: %d\nCumple %d agnos el %d/%d\n\n", persona[cumple[j]].nombre, persona[cumple[j]].telefono, (agno - persona[cumple[j]].cumpleagnos.agno), persona[cumple[j]].cumpleagnos.dia, persona[cumple[j]].cumpleagnos.mes);
						j++;
				}
				system("pause");
				system("cls");
				break;
			}
		case 'A'://cambia el agno que lo usa para calcular las edades
		case 'a':
			printf("Que agno es? : ");
			scanf_s("%d", &agno);
			getchar();
			system("cls");
			break;
		case's':
		case'S':
			error = fopen_s(&Fagenda, "contactos.txt", "w");
			if (error != 0) {
				printf("Fichero no abierto correctamente\n");
				system("pause");
				return;
			}
			for (j = 0; j < i; j++) {
				fprintf(Fagenda, "%s\t", persona[j].nombre, 100);
				fprintf(Fagenda, "%d\t%d\t%d\t%d\n", persona[j].telefono, persona[j].cumpleagnos.dia, persona[j].cumpleagnos.mes, persona[j].cumpleagnos.agno);
			}
			fclose(Fagenda);
			error = fopen_s(Fagno, "agno.txt", "w");
			if (error != 0) {
				printf("Fichero no abierto correctamente\n");
				system("pause");
				return;
			}
			fprintf(Fagno, "%d", agno);
			fclose(Fagno);
			s = 1;
			break;
		default:
			printf("Opcion incorrecta.\n");
			system("pause");
			system("cls");
		}
		
	} while (s == 0);

}