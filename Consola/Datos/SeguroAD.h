#include <cstring>
#include <vector>
#include <stdexcept>
#include "sqlite3.h"
#include "..\Entidades\SeguroEN.h"

#define DB "db.sqlite3"

using namespace std;

void insertarSeguro(Seguro seguro) {
	sqlite3 *db;
	try {
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;
		
		const char *sqlInsert = "INSERT INTO Seguros VALUES(?, ?, ?)";
		
		int result = sqlite3_prepare(db, sqlInsert, strlen(sqlInsert), &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));
		
		sqlite3_bind_text(compiledStatement, 1, seguro.cedula, strlen(seguro.cedula), 0);
		sqlite3_bind_text(compiledStatement, 2, seguro.tipoAuto, strlen(seguro.tipoAuto), 0);
		sqlite3_bind_int(compiledStatement, 3, seguro.montoAnual);
		
		sqlite3_step(compiledStatement);
		sqlite3_finalize(compiledStatement);
		
	} catch (const exception& ex) {
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

void modificarSeguro(Seguro seguro){
	sqlite3 *db;
	try {
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;
		
		const char *sqlUpdate = "UPDATE Seguros SET tipo_auto = ?, monto_anual = ? WHERE Cedula = ?";
		
		int result = sqlite3_prepare(db, sqlUpdate, strlen(sqlUpdate), &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));
		
		sqlite3_bind_text(compiledStatement, 1, seguro.cedula, strlen(seguro.cedula), 0);
		sqlite3_bind_text(compiledStatement, 2, seguro.tipoAuto, strlen(seguro.tipoAuto), 0);
		sqlite3_bind_int(compiledStatement, 3, seguro.montoAnual);
		
		sqlite3_step(compiledStatement);
		sqlite3_finalize(compiledStatement);
	
	} catch (const exception& ex) {
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

int eliminarSeguro(string cedula){
	sqlite3 *db;
	try {
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;

		const char *sqlDelete = "DELETE FROM Seguros WHERE Cedula = ?";
		int result = sqlite3_prepare(db, sqlDelete, strlen(sqlDelete), &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));

		sqlite3_bind_text(compiledStatement, 1, cedula.c_str(), strlen(cedula.c_str()), 0);
		
		sqlite3_step(compiledStatement);
		sqlite3_finalize(compiledStatement);
		
	} catch (const exception& ex) {
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

void crearTablaSeguro(){
	sqlite3 *db;
	char *error;
	try {
		sqlite3_open(DB, &db);
		
		const char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS Seguros (cedula STRING, tipo_auto STRING,  monto_anual INTEGER)";
		
		int result = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);
		if(result) throw invalid_argument(error);
		
		sqlite3_close(db);
		
	} catch (const exception& ex) {
		sqlite3_free(error);
		throw invalid_argument(ex.what());
	}
}

void eliminarTablaSeguro(){
	sqlite3 *db;
	char *error;
	try {
		sqlite3_open(DB, &db);
		
		const char *sqlDropTable = "DROP TABLE IF EXISTS Seguros";
		
		int result = sqlite3_exec(db, sqlDropTable, NULL, NULL, &error);
		if(result) throw invalid_argument(error);
		
		sqlite3_close(db);
	}
	catch (const exception& ex) {
		sqlite3_free(error);
		throw invalid_argument(ex.what());
	}
}

bool obtenerSeguroPorCedula(string cedula) {
	sqlite3 *db;
	sqlite3_stmt *compiledStatement;
	bool seguros = false;
	try {
		sqlite3_open(DB, &db);
		
		const char *sqlSelect = "SELECT * FROM Seguros WHERE cedula = ?";
		
		
		int result =  sqlite3_prepare(db, sqlSelect, -1, &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));
		
		sqlite3_bind_text(compiledStatement, 1, cedula.c_str(), strlen(cedula.c_str()), 0);
		int res = sqlite3_step(compiledStatement);
		
		while (res == SQLITE_ROW) {
            string cedula = (char*)sqlite3_column_text(compiledStatement, 0);
            string tipo_auto = (char*)sqlite3_column_text(compiledStatement, 1);
            int monto_anual = sqlite3_column_int(compiledStatement, 2);
            agregarSeguro(cedula, tipo_auto, monto_anual);
            res = sqlite3_step(compiledStatement);
            seguros = true;
        }
        sqlite3_finalize(compiledStatement);
		sqlite3_close(db);
		return seguros;
        
	} catch (const exception& ex) {
		sqlite3_finalize(compiledStatement);
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

void obtenerTodosLosSeguros() {
	sqlite3 *db;
	sqlite3_stmt *compiledStatement;
	try	{
		sqlite3_open(DB, &db);
		
		const char *sqlSelect = "SELECT * FROM Seguros";
		
		int result =  sqlite3_prepare(db, sqlSelect, -1, &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));
	
		int res = sqlite3_step(compiledStatement);
		
		while (res == SQLITE_ROW) {
            string cedula = (char*)sqlite3_column_text(compiledStatement, 0);
            string tipo_auto = (char*)sqlite3_column_text(compiledStatement, 1);
            int monto_anual = sqlite3_column_int(compiledStatement, 2);
            agregarSeguro(cedula, tipo_auto, monto_anual);
            res = sqlite3_step(compiledStatement);
        }
        sqlite3_finalize(compiledStatement);
		sqlite3_close(db);
		
	}
	catch (const exception& ex) {
		sqlite3_finalize(compiledStatement);
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}
