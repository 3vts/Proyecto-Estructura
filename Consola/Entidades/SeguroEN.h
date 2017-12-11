#include <string.h>

using namespace std;

struct Seguro {
	
	char cedula[14];
	char tipoAuto[50];
	int montoAnual;
	Seguro *siguienteSeguro;
	
	Seguro(string cedula, string tipoAuto, int montoAnual) {
		strcpy(this->cedula, cedula.c_str());
		strcpy(this->tipoAuto, tipoAuto.c_str());
		this->montoAnual = montoAnual;
		this->siguienteSeguro  = NULL;
	}
	
	friend ostream& operator<<(ostream& os, const Seguro& seguro) {
    	return os << seguro.cedula << "\t" << seguro.tipoAuto << "\t" << seguro.montoAnual;
	}
	
};

Seguro *seguroPrimero = NULL;
