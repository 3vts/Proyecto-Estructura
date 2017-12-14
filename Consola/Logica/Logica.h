#include <string>
#include "..\Datos\ClienteAD.h"
#include "..\Datos\SeguroAD.h"

#define MONTOBASE 100000

bool validaCliente (string cedula) {
	try {
		Cliente cliente = obtenerClientePorCedula(cedula);
		return true;
	} catch (const exception& ex){
		return false;
	}
}

bool validaSeguro (string cedula) {
	try {
		return obtenerSeguroPorCedula(cedula);
	} catch (const exception& ex){
		return false;
	}
}

int calculaAnios(int anio){
	return abs(2017 - anio);
}

int calculaSeguro(int edad, int tiempoLicencia, int tipoAuto) {
	int montoAnual = MONTOBASE;
	if (edad < 20) {
		montoAnual = montoAnual + montoAnual * 0.25;
	} else if (edad >= 20 & edad < 30) {
		montoAnual = montoAnual + montoAnual * 0.1;
	} else if (edad > 65) {
		montoAnual = montoAnual + montoAnual * 0.15;
	}
	if (tiempoLicencia < 2){
		montoAnual = montoAnual + montoAnual * 0.1;
	} else if (tiempoLicencia >= 2 & tiempoLicencia < 5) {
		montoAnual = montoAnual + montoAnual * 0.08;
	} else {
		montoAnual = montoAnual + montoAnual * 0.05;
	}
	if (tipoAuto == 2){
		montoAnual = montoAnual + montoAnual * 0.05;
	}
	return montoAnual;
}
