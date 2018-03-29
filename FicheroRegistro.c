//Desarrollador:Ana Dueñas


//Simulador de registro en una web de compras online
//Tras el registro, para poder entrar a su usuario se necesita contraseña
//Se pueden registrar todos los usuarios que se quiera

//ES NECESARIO ESCOGER LA OPCION SALIR PARA QUE SE GUARDEN LOS DATOS

#include <stdio.h>
#include <Windows.h>
#include <string.h>
#define NUMUSUARIOS 10

struct TUsuario {
	char nombre[50];
	char contrasena[50];
	char cuentabancaria[25];
};
struct TAux {
	char nombre[50];
	char contrasena[50];
	char cuentabancaria[25];
};
void main() {
	FILE*fichero;
	errno_t error;
	struct TUsuario usu[NUMUSUARIOS];
	struct TAux aux;

	int opcion, comp1, k = 0, i, auxx = 0, nusu=0;
	printf("Bienvenido a nuestra pagina de ventas online.\n");
	printf("Espere, estamos cargando los datos del sistema\n");
	Sleep(2000);
	
	error = fopen_s(&fichero, "usuarios.txt", "r");//Error al abrir el fichero?
	
	if (error == 0) { 
		printf("Datos cargados\n");
	}
	else {
		printf("Ha habido un error %d al cargar los datos\n", error);
		return; // return sale del programa
	}
	fscanf_s(fichero, "%d", &nusu);//Lee del fichero el numero de usuarios
	if (nusu != 0) {//Si no es 0, lee el fichero completo
		for (i = 0; i < nusu; i++) {
			fscanf_s(fichero,"%s\t", usu[i].nombre, 50);
			fscanf_s(fichero,"%s\t", usu[i].contrasena, 50);
			fscanf_s(fichero,"%s\t", usu[i].cuentabancaria, 25);
			
		}
	}
	fclose(fichero);//Se cierra y comienza el programa.

	do {//Bucle que se repite hasta que se quiera salir del programa
		
		
		system("cls");
		printf("Elija entre estas opciones e introduzca su decision\n");
		printf("1.	Acceder a su cuenta\n2.	Registrarse\n3.	Salir del programa\n"); //menu
		scanf_s("%d", &opcion);
		getchar();
		switch (opcion) {
		case 1: //Acceder a una cuenta
			printf("Introduzca su nombre de usuario\n");
			scanf_s("%s", &aux.nombre, 50);
			getchar();
			for (k = 0; k < nusu; k++) {
				comp1 = strcmp(aux.nombre, usu[k].nombre); //Compara entre todos los usuarios ya registrados
				if (comp1 == 0) {
					break;
				}
			}

			if (comp1 == 0) {//Si coincide con algun nombre
				printf("Bienvenido %s\n", usu[k].nombre);
				do {
					printf("Introduzca su contrasena para entrar\n");
					scanf_s("%s", &aux.contrasena, 50);
					getchar();
					comp1 = strcmp(aux.contrasena, usu[k].contrasena); //Compara  si es la contraseña

					if (comp1 == 0) {
						printf("Contrasena correcta\n");
						Sleep(2000);
					}
					else {
						printf("Contrasena incorrecta vuelva a intentarlo\n");
					}
				} while (comp1 != 0); //Hasta que la contraseña sea correcta se repite
			}
			else {
				printf("Lo sentimos, no se encuentra entre nuestros usuarios, registrese como uno nuevo.\n");
				Sleep(2000);
			}
			break;
		case 2: //Registro
			printf("Para registrarse necesitamos varios datos sobre usted\n");
			do {
				printf("Introduzca su nombre de usuario\n");
				scanf_s("%s", &aux.nombre, 50);
				getchar();
				for (k = 0; k < nusu; k++) {
					comp1 = strcmp(aux.nombre, usu[k].nombre); //Compara entre todos los usuarios
					if (comp1 == 0) {
						break;

					}
				}

				if (comp1 != 0) {//Si no hay nadie registrado con ese nombre
					if (nusu == NUMUSUARIOS) {//Si el numero de usuarios es igual al numero maximo de ellos
						printf("NO SE PUEDEN REGISTRAR MAS USUARIOS\n");

					}
					else {
						strcpy_s(usu[nusu].nombre, 50, aux.nombre); //guarda el nombre nuevo en usuarios
						printf("Introduzca su contrasena\n");
						scanf_s("%s", &usu[nusu].contrasena, 50);
						getchar();
						printf("Introduzca su numero de cuenta bancaria\n");
						scanf_s("%s", &usu[nusu].cuentabancaria, 25);
						getchar();
						printf("Usted ha sido registrado como %s con contrasena %s y numero de cuenta %s\n", usu[nusu].nombre, usu[nusu].contrasena, usu[nusu].cuentabancaria);
						Sleep(2000);
						nusu = nusu++;//Como se ha registrado un usuarios aumentamos uno el numero de usuarios

					}
				}
				else {
					printf("Ya existe un usuario con ese nombre, intente con otro\n");
				}
			} while (comp1 == 0);//Se repite mientras que se introduzcan nombres ya registrados
			Sleep(2000);

			getchar();
			break;
		case 3: printf("Hasta la proxima!\n");
			Sleep(2000);
			getchar();
			break;

		default: printf("Elija entre alguna de las 3 opciones\n");

			Sleep(2000);
			getchar();
			break;
		}

	} while (opcion != 3); //Se repite hasta que se acabe le numero de usuarios permitidos 
						   // o se decida salir del programa
	error = fopen_s(&fichero, "usuarios.txt", "w");//Error para escribir en el fichero

	if (error == 0) {//Si no hay error
		printf("Guardando datos...\n");
	}
	else {//Si hay error
		printf("Ha habido un error %d para guardar los datos.\n", error);
		return; // return sale del programa
	}
	fprintf(fichero, "%d\n", nusu);//Imprime el numero de usuarios alcanzado
	for (i = 0; i < nusu; i++) {//En un bucle va escribiendo los usuarios que se han registrado antes de salir
		fprintf(fichero, "%s\t%s\t%s\n", usu[i].nombre, usu[i].contrasena, usu[i].cuentabancaria);
	}
	fclose(fichero);
	

	system("pause");
}