#include <stdio.h>
#include "menu.hpp"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "datos.hpp"
#include <stdlib.h>
#include <iomanip>

using namespace std;

int buscarReferencia(string numero, string proveedor) { /*Función para elegir la referencia con la que quieres trabajar*/
	tReferencia referencias;
	string bufferNombre;
	int contador = 0;
	string nombrearchivo;


	nombrearchivo = proveedor;
	nombrearchivo = nombrearchivo + ".txt";

	ifstream archivoMostrar(nombrearchivo);
	archivoMostrar.read((char*)& referencias, sizeof(referencias));

	while (archivoMostrar && !archivoMostrar.eof()) {
		bufferNombre = referencias.numero;
		contador++;

		archivoMostrar.read((char*)& referencias, sizeof(referencias));


		if (numero == bufferNombre) {
			system("cls");
			gotoxy(45, 14);
			printf("Referencia encontrada\n");
			gotoxy(50, 16);
			printf("Presione cualquier tecla para continuar\n");
			archivoMostrar.read((char*)& referencias, sizeof(referencias));
			return contador;
		}
	}
	archivoMostrar.close();
	return 0;
}   

bool referenciaCambiada(int ubicacion, string nombrearchivo) {
	try {
		tReferencia referencia;
		cin.ignore();
		system("cls");
		gotoxy(45, 4);
		printf("Introduzca nueva designacion:\n");
		gotoxy(50, 6);
		cin.getline(referencia.designacion, MAX_DESIGNACION);
		gotoxy(45, 8);
		printf("Introduzca nuevo numero de referencia:\n");
		gotoxy(50, 10);
		cin.getline(referencia.numero, MAX_CHARS);
		gotoxy(45, 12);
		printf("Introduzca nuevo condicionante:\n");
		gotoxy(50, 14);
		cin.getline(referencia.codicionante, MAX_CHARS);
		gotoxy(45, 16);
		printf("Introduzca la cantidad de palets que caben en stock:\n");
		gotoxy(50, 18);
		cin.getline(referencia.facingMaximo, MAX_CHARS);
		gotoxy(45, 20);
		printf("Introduzca la media de ventas mensuales:\n");
		gotoxy(50, 22);
		cin.getline(referencia.ventas, MAX_CHARS);

		gotoxy(45, 28);
		system("pause");

		nombrearchivo = nombrearchivo + ".txt";

		fstream archivoCambio(nombrearchivo);
		archivoCambio.seekg((ubicacion - 1) * sizeof(referencia), ios::beg);
		archivoCambio.write((char*)& referencia, sizeof(referencia));
		archivoCambio.close();
		return true;
	}
	catch (exception e) {
		printf("\nHa ocurrido un error");
		return false;
	}
}

bool mediaCambiada(int ubicacion, string nombrearchivo) {
	try {
		char nuevaMedia[5];
		tReferencia referencia, referencias;
		cin.ignore();
		system("cls");
		gotoxy(45, 4);
		printf("Introduzca la nueva media de ventas mensuales:\n");
		gotoxy(50, 6);
		cin.getline(nuevaMedia, MAX_CHARS);

		nombrearchivo = nombrearchivo + ".txt";

		ifstream archivoMostrar(nombrearchivo);
		system("cls");
		archivoMostrar.seekg((ubicacion - 1) * sizeof(referencia), ios::beg);
		archivoMostrar.read((char*)& referencias, sizeof(referencias));

		strcpy_s(referencia.designacion, referencias.designacion);
		strcpy_s(referencia.numero, referencias.numero);
		strcpy_s(referencia.codicionante, referencias.codicionante);
		strcpy_s(referencia.facingMaximo, referencias.facingMaximo);
		strcpy_s(referencia.ventas, nuevaMedia);

		fstream archivoCambio(nombrearchivo);
		archivoCambio.seekg((ubicacion - 1) * sizeof(referencia), ios::beg);
		archivoCambio.write((char*)& referencia, sizeof(referencia));
		archivoCambio.close();
		return true;
	}
	catch (exception e) {
		printf("\nHa ocurrido un error");
		return false;
	}
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void menuPrincipal() {
	int opcion = 0;
	int a = 1;

	do {
		system("cls");
		gotoxy(40, 4);
		printf("BIENVENIDO A LA CALCULADORA DE PEDIDOS.\n");
		gotoxy(43, 6);
		printf("ELIJA UNA OPCION PARA CONTINUAR.\n");
		gotoxy(45, 10);
		printf("1  -> Calcular pedido\n");
		gotoxy(45, 12);
		printf("2  -> Nuevo proveedor\n");
		gotoxy(45, 14);
		printf("3  -> Modificar datos\n");
		gotoxy(45, 16);
		printf("4  -> Ver proveedor\n");
		gotoxy(45, 18);
		printf("5  -> Ver referencias\n");
		gotoxy(45, 20);
		printf("99 -> Salir\n");

		gotoxy(50, 24);
		printf("Escriba opcion: "); scanf_s("%d", &opcion);

		switch (opcion) {
		case 1:
			menuCalcularPedido();
			break;
		case 2:
			menuNuevoProveedor();
			break;
		case 3:
			menuModificarDatos();
			break;
		case 4:
			menuVerProveedor();
			break;
		case 5:
			menuVerReferencia();
			break;
		case 99:
			a = 0;
			exit(1);
			break;
		default:
			gotoxy(40, 24);
			printf("Opcion incorrecta. Vuelva a intentarlo.\n");
			gotoxy(40, 26);
			system("pause");
		}
	} while (a);

}

void menuCalcularPedido() {

	/*primero elegimos el proveedor que deseamos calcular*/

	system("cls");
	gotoxy(50, 2);
	printf("CALCULADORA DE PEDIDOS\n\n");
	printf("\t\t| PROVEEDOR                              | NUMERO |\n");

	tProveedor proveedor;

	ifstream archivoMostrar("proveedores.txt");
	archivoMostrar.read((char*)& proveedor, sizeof(proveedor));

	char numprov[8];

	int numprovAux[100];
	int cabenAux[100]; // cantidad de palets que caben en el camión.
	int z = 0;

	while (archivoMostrar && !archivoMostrar.eof()) {

			cout << "\n\t\t" << left << setw(40) << proveedor.designacion << "   " << left << setw(10) << proveedor.numero << " " << endl;		
			numprovAux[z] = atoi(proveedor.numero);
			cabenAux[z] = atoi(proveedor.pedMaximo);
			archivoMostrar.read((char*)& proveedor, sizeof(proveedor));
			z = z + 1;
	}
	
	cin.ignore();
	gotoxy(45, 24);
	printf("Introduzca el numero del proveedor que desea calcular:\n");
	gotoxy(50, 26);
	cin.getline(numprov, MAX_CHARS);
	
	/*buscar la cantidad de palets que caben en el camion*/
	int j;
	int caben=0;
	int aux;
	
	aux = atoi(numprov);

	for (j = 0; j < 20; j++) {
		if (numprovAux[j] == aux) {
			caben = cabenAux[j];
			
		}
	}
	gotoxy(45, 28);
	system("pause");

	/*abrir archivo del proveedor y mostrar referencias*/
	string nombrearchivo;
	nombrearchivo = numprov;
	nombrearchivo = nombrearchivo + ".txt";

	tReferencia referencias;

	int modificar = 0;

	char numref[8];
	int lugar = 0;
	int contador = 0; /*contador de referencias*/
	char kilospalets[8]; /*auxiliar cálculo kilos palets*/


	while (modificar == 0) {/*modificar medias*/
		ifstream archivoMostrar2(nombrearchivo);
		system("cls");
		archivoMostrar.read((char*)& referencias, sizeof(referencias));

		system("cls");
		gotoxy(50, 2);
		printf("LISTA DE REFERENCIAS\n");
		gotoxy(15, 4);
		printf("| DESIGNACION                            |  NUMERO  | CONDICIONANTE | FACING | VENTAS |\n");
	

		while (archivoMostrar2 && !archivoMostrar2.eof()) {

			cout << "\t\t" << left << setw(40) << referencias.designacion << "   " << left << setw(12) << referencias.numero << " " << left << setw(14) << referencias.codicionante << " " << left << setw(6)
				<< referencias.facingMaximo << " " << left << setw(10) << referencias.ventas << endl;
			strcpy_s(kilospalets, proveedor.calculo);
			archivoMostrar2.read((char*)& referencias, sizeof(referencias));
		}
							
							/*preguntar si queremos modificar las ventas*/
		gotoxy(40, 22);
		printf("Inserte 0 si quiere modificar las medias y 1 si quiere continuar\n");
		gotoxy(45, 24);
		scanf_s("%d", &modificar);
		
		if (modificar == 1) {
			break;
		}
		gotoxy(40, 26);
		getchar();
		printf("Inserte el numero de referencia que desea modificar:\n");
		gotoxy(40, 28);
		cin.getline(numref, MAX_CHARS);
		
		lugar = buscarReferencia(numref, numprov);
		
		if (lugar) {
			if (mediaCambiada(lugar, numprov)) {
				system("cls");
				gotoxy(45, 6);
				printf("La referencia se ha modificado con exito.\n");
				gotoxy(45, 14);
				printf("Pulse 0 si desea modificar otra referencia y 1 si desea continuar:\n");
				gotoxy(50, 16);
				scanf_s("%d", &modificar);
			}
			else {
				system("cls");
				gotoxy(45, 6);
				printf("La referencia no existe en el archivo");
				gotoxy(45, 8);
				system("pause");
			}
		}
	}

	/*preguntar stock actual de cada referencia (en palets)*/

	tAuxCalculo auxcalculo[100];

	ifstream archivoMostrar3(nombrearchivo);
	system("cls");
	archivoMostrar3.read((char*)& referencias, sizeof(referencias));
	while (archivoMostrar3 && !archivoMostrar3.eof()) {
		
		int palets=0;
		
		system("cls");
		gotoxy(15, 4);
		printf("| DESIGNACION                            |  NUMERO  | CONDICIONANTE | FACING | VENTAS |\n\n");
		cout << "\t\t" << left << setw(40) << referencias.designacion << "   " << left << setw(12) << referencias.numero << " " << left << setw(14) << referencias.codicionante << " " << left << setw(6)
			<< referencias.facingMaximo << " " << left << setw(10) << referencias.ventas << endl;
		
		auxcalculo[contador].auxcondicionante = atoi(referencias.codicionante);
		auxcalculo[contador].auxventas = atoi(referencias.ventas);
		strcpy_s(auxcalculo[contador].auxdesignacion, referencias.designacion);
		strcpy_s(auxcalculo[contador].auxnumero, referencias.numero);
		
		archivoMostrar3.read((char*)& referencias, sizeof(referencias));
		

		gotoxy(25, 16);
		printf("Inserte la cantidad de palets que tienes de la referencia en la actualidad:\n");
		gotoxy(30, 18);
		scanf_s("%d", &palets);
		auxcalculo[contador].stockactual = palets * auxcalculo[contador].auxcondicionante;
		auxcalculo[contador].diascubiertos = (float)auxcalculo[contador].stockactual / (auxcalculo[contador].auxventas / 30);


		gotoxy(40, 22);
		printf("Stock actual de la referencia: %d\n", auxcalculo[contador].stockactual);
		gotoxy(40, 24);
		printf("Dias cubiertos con el stock actual: %f\n", auxcalculo[contador].diascubiertos);
		gotoxy(40, 26);
		system("pause");
		system("cls");
		contador = contador + 1;
	
	}

	/*calculo de media de ventas diarias por referencia y cantidad de dias cubiertos con el stock actual */

	float min = 10000;
	int i, b, contadorref;
	char elegir[40];
	contadorref = 0;
	char elegiracero[40] = "";

	for (b = 0; b < caben; b++) {
		for (i = 0; i < contador; i++) {
			if (min > auxcalculo[i].diascubiertos) {
				min = auxcalculo[i].diascubiertos;
				strcpy_s(elegir, auxcalculo[i].auxdesignacion);
				if (strcmp(elegir, auxcalculo[i].auxdesignacion) == 0) {
					contadorref = i;
				}
			}
		}
		auxcalculo[contadorref].contador = auxcalculo[contadorref].contador + 1;
		auxcalculo[contadorref].stockactual = auxcalculo[contadorref].stockactual + auxcalculo[contadorref].auxcondicionante;
		auxcalculo[contadorref].diascubiertos = ((float)auxcalculo[contadorref].stockactual / (auxcalculo[contadorref].auxventas / 30));
		contadorref = 0;
		min = 10000;
		strcpy_s(elegir, elegiracero);
	}

	gotoxy(40, 2);
	printf("Pedido que tendras que realizar: \n");
	gotoxy(20, 4);
	printf("| DESIGNACION                            |  NUMERO  |  PALETS  | CANTIDAD |\n");

	int x = 20;
	int y = 6;
	for (i = 0; i < contador; i++) {
		gotoxy(x, y);
		printf(" %s\n", auxcalculo[i].auxdesignacion);
		x = 62;
		gotoxy(x, y);
		printf(" %s\n", auxcalculo[i].auxnumero);
		x = 77;
		gotoxy(x, y);
		printf(" %d\n", auxcalculo[i].contador);
		x = 87;
		gotoxy(x, y);
		printf(" %d\n", auxcalculo[i].contador * auxcalculo[i].auxcondicionante);
		y = y + 2;
		x = 20;
	}

	gotoxy(40, 26);
	system("pause");
	

	

	/*comprobrar si calcula por kilos o por palets
	printf("\nkilospalets = %s\n", kilospalets);
	char palets[] = "palets";
	if (strcmp(kilospalets, palets) == 0) {
		printf("\nEl proveedor calcula el camion por palets\n");
		system("pause");
	}
	else {
		printf("\nEl proveedor calcula el camion por kilos\n");
		system("pause");
	}*/
}

void menuNuevoProveedor() {
	int opcion;
	int a = 1;
	ofstream archivoGuardar("proveedores.txt", ios::app);
	tProveedor proveedor;

	do {
		system("cls");
		gotoxy(50, 2);
		printf("NUEVO PROVEDOR\n\n");
		getchar();
		gotoxy(40, 4);
		printf("Introduca el nombre del proveedor:\n");
		gotoxy(45, 6);
		cin.getline(proveedor.designacion, MAX_DESIGNACION);
		gotoxy(40, 8);
		printf("Introduzca el numero del proveedor:\n");
		gotoxy(45, 10);
		cin.getline(proveedor.numero, MAX_CHARS);
		gotoxy(40, 12);
		printf("Introduzca el franco:\n");
		gotoxy(45, 14);
		cin.getline(proveedor.franco, MAX_CHARS);
		gotoxy(40, 16);
		printf("Introduzca la cantidad maxima de palets por camion:\n");
		gotoxy(45, 18);
		cin.getline(proveedor.pedMaximo, MAX_CHARS);
		gotoxy(40, 20);
		printf("Introduzca los dias que tardan en servir:\n");
		gotoxy(45, 22);
		cin.getline(proveedor.diasServicio, MAX_CHARS);
		gotoxy(40, 24);
		printf("Introduzca si quiere calcular el pedido por palets o por kilos:\n");
		gotoxy(45, 26);
		cin.getline(proveedor.calculo, MAX_CHARS);
		system("cls");
		gotoxy(40, 10);
		printf("Proveedor guardado con exito\n");
		int nuevaRef = 0;
		gotoxy(40, 12);

		tReferencia referencias;
		
		string nombreArchivo;

		nombreArchivo = proveedor.numero;
		nombreArchivo = nombreArchivo + ".txt";
		
		ofstream archivoref(nombreArchivo, ios::app);

		printf("Pulse 0 si desea introducir una nueva referencia y 1 si desea terminar:\n");
		gotoxy(45, 14);
		scanf_s("%d", &nuevaRef);
		while (nuevaRef != 0 && nuevaRef != 1) {
			gotoxy(40, 16);
			printf("Error de datos. Por favor vuelva a introducir una opcion correcta:\n");
			gotoxy(40, 18);
			printf("Pulse 0 si desea introducir una nueva referencia y 1 si desea terminar:\n");
			gotoxy(45, 20);
			scanf_s("%d", &nuevaRef);
			system("cls");
		}

		while (nuevaRef == 0) {
			system("cls");
			gotoxy(40, 2);
			printf("NUEVA REFERENCIA\n");
			getchar();
			gotoxy(40, 4);
			printf("Introduzca la designacion de la nueva referencia:\n");
			gotoxy(45, 6);
			cin.getline(referencias.designacion, MAX_DESIGNACION);
			gotoxy(40, 8);
			printf("Introduzca el numero de referencia:\n");
			gotoxy(45, 10);
			cin.getline(referencias.numero, MAX_CHARS);
			gotoxy(40, 12);
			printf("Introduzca el condicionante de compra:\n");
			gotoxy(45, 14);
			cin.getline(referencias.codicionante, MAX_CHARS);
			gotoxy(40, 16);
			printf("Introduzca la cantidad de palets maxima que le caben en stock:\n");
			gotoxy(45, 18);
			cin.getline(referencias.facingMaximo, MAX_CHARS);
			gotoxy(40, 20);
			printf("Introduzca la media de ventas mensual:\n");
			gotoxy(45, 22);
			cin.getline(referencias.ventas, MAX_CHARS);
			gotoxy(40, 24);
			archivoref.write((char *) &referencias, sizeof(referencias));
			printf("Referencia guardada con exito\n");
			gotoxy(40, 26);
			printf("Pulse 0 si desea introducir una nueva referencia y 1 si desea terminar:\n");
			gotoxy(45, 28);
			scanf_s("%d", &nuevaRef);
			system("cls");
		}
		archivoref.close();

		gotoxy(40, 14);
		printf("2  -> Atras\n");
		gotoxy(40, 16);
		printf("99 -> Salir\n");
		gotoxy(45, 18);
		printf("Escriba opcion: "); scanf_s("%d", &opcion);

		archivoGuardar.write((char *)&proveedor, sizeof(proveedor));
		archivoGuardar.close();

		switch (opcion) {
		case 2:
			menuPrincipal();
			break;
		case 99:
			exit(1);
			break;
		default:
			gotoxy(40, 24);
			printf("Opcion incorrecta. Vuelva a intentarlo.\n");
			gotoxy(40, 26);
			system("pause");
		}
	}while(a);

}

int buscarProveedor(string numero) { /*función para elegir el proveedor con el que quieres trabajar*/
	struct tProveedor proveedor;
	string bufferNombre;
	int contador = 0;

	ifstream archivoMostrar("proveedores.txt");
	archivoMostrar.read((char *) &proveedor, sizeof(proveedor));

	while (archivoMostrar && !archivoMostrar.eof()) {
		bufferNombre = proveedor.numero;
		contador++;

		archivoMostrar.read((char*)& proveedor, sizeof(proveedor));

		
		if (numero == bufferNombre) {
			gotoxy(45, 10);
			printf("Proveedor encontrado\n");
			gotoxy(50, 12);
			printf("Presione cualquier tecla para continuar\n");
			archivoMostrar.read((char*)& proveedor, sizeof(proveedor));
			return contador;
		}
	}
	archivoMostrar.close();
	return 0;
}

bool proveedorCambiado(int ubicacion) {

	try {
		tProveedor proveedor;
		cin.ignore();
		system("cls");
		gotoxy(45, 4);
		printf("Introduzca nueva designacion:\n");
		gotoxy(50, 6);
		cin.getline(proveedor.designacion, MAX_DESIGNACION);
		gotoxy(45, 8);
		printf("Introduzca nuevo numero de proveedor:\n");
		gotoxy(50, 10);
		cin.getline(proveedor.numero, MAX_CHARS);
		gotoxy(45, 12);
		printf("Introduzca nuevo franco:\n");
		gotoxy(50, 14);
		cin.getline(proveedor.franco, MAX_CHARS);
		gotoxy(45, 16);
		printf("Introduzca la nueva cantidad maxima de palets:\n");
		gotoxy(50, 18);
		cin.getline(proveedor.pedMaximo, MAX_CHARS);
		gotoxy(45, 20);
		printf("Introduzca nueva cantidad de dias que tardan en servir:\n");
		gotoxy(50, 22);
		cin.getline(proveedor.diasServicio, MAX_CHARS);
		gotoxy(45, 24);
		printf("Introduzca si quiere realizar el calculo por palets o por kilos:\n");
		gotoxy(50, 26);
		cin.getline(proveedor.calculo, MAX_CHARS);

		gotoxy(45, 28);
		system("pause");

		fstream archivoCambio("proveedores.txt");
		archivoCambio.seekg((ubicacion-1) *sizeof(proveedor), ios::beg);
		archivoCambio.write((char *) &proveedor, sizeof(proveedor));
		archivoCambio.close();
		return true;
	}
	catch (exception e) {
		printf("\nHa ocurrido un error");
		return false;
	}
}

void referenciaNueva(string nombreArchivo) {
	tReferencia referencias;

	ofstream archivoref(nombreArchivo, ios::app);

	system("cls");
	gotoxy(40, 2);
	printf("NUEVA REFERENCIA\n");
	gotoxy(40, 4);
	printf("Introduzca la designacion de la nueva referencia:\n");
	gotoxy(45, 6);
	cin.getline(referencias.designacion, MAX_DESIGNACION);
	gotoxy(40, 8);
	printf("Introduzca el numero de referencia:\n");
	gotoxy(45, 10);
	cin.getline(referencias.numero, MAX_CHARS);
	gotoxy(40, 12);
	printf("Introduzca el condicionante de compra:\n");
	gotoxy(45, 14);
	cin.getline(referencias.codicionante, MAX_CHARS);
	gotoxy(40, 16);
	printf("Introduzca la cantidad de palets maxima que le caben en stock:\n");
	gotoxy(45, 18);
	cin.getline(referencias.facingMaximo, MAX_CHARS);
	gotoxy(40, 20);
	printf("Introduzca la media de ventas mensual:\n");
	gotoxy(45, 22);
	cin.getline(referencias.ventas, MAX_CHARS);
	gotoxy(40, 24);

	archivoref.write((char*)& referencias, sizeof(referencias));
	printf("Referencia guardada con exito\n");
	gotoxy(40, 26);
	system("pause");
	archivoref.close();
}

void menuModificarDatos() {
	int opcion;
	int a = 1;
	do {
		system("cls");
		gotoxy(54, 2);
		printf("MODIFICAR DATOS\n\n");
		gotoxy(45, 6);
		printf("1  -> Modificar proveedor\n");
		gotoxy(45, 8);
		printf("2  -> Modificar referencia\n");
		gotoxy(45, 10);
		printf("3  -> Nueva referencia\n");
		gotoxy(45, 12);
		printf("4  -> Eliminar proveedor\n");
		gotoxy(45, 14);
		printf("5  -> Eliminar referencia\n");
		gotoxy(45, 16);
		printf("6  -> Atras\n");
		gotoxy(45, 18);
		printf("99  -> Salir\n");

		gotoxy(50, 20);
		printf("Escriba opcion: "); scanf_s("%d", &opcion);

		char designacionBuscada[40];
		int ubicacion = 0;
		char referenciaBuscada[40];

		string nombreArchivo;
		tReferencia referencias;

		switch (opcion) {
		case 1:
			
			system("cls");

			cin.ignore();
			gotoxy(45, 4);
			printf("Introduzca el numero del proveedor que desea modificar:\n");
			gotoxy(50, 6);
			cin.getline(designacionBuscada, MAX_DESIGNACION);
			

			ubicacion = buscarProveedor(designacionBuscada);

			if (ubicacion) {
				if (proveedorCambiado(ubicacion)) {
					system("cls");
					gotoxy(45, 6);
					printf("El proveedor se ha modificado con exito.\n");
					gotoxy(45, 8);
					system("pause");
					a = 0;
				}
				else {
					system("cls");
					gotoxy(45, 6);
					printf("El proveedor no existe en el archivo");
					gotoxy(45, 8);
					system("pause");
					a = 0;
				}
			}
			break;
		case 2:

			system("cls");

			cin.ignore();
			gotoxy(45, 4);
			printf("Introduzca el numero del proveedor que desea modificar:\n");
			gotoxy(50, 6);
			cin.getline(designacionBuscada, MAX_DESIGNACION);
			gotoxy(45, 8);
			printf("Introduzca el numero de referencia que desea modificar:\n");
			gotoxy(50, 10);
			cin.getline(referenciaBuscada, MAX_CHARS);


			ubicacion = buscarReferencia(referenciaBuscada, designacionBuscada);

			if (ubicacion) {
				if (referenciaCambiada(ubicacion, designacionBuscada)) {
					system("cls");
					gotoxy(45, 6);
					printf("La referencia se ha modificado con exito.\n");
					gotoxy(45, 8);
					system("pause");
					a = 0;
				}
				else {
					system("cls");
					gotoxy(45, 6);
					printf("La referencia no existe en el archivo");
					gotoxy(45, 8);
					system("pause");
					a = 0;
				}
			}

			break;

		case 3:
			
			system("cls");
			gotoxy(40, 4);
			printf("Introduzca el proveedor de la nueva referencia\n");
			gotoxy(45, 6);
			cin.getline(designacionBuscada, MAX_DESIGNACION);
			
			nombreArchivo = designacionBuscada;
			nombreArchivo = nombreArchivo + ".txt";

			referenciaNueva(nombreArchivo);
			
			break;
		case 4:
			enConstruccion();
			break;
		case 5:
			enConstruccion();
			break;
		case 6:
			a = 0;
			break;
		case 99:
			exit(1);
			break;
		default:
			gotoxy(40, 26);
			printf("Opcion incorrecta. Vuelva a intentarlo.\n");
			gotoxy(40, 28);
			system("pause");
		}
	} while (a);
}

void menuVerProveedor() {
	int opcion;
	int a = 1;

	do {
		tProveedor proveedor;

		ifstream archivoMostrar("proveedores.txt");
		system("cls");
		archivoMostrar.read((char*)& proveedor, sizeof(proveedor));

		gotoxy(50, 2);
		printf("LISTA DE PROVEEDORES\n");
		gotoxy(15, 4);
		printf("| DESIGNACION                            |  NUMERO  | FRANCO | DIAS SERV | PED MAX |   CALCULO   |\n");

		while (archivoMostrar && !archivoMostrar.eof()) {

			cout << "\n\t\t" << left << setw(40) << proveedor.designacion << "   " << left << setw(10) << proveedor.numero << " " << left << setw(7) << proveedor.franco << " " << left << setw(12)
				<< proveedor.diasServicio << " " << left << setw(10) << proveedor.pedMaximo << " " << left << setw(6) << proveedor.calculo << endl;
			archivoMostrar.read((char*)& proveedor, sizeof(proveedor));
		}
		archivoMostrar.close();
		gotoxy(45, 24);
		printf("2  -> Atras\n");
		gotoxy(45, 26);
		printf("99 -> Salir\n");
		
		gotoxy(50, 28);
		printf("Escriba opcion: "); scanf_s("%d", &opcion);

		switch (opcion) {
		case 2:
			a = 0;
			break;
		case 99:
			exit(1);
			break;
		default:
			gotoxy(45, 24);
			printf("Opcion incorrecta. Vuelva a intentarlo.\n");
			gotoxy(45, 26);
			system("pause");
		}
	} while (a);
}

void menuVerReferencia() {
	int opcion;
	int a = 1;
	int b = 1;

	char amostrar[8];
	tProveedor proveedor;
	tReferencia referencias;
	string nombrearchivo;

	do {
		system("cls");
		gotoxy(50, 2);
		printf("LISTA DE PROVEEDORES\n\n");
		printf("\t\t| PROVEEDOR                              | NUMERO |\n");

		ifstream archivoMostrar("proveedores.txt");
		archivoMostrar.read((char*)& proveedor, sizeof(proveedor));
		
		while (archivoMostrar && !archivoMostrar.eof()) {
			cout << "\n\t\t" << left << setw(40) << proveedor.designacion << "   " << left << setw(10) << proveedor.numero << " " << endl;
			archivoMostrar.read((char*)& proveedor, sizeof(proveedor));
		}
		archivoMostrar.close();

		cin.ignore();
		gotoxy(45, 26);
		printf("Elija el proveedor que quiere consultar\n");
		gotoxy(50, 28);
		cin.getline(amostrar, MAX_CHARS);

		nombrearchivo = amostrar;
		nombrearchivo = nombrearchivo + ".txt";

		ifstream archivoMostrar2(nombrearchivo);
		system("cls");

		if (!archivoMostrar2) {
			gotoxy(40, 6);
			printf("El proveedor no existe en la base de datos\n");
			gotoxy(40, 10);
			printf("Por favor, vuelva a intentarlo\n");
			gotoxy(45, 26);
			system("pause");
			a = 0;
			break;
		}

		archivoMostrar2.read((char*)& referencias, sizeof(referencias));
		system("cls");
		gotoxy(50, 2);
		printf("LISTA DE REFERENCIAS\n");
		gotoxy(15, 4);
		printf("| DESIGNACION                            |  NUMERO  | CONDICIONANTE | FACING | VENTAS |\n");

		while (archivoMostrar2 && !archivoMostrar2.eof()) {
			cout << "\n\t\t" << left << setw(40) << referencias.designacion << "   " << left << setw(12) << referencias.numero << " " << left << setw(14) << referencias.codicionante << " " << left << setw(6)
				<< referencias.facingMaximo << " " << left << setw(10) << referencias.ventas << endl;
			archivoMostrar2.read((char*)& referencias, sizeof(referencias));
		}
		archivoMostrar2.close();

		gotoxy(45, 28);
		printf("2  -> Atras\n");
		gotoxy(45, 30);
		printf("99 -> Salir\n");
		gotoxy(50, 32);
		printf("Escriba opcion: "); scanf_s("%d", &opcion);

		switch (opcion) {
		case 2:
			b = 0;
			break;
		case 99:
			exit(1);
			break;
		default:
			gotoxy(40, 24);
			printf("Opcion incorrecta. Vuelva a intentarlo.\n");
			gotoxy(40, 26);
			system("pause");
			b = 0;
		}
	} while (b);
}

void enConstruccion() {
	int opcion;
	int b = 1;

	do {
		system("cls");
		gotoxy(35, 4);
		printf("Seccion en construccion. Disculpen las molestias.\n");
		gotoxy(45, 10);
		printf("2  -> Atras\n");
		gotoxy(45, 12);
		printf("99 -> Salir\n");
		gotoxy(50, 20);
		printf("Escriba opcion: "); scanf_s("%d", &opcion);
		switch (opcion) {
		case 2:
			b = 0;
			break;
		case 99:
			exit(1);
			break;
		default:
			gotoxy(40, 24);
			printf("Opcion incorrecta. Vuelva a intentarlo.\n");
			gotoxy(40, 26);
			system("pause");
		}
	} while (b);
	
}