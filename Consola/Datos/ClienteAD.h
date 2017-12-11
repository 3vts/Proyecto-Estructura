#include <cstring>
#include <vector>
#include <stdexcept>
#include "sqlite3.h"
#include "..\Entidades\ClienteEN.h"

#define DB "db.sqlite3"

using namespace std;

sqlite3 *db;
char *error;

void insertarCliente(Cliente cliente) {
	try {
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;
		
		const char *sqlInsert = "INSERT INTO Clientes VALUES(?, ?, ?, ?)";
		
		int result = sqlite3_prepare(db, sqlInsert, strlen(sqlInsert), &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));
		
		sqlite3_bind_text(compiledStatement, 1, cliente.cedula, strlen(cliente.cedula), 0);
		sqlite3_bind_text(compiledStatement, 2, cliente.nombre, strlen(cliente.nombre), 0);
		sqlite3_bind_int(compiledStatement, 3, cliente.edad);
		sqlite3_bind_int(compiledStatement, 4, cliente.tiempoLicencia);
		
		sqlite3_step(compiledStatement);
		sqlite3_finalize(compiledStatement);
		
	} catch (const exception& ex) {
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

void modificarCliente(Cliente cliente){
	try {
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;
		
		const char *sqlUpdate = "UPDATE Clientes SET nombre = ?, edad = ?, tiempo_licencia = ? WHERE cedula = ?";
		
		int result = sqlite3_prepare(db, sqlUpdate, strlen(sqlUpdate), &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));
		
		sqlite3_bind_text(compiledStatement, 1, cliente.nombre, strlen(cliente.nombre), 0);
		sqlite3_bind_int(compiledStatement, 2, cliente.edad);
		sqlite3_bind_int(compiledStatement, 3, cliente.tiempoLicencia);
		sqlite3_bind_text(compiledStatement, 4, cliente.cedula, strlen(cliente.cedula), 0);
		
		sqlite3_step(compiledStatement);
		sqlite3_finalize(compiledStatement);
	
	} catch (const exception& ex) {
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

int eliminarCliente(string cedula){
	try {
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;

		const char *sqlInsert = "DELETE FROM Clientes WHERE Cedula = ?";
		int result = sqlite3_prepare(db, sqlInsert, strlen(sqlInsert), &compiledStatement, 0);
		if(result) throw invalid_argument(sqlite3_errmsg(db));

		sqlite3_bind_text(compiledStatement, 1, cedula.c_str(), strlen(cedula.c_str()), 0);
		
		sqlite3_step(compiledStatement);
		sqlite3_finalize(compiledStatement);
		
	} catch (const exception& ex) {
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

void crearTabla(){
	try {
		sqlite3_open(DB, &db);
		
		const char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS Clientes (cedula STRING PRIMARY KEY, nombre STRING,  edad INTEGER, tiempo_licencia INTEGER);";
		
		int result = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);
		if(result) throw invalid_argument(error);
		
		sqlite3_close(db);
		
	} catch (const exception& ex) {
		sqlite3_free(error);
		throw invalid_argument(ex.what());
	}
}

void eliminarTabla(){
	try {
		sqlite3_open(DB, &db);
		
		const char *sqlDropTable = "DROP TABLE IF EXISTS Clientes";
		
		int result = sqlite3_exec(db, sqlDropTable, NULL, NULL, &error);
		if(result) throw invalid_argument(error);
		
		sqlite3_close(db);
	}
	catch (const exception& ex) {
		sqlite3_free(error);
		throw invalid_argument(ex.what());
	}
}

Cliente obtenerClientePorCedula(string cedula) {
	try {
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;
		
		const char *sqlSelect = "SELECT * FROM Clientes WHERE cedula = ?";
		
		
		int result =  sqlite3_prepare(db, sqlSelect, -1, &compiledStatement, 0);
		if(result) throw invalid_argument(error);
		
		sqlite3_bind_text(compiledStatement, 1, cedula.c_str(), strlen(cedula.c_str()), 0);
		int res = sqlite3_step(compiledStatement);
		
		if (res == SQLITE_ROW) {
            string cedula = (char*)sqlite3_column_text(compiledStatement, 0);
            string nombre = (char*)sqlite3_column_text(compiledStatement, 1);
            int edad = sqlite3_column_int(compiledStatement, 2);
            int tiempoLicencia = sqlite3_column_int(compiledStatement, 3);
            Cliente cliente = Cliente(cedula, nombre, edad, tiempoLicencia);
            return cliente;
        } else {
        	throw invalid_argument("Cliente no existe");
		}
        
		sqlite3_close(db);
		
	} catch (const exception& ex) {
		sqlite3_close(db);
		throw invalid_argument(ex.what());
	}
}

void obtenerTodosLosClientes() {
	try	{
		sqlite3_open(DB, &db);
		sqlite3_stmt *compiledStatement;
		
		const char *sqlSelect = "SELECT * FROM Clientes";
		
		int result =  sqlite3_prepare(db, sqlSelect, -1, &compiledStatement, 0);
		if(result) throw invalid_argument(error);
	
		int res = sqlite3_step(compiledStatement);
		
		while (res == SQLITE_ROW) {
            string cedula = (char*)sqlite3_column_text(compiledStatement, 0);
            string nombre = (char*)sqlite3_column_text(compiledStatement, 1);
            int edad = sqlite3_column_int(compiledStatement, 2);
            int tiempoLicencia = sqlite3_column_int(compiledStatement, 3);
            Cliente cliente = Cliente(cedula, nombre, edad, tiempoLicencia);
            cout << cliente;
            res = sqlite3_step(compiledStatement);
        }
		sqlite3_close(db);
		
	}
	catch (const exception& ex) {
		sqlite3_free(error);
		throw invalid_argument(ex.what());
	}
}

