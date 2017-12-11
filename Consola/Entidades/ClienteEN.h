#include <string.h>

using namespace std;

struct Cliente {
	
	char cedula[14];
	char nombre[50];
	int edad;
	int tiempoLicencia;
	Cliente *siguienteCliente;
	
	Cliente(string cedula, string nombre, int edad, int tiempoLicencia) {
		strcpy(this->cedula, cedula.c_str());
		strcpy(this->nombre, nombre.c_str());
		this->edad = edad;
		this->tiempoLicencia = tiempoLicencia;
		this->siguienteCliente  = NULL;
	}
	
	friend ostream& operator<<(ostream& os, const Cliente& cliente) {
    	return os << cliente.cedula << "\t" << cliente.nombre << "\t" << cliente.edad << "\t" << cliente.tiempoLicencia;
	}
	
};

Cliente *clientePrimero = NULL;
