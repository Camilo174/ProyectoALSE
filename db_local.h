#ifndef DB_LOCAL_H
#define DB_LOCAL_H

#include <string>
#include <sqlite3.h>

using namespace std;

class DB_Local{
private:
    sqlite3 *db;

    static int funcionLlamadaU(void *data, int argc, char **argv, char **azColName);
    static int funcionLlamadaU1(void *data, int argc, char **argv, char **azColName);

public:
    DB_Local();
    bool almacenarPaciente(string Nombre, string apellido, int edad, int documento, string genero, string raza, string ingresos);
    bool abrirDB( string path );
    int compararDatosUsuario( string nombreUsuario, string contrasena );
    bool almacenarUsuario( string nombreUsuario, string password,  string Nombre, string apellido, int documento, int edad);
    bool cerrarDB();
};

#endif // DB_LOCAL_H
