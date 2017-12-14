#include <string.h>
#include <iomanip>

using namespace std;

struct Cliente {
	
	char cedula[14];
	char nombre[25];
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
    	return os << setw(14) << left << cliente.cedula << "\t" << setw(25) << left << cliente.nombre << "\t" << setw(14) << left << cliente.edad << "\t" << cliente.tiempoLicencia << "\n";
	}
	
};

Cliente *clientePrimero = NULL;

void agregarCliente(string cedula, string nombre, int edad, int tiempoLicencia) {
	
	Cliente *clienteNuevo;
    Cliente *clienteUltimo = clientePrimero;

    clienteNuevo = (Cliente*)malloc(sizeof(Cliente));
	strcpy(clienteNuevo->cedula, cedula.c_str());
	strcpy(clienteNuevo->nombre, nombre.c_str());
	clienteNuevo->edad = edad;
	clienteNuevo->tiempoLicencia = tiempoLicencia;
	clienteNuevo->siguienteCliente  = NULL;
	
	if (clientePrimero == NULL) {
        clientePrimero = clienteNuevo;
    }
    else {
        while (clienteUltimo->siguienteCliente != NULL) {
            clienteUltimo = clienteUltimo->siguienteCliente;
        }
        clienteUltimo->siguienteCliente = clienteNuevo;
    }
}
