#include <string.h>
#include <iomanip>

using namespace std;

struct Seguro {
	
	char cedula[14];
	char tipoAuto[20];
	int montoAnual;
	Seguro *siguienteSeguro;
	
	Seguro(string cedula, string tipoAuto, int montoAnual) {
		strcpy(this->cedula, cedula.c_str());
		strcpy(this->tipoAuto, tipoAuto.c_str());
		this->montoAnual = montoAnual;
		this->siguienteSeguro  = NULL;
	}
	
	friend ostream& operator<<(ostream& os, const Seguro& seguro) {
    	return os << setw(14)  << left << seguro.cedula << "\t" << setw(20)  << left << seguro.tipoAuto << "\t"  << seguro.montoAnual << "\n";
	}
	
};

Seguro *seguroPrimero = NULL;

void agregarSeguro(string cedula, string tipoAuto, int montoAnual) {
	Seguro *seguroNuevo;
    Seguro *seguroUltimo = seguroPrimero;

    seguroNuevo = (Seguro*)malloc(sizeof(Seguro));
	strcpy(seguroNuevo->cedula, cedula.c_str());
	strcpy(seguroNuevo->tipoAuto, tipoAuto.c_str());
	seguroNuevo->montoAnual = montoAnual;
	seguroNuevo->siguienteSeguro  = NULL;
	
	if (seguroPrimero == NULL) {
        seguroPrimero = seguroNuevo;
    }
    else {
        while (seguroUltimo->siguienteSeguro != NULL) {
            seguroUltimo = seguroUltimo->siguienteSeguro;
        }
        seguroUltimo->siguienteSeguro = seguroNuevo;
    }
}

void limpiaListaSeguro(Seguro *seguro) {
	while(seguro) {
		Seguro *seguroAnterior = seguro;
		seguro = seguro->siguienteSeguro;
		free(seguro);
	}
}
