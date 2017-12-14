#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "..\Logica\Logica.h"


using namespace std;

void mostrarMenu();
void agregarCliente();
void agregarSeguro();
void mostrarCliente();
void mostrarTodosLosClientes();
void mostrarSegurosDeCliente();
void mostrarTodosLosSeguros();
void eliminarCliente();
void eliminarSeguro();

int main() {
	char opcion;
	
	do {
		mostrarMenu();
		scanf("%i", &opcion);
		switch(opcion) {
			case 1:
				agregarCliente();
				break;
			case 2:
				agregarSeguro();
				break;
			case 3:
				mostrarCliente();
				break;
			case 4:
				mostrarTodosLosClientes();
				break;
			case 5:
				mostrarSegurosDeCliente();
				break;
			case 6:
				mostrarTodosLosSeguros();
				break;
			case 7:
				eliminarCliente();
				break;
			case 8:
				eliminarSeguro();
				break;
			default:
				break;
		} 
	} while (opcion !=9);
}

void mostrarMenu() {
    system("CLS");
    printf("\t***Seguros  Vehiculares***\n");

    printf("1. Ingrese Nuevo Cliente\n");
    printf("2. Ingrese Nuevo Seguro\n");
    printf("3. Mostrar Cliente\n");
    printf("4. Mostrar todos los clientes\n");
    printf("5. Mostrar Seguros de Cliente\n");
    printf("6. Mostrar todos los Seguros\n");
    printf("7. Eliminar Cliente\n");
	printf("8. Eliminar Seguro\n");
    printf("9. Salir\n");
    printf("\nEscoja una opcion: \n");
    fflush(stdin);
}

void agregarCliente() {
	bool clienteExiste = false;
	string cedula;
	string nombre;
	int anioNacimiento;
	int edad;
	int fechaExpedicionLicencia;
	int tiempoLicencia;
	
	do {
		printf("\nIngrese el numero de cedula del cliente:\n");
		cin >> cedula;
		if (validaCliente (cedula)) {
			printf("\nCliente ya existe intente nuevamente\n");
			clienteExiste = true;
		} else {
			clienteExiste = false;
		}
	} while (clienteExiste);
	
	printf("\nIngrese el nombre del cliente:\n");
	cin >> nombre;
	printf("\nIngrese el anio de nacimiento del cliente:\n");
	cin >> anioNacimiento;
	edad = calculaAnios(anioNacimiento);
	printf("\nIngrese la fecha de expedicion de la licencia de cliente:\n");
	cin >> fechaExpedicionLicencia;
	tiempoLicencia = calculaAnios(fechaExpedicionLicencia);
	Cliente cliente = Cliente(cedula, nombre, edad, tiempoLicencia);
	crearTablaCliente();
	insertarCliente(cliente);
	cout << "\n" << setw(14) << left << "Cedula" << "\t" << setw(25) << left << "Nombre" << "\t" << setw(14) << left << "Edad" << "\t" << "Anios de tener licencia" << "\n";
	cout << cliente;
	getch();
}

void agregarSeguro() {
	bool clienteExiste = false;
	string cedula;
	int tipoAuto = 0;
	int montoAnual;
	string tipoAutoStr;
	
	do {
		printf("\nIngrese el numero de cedula del cliente:\n");
		cin >> cedula;
		if (!validaCliente (cedula)) {
			printf("\nCliente no existe intente nuevamente\n");
			clienteExiste = false;
		} else {
			clienteExiste = true;
		}
	} while (!clienteExiste);
	
	do {
		printf("\nSeleccione el tipo de auto a asegurar:\n1. Sedan\n2. Transporte\n");
		scanf("%i", &tipoAuto);
		
	} while (tipoAuto != 1 & tipoAuto != 2);
	
	tipoAutoStr = (tipoAuto == 1) ? "Sedan" : "Transporte";
	Cliente cliente  = obtenerClientePorCedula(cedula);
	montoAnual = calculaSeguro(cliente.edad, cliente.tiempoLicencia, tipoAuto);
	Seguro seguro = Seguro(cedula, tipoAutoStr, montoAnual);
	crearTablaSeguro();
	insertarSeguro(seguro);
	
	cout << "\n" << setw(14)  << left << "Cedula" << "\t" << setw(20)  << left << "Tipo de Auto" << "\t"  << "Monto Anual" << "\n";
	cout << seguro;

	getch();
	
}

void mostrarCliente() {
	string cedula;
	printf("\nIngrese el numero de cedula del cliente:\n");
	cin >> cedula;
	try{
		Cliente cliente = obtenerClientePorCedula(cedula);
		cout << "\n" << setw(14) << left << "Cedula" << "\t" << setw(25) << left << "Nombre" << "\t" << setw(14) << left << "Edad" << "\t" << "Anios de tener licencia" << "\n";
		cout << cliente;
		} catch (const exception& ex) {
		cout << ex.what();
	}
	getch();
}

void mostrarTodosLosClientes() {
	clientePrimero = NULL;
	obtenerTodosLosClientes();
	Cliente *siguiente = clientePrimero;
	cout << "\n" << setw(14) << left << "Cedula" << "\t" << setw(25) << left << "Nombre" << "\t" << setw(14) << left << "Edad" << "\t" << "Anios de tener licencia" << "\n";
	while (siguiente){
		cout << setw(14) << left << siguiente->cedula << "\t" << setw(25) << left << siguiente->nombre << "\t" << setw(14) << left << siguiente->edad << "\t" << siguiente->tiempoLicencia << "\n";
		siguiente = siguiente->siguienteCliente;
	}
	getch();
}

void mostrarSegurosDeCliente() {
	seguroPrimero = NULL;
	bool seguroExiste;
	string cedula;

	do {
		printf("\nIngrese el numero de cedula del cliente:\n");
		cin >> cedula;
		if (!validaSeguro (cedula)) {
			printf("\nCliente no tiene seguros asociados intente nuevamente\n");
			seguroExiste = false;
		} else {
			seguroExiste = true;
		}
	} while (!seguroExiste);
	obtenerSeguroPorCedula(cedula);
	Seguro *siguiente = seguroPrimero;
	cout << "\n" << setw(14) << left << "Cedula" << "\t" << setw(20) << left << "Tipo Auto" << "\t" << setw(14) << left << "Monto Anual" << "\n";
	while (siguiente){
		cout << setw(14)  << left << siguiente->cedula << "\t" << setw(20)  << left << siguiente->tipoAuto << "\t"  << siguiente->montoAnual << "\n";
		siguiente = siguiente->siguienteSeguro;
	}
	getch();
}

void mostrarTodosLosSeguros() {
	seguroPrimero = NULL;
	obtenerTodosLosSeguros();
	Seguro *siguiente = seguroPrimero;
	cout << "\n" << setw(14) << left << "Cedula" << "\t" << setw(20) << left << "Tipo Auto" << "\t" << setw(14) << left << "Monto Anual" << "\n";
	while (siguiente){
		cout << setw(14)  << left << siguiente->cedula << "\t" << setw(20)  << left << siguiente->tipoAuto << "\t"  << siguiente->montoAnual << "\n";
		siguiente = siguiente->siguienteSeguro;
	}
	getch();
}

void eliminarCliente() {
	bool clienteExiste;
	string cedula;
	
	do {
		printf("\nIngrese el numero de cedula del cliente:\n");
		cin >> cedula;
		if (!validaCliente (cedula)) {
			printf("\nCliente no existe intente nuevamente\n");
			clienteExiste = false;
		} else {
			clienteExiste = true;
		}
	} while (!clienteExiste);
	eliminarCliente(cedula.c_str());
	eliminarSeguro(cedula.c_str());
	printf("\nCliente eliminado\n");
	getch();
	
}
void eliminarSeguro() {
	bool seguroExiste;
	string cedula;
	
	do {
		printf("\nIngrese el numero de cedula del cliente:\n");
		cin >> cedula;
		if (!validaSeguro (cedula)) {
			printf("\nCliente no tiene seguros asociados intente nuevamente\n");
			seguroExiste = false;
		} else {
			seguroExiste = true;
		}
	} while (!seguroExiste);
	eliminarSeguro(cedula.c_str());
	printf("\nSeguros eliminados\n");
	getch();
}
