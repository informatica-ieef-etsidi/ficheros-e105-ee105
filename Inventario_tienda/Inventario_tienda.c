/*ALEJANDRO_LÓPEZ_GUERRERO. Este programa simula un sencillo inventario de una tienda de componentes eléctricos. 
Para poder hacer funcionar el programa se necesitan además los ficheros memoria.txt y Activation.txt*/

// DESBLOQUEO: >>> USUARIO: tienda  CONTRASEÑA:1234

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct {
	char user[50];
	char password[50];
}acceso;

typedef struct {
	char codigo[15];
	char nombre[25];
	char modelo[20];
	int cantidad;
	float precio;
}inventario;

void main(void) {
	//Direcciones de los ficheros Activation.txt, memoria.txt y memoria_aux.txt respectivamente.
	FILE *access;
	FILE *data;
	FILE *data_aux;

	acceso desbloqueo;
	inventario productos[200];
	char user_aux[50], password_aux[50], aux[50], opcionmenu1, caracter,opcionmenu3, code_aux[15];
	int i,j, k, booleana;
	
	errno_t Error1, Error2;
	//El código de debajo evalúa si se encuentran los ficheros correspondientes a access y a data
	Error1 = fopen_s(&access, "Activation.txt", "r");
	Error2 = fopen_s(&data, "memoria.txt", "r");
	fopen_s(&data_aux, "memoria_aux.txt", "w");//Este fichero, a no existir se crea nuevo
	if ((Error1 != NULL) || (Error2 != NULL)) {
		system("color 0C");
		for (i = 7; i > 0; i--) {
			system("cls");
			printf("Fallo al ejecutar el programa.\n\nFaltan los ficheros de memoria o son defectuosos.\n\n");
			printf("El programa se cerrara en %d segundos", i);
			Sleep(1000);
		}
		return;
	}
	//Inicializamos las cadenas donde el usuario escribirá el user y el password
	for (i = 0; i < 50; i++) {
		user_aux[i] = '\0';
		password_aux[i] = '\0';
	}
	/*En el código de debajo copiamos los datos del fichero data al data_aux. A partir de ahora los cambios efectuados durante 
	la ejecución del programa se irán guardando en data_aux*/
	caracter = fgetc(data);
	while (caracter != EOF){
		fputc(caracter, data_aux);
		caracter = fgetc(data);
	}
	fclose(data_aux);
	
	booleana = 0;//Variable para bloquear y desbloquear el programa
	do {
		system("cls");

		//MENU PRINCIPAL
		printf("\n\tRECAMBIOS ELECTRIC.SA\n\n\n  Menu principal\n\n\t");
		if (booleana == 0) printf("(D) >> Desbloquear programa\n\n\t");
		else if(booleana==1) printf("(B) >> Bloquear programa\n\n\t");
		printf("(V) >> Visualizar inventario");
		printf("\n\n\t(A) >> Agregar productos al inventario\n\n\t(Q) >> Quitar productos del inventario\n\n\t(S) >> Salir\n\nOpcion: ");
		scanf("%c", &opcionmenu1);
		system("cls");

		switch (opcionmenu1) {
		case 'D'://Desbloquear programa(en caso de estar bloqueado)
		case 'd':
			if (booleana == 1) break;
			getchar();
			printf("Desbloquear programa\n\nIntroduzca usuario: ");
			gets(user_aux);
			printf("\nIntroduzca contraseña: ");
			gets(password_aux);

			//Descodificar contraseña(Se encuentra codificada en el fichero access)
			fclose(access);
			fopen_s(&access, "Activation.txt", "r");
			fscanf(access, "%s", aux);
			for (i = 0; i < 50; i++) {
				if (aux[i] != '\0') {
					aux[i] = aux[i] - 3;
				}
			}
			strcpy(desbloqueo.user, aux);//El user se almacena en desbloqueo.user una vez descodificado
			fscanf(access, "%s", aux);
			for (i = 0; i < 50; i++) {
				if (aux[i] != '\0') {
					aux[i] = aux[i] - 3;
				}
			}
			strcpy(desbloqueo.password, aux);//El password se almacena en desbloqueo.password una vez descodificado
			
			//Con el paso siguiente verificamos la identidad y la contraseña
			if (((strcmp(desbloqueo.user, user_aux)) == 0) && ((strcmp(desbloqueo.password, password_aux)) == 0)) {
				booleana = 1;
				printf("Programa desbloqueado\n\n");
				system("Pasue()");
			}
			else {
				printf("\nLas claves de acceso no coinciden\n\n");
				system("Pause()");
			}
			fclose(access);
			break;
		case 'B'://Bloquear programa(en caso de estar desbloqueado)
		case 'b':
			if (booleana == 0) break;
			booleana = 0;
			printf("El programa ha sido bloqueado\n\n");
			system("Pause()");
			break;
		case 'V'://Visualizar inventario
		case 'v':
			if (booleana == 0) { printf("\nPrimero tiene que desbloquear el programa\n\n"); system("Pause()"); break; }
			fopen_s(&data_aux, "memoria_aux.txt", "r");
			printf("\n\tINVENTARIO\n\n");
			printf("CODIGO --- NOMBRE --- MODELO --- CANTIDAD --- PRECIO\n\n");
			i = 0;
			//Impresión por pantalla de la información almacenada en data_aux.
			while(fscanf(data_aux, "%s %s %s %d %f", productos[i].codigo, productos[i].nombre, productos[i].modelo,
				&productos[i].cantidad, &productos[i].precio) != EOF){				
				printf("%s   %s    %s    %d     %.2f Euros\n", productos[i].codigo, productos[i].nombre,
					productos[i].modelo, productos[i].cantidad, productos[i].precio);
				i++;
			}

			printf("\n\n");
			system("Pause()");
			fclose(data_aux);
			break;
		case 'A'://Añadir productos al inventario
		case 'a':
			getchar();
			if (booleana == 0) { printf("\nPrimero tiene que desbloquear el programa\n\n"); system("Pause()"); break; }
			
			printf("Agregar productos al inventario\n\n");
			printf("Introduzca a continuacion los siguientes datos del producto:");
			printf("\n\nCODIGO: ");
			gets(productos[0].codigo);
			printf("\nNOMBRE: ");
			gets(productos[0].nombre);
			_strupr(productos[0].nombre);
			//Si el usuario introduce espacios se sustituyen por '_', para no crear problemas en el fichero
			for (i = 0; i < 25; i++) {
				if (productos[0].nombre[i] == ' ') {
					productos[0].nombre[i] = '_';
				}
			}
			printf("\nMODELO: ");
			gets(productos[0].modelo);
			_strupr(productos[0].modelo);
			for (i = 0; i < 20; i++) {
				if (productos[0].modelo[i] == ' ') {
					productos[0].modelo[i] = '-';
				}
			}
			printf("\nCANTIDAD: ");
			scanf("%d",&productos[0].cantidad);
			printf("\nPRECIO: ");
			scanf("%f", &productos[0].precio);
			Sleep(100);
			fopen_s(&data_aux, "memoria_aux.txt", "a");
			fprintf(data_aux,"%s %s %s %d %f\n", productos[0].codigo, productos[0].nombre, productos[0].modelo, 
				productos[0].cantidad, productos[0].precio);
			fclose(data_aux);
			printf("\n\nProducto guardado\n\n");
			break;
		case 'Q'://Quitar producto del inventario
		case 'q':
			getchar();
			if (booleana == 0) { printf("\nPrimero tiene que desbloquear el programa\n\n"); system("Pause()"); break; }
			printf("Indique el codigo del producto: ");
			scanf("%s", code_aux);//Almacenamos el código de búsqueda en code_aux
			fopen_s(&data_aux, "memoria_aux.txt", "r");
			i = 0;
			j = -1;//Esta variable registrará la posición del producto en el vector de estructuras de productos
			while (fscanf(data_aux, "%s %s %s %d %f", productos[i].codigo, productos[i].nombre, productos[i].modelo,
				&productos[i].cantidad, &productos[i].precio) != EOF) {
				if (strcmp(productos[i].codigo, code_aux) == 0) {
					j = i;
					}
				i++;
			}
			//Si ha encontrado alguna coincidencia ha cambiado el valor de j.
			if (j != -1) {
				fclose(data_aux);
				fopen_s(&data_aux, "memoria_aux.txt", "w");
				for (k = 0; k < i; k++) {
					if (k == j) {
						continue;//Cuando vaya a escribir en el fichero el producto de la posición j, se lo salta
					}else
						fprintf(data_aux,"%s %s %s %d %f\n", productos[k].codigo, productos[k].nombre, productos[k].modelo,
							productos[k].cantidad, productos[k].precio);
				}
				printf("\n\nProducto borrado\n\n");
				system("Pause()");
			}
			else {
				printf("\n\nNo se ha encontrado ningun producto con ese codigo\n\n");
				system("Pause()");
			}

			break;
		case 'S'://Salir del programa
		case 's':
			getchar();
			opcionmenu1 = 'S';
			printf("Salir del programa\n\n\n¿Desea guardar los cambios realizados?:\n\n\t(S) >> SI\n\n\t(N) >> NO\n\n\t(C) >> Cancelar\n\nOpcion: ");
			scanf("%c", &opcionmenu3);
			switch (opcionmenu3) {
			case 's':
			case 'S':
				//Si el usuario guarda los cambios, se copia el fichero data_aux al data, para fijar los cambios realizados
				fclose(data);
				fclose(data_aux);
				fopen_s(&data, "memoria.txt", "w");
				fopen_s(&data_aux, "memoria_aux.txt", "r");
				//En el siguiente while se copian los datos de un fichero al otro
				caracter = fgetc(data_aux);
				while(caracter  != EOF){
					fputc(caracter, data);
					caracter = fgetc(data_aux);
					
				}
				fclose(data);
				fclose(data_aux);
				fclose(access);
				printf("\n\nDatos guardados correctamente.\n\n");
				
				break;
			case 'n':
			case 'N':
				remove(data_aux);//Se supone que esta fución borra el fichero de data_aux, eliminando así los cambios realizados
				fclose(data);
				fclose(access);
				printf("\n\nNo se han guardado los cambios.\n\n");
				
				break;
			default:
				opcionmenu3 = 'E';
				break;
			}

			break;
		default:
			
			if (opcionmenu1 != '\n') {
				printf("Opcion incorrecta.\n\n");
				system("Pause");
			}
			break;
		}
		fclose(data_aux);
	} while ((opcionmenu1 != 'S')||(opcionmenu3=='E'));
	fclose(access);
	system("Pause()");
}
		