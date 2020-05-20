#ifndef DB_LOCAL_H
#define DB_LOCAL_H

#include <string>
#include <sqlite3.h>

using namespace std;

/**
 * @brief The DB_Local class se tiene en cuenta sqlite3 para la base de datos en los atributos privados se definen las funciones
 * llamadas necesarias para comparar las contraseñas y en los atributos publicos se definen las funciones necesarias con sus
 * parametros correspondientes
 */
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
