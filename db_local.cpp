#include "db_local.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <sqlite3.h>
/**
 * @brief DB_Local::DB_Local
 */
DB_Local::DB_Local()
{

}
/**
 * @brief DB_Local::abrirDB
 * @param path
 * @return
 */
bool DB_Local::abrirDB(string path){
    char *zErrMsg = 0;
    int rc;

    /* Open database */
    rc = sqlite3_open( path.c_str() , &db);

    if( rc ) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return false;
    }else
        fprintf(stderr, "Opened database successfully\n");

    return true;

}
/**
 * @brief DB_Local::almacenarUsuario
 * @param nombreUsuario
 * @param password
 * @param Nombre
 * @param apellido
 * @param documento
 * @param edad
 * @return
 */
bool DB_Local::almacenarUsuario(string nombreUsuario, string password,  string Nombre, string apellido, int documento, int edad){

    char *zErrMsg = 0;
    int rc;

    std::stringstream sql;
    sql << "INSERT INTO usuario(nombreUS, password, Nombre, Apellido, Documento, Edad) VALUES ('" ;
    sql << nombreUsuario << "', '" <<  password << "', '" << Nombre <<"','"<<apellido<<"',"<< documento<<","<<edad <<");" ;

    std::cout << sql.str() << std::endl;

    rc = sqlite3_exec(db, sql.str().c_str(), 0, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       return false;
    } else {
       //fprintf(stdout, "Records created successfully\n");
    }
    return true;
}
/**
 * @brief DB_Local::almacenarPaciente
 * @param Nombre
 * @param apellido
 * @param edad
 * @param documento
 * @param ingresos
 * @param genero
 * @param raza
 * @return
 */
bool DB_Local::almacenarPaciente(string Nombre, string apellido, int edad, int documento, string ingresos ,string genero,string raza){

    char *zErrMsg = 0;
    int rc;

    std::stringstream sql;
    sql << "INSERT INTO pacientes(Nombre, Apellido, Edad, Documento, Genero, Raza, Ingresos) VALUES ('" ;
    sql << Nombre <<"','"<< apellido <<"',"<< edad <<","<< documento <<",'"<< genero <<"','"<< raza <<"','"<<ingresos<<"');";

    std::cout << sql.str() << std::endl;

    rc = sqlite3_exec(db, sql.str().c_str(), 0, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       return false;
    } else {
       //fprintf(stdout, "Records created successfully\n");
    }
    return true;
}
/**
 * @brief DB_Local::cerrarDB
 * @return
 */
bool DB_Local::cerrarDB(){
    sqlite3_close( db );
}
/**
 * @brief DB_Local::funcionLlamadaU
 * @param data
 * @param argc
 * @param argv
 * @param azColName
 * @return
 */
int DB_Local::funcionLlamadaU(void* data,int argc, char **argv, char **azColName){
    char* cont = (char* ) data;
    return strcmp (cont,argv[1]);
}
/**
 * @brief DB_Local::compararDatosUsuario
 * @param nombreUsuario
 * @param contrasena
 * @return
 */
bool DB_Local::compararDatosUsuario(string nombreUsuario, string contrasena){
    char *zErrMsg = 0;
    int rc;

    std::string sql = "SELECT nombreUS, password FROM usuario WHERE nombreUS=('";
    sql+=nombreUsuario;
    sql+="');";
    rc = 1 ;

    char * cstr = new char [contrasena.length()+1];
    std::strcpy (cstr, contrasena.c_str());


    rc = sqlite3_exec(db, sql.c_str(), funcionLlamadaU, (void* ) cstr, &zErrMsg);

    if( rc != 0 ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       return false;
    }
    return true;
}
