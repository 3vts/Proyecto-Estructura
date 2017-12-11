#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "..\Datos\ClienteAD.h"
#include "..\Datos\SeguroAD.h"

using namespace std;

Cliente cliente = Cliente("111920241", "Alvaro Alfaro Santiesteban", 34, 0);
Seguro seguro = Seguro("111920241", "Sedan", 12892374);

int main()
{
	try{
		eliminarTabla();
		crearTabla();
		insertarCliente(cliente);
		strcpy(cliente.nombre, "Modificado");
		modificarCliente(cliente);
		Cliente test = obtenerClientePorCedula("111920241");
		cout << test;
		//eliminarCliente("111920241");
		//cout << cliente;
		//cout << "\n" << seguro;
		//obtenerTodosLosClientes();
	} catch (const exception& ex) {
		cout << ex.what();
	}
	    
}
