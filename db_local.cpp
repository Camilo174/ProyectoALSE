#include "db_local.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <sqlite3.h>
/**
 * @brief DB_Local::DB_Local es el constructor de la clase
 */
DB_Local::DB_Local()
{

}
/**
 * @brief DB_Local::abrirDB abre la base de datos
 * @param path es el archivo de la base de datos
 * @return true si puede abrir la base de datos o false si no puede abrir la base de datos y un mensaje en la pantalla
 */
bool DB_Local::abrirDB(string path){
    char *zErrMsg = 0;
    int rc;

    /**
     * abre la base de datos
    */
    rc = sqlite3_open( path.c_str() , &db);

    if( rc ) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return false;
    }else
        fprintf(stderr, "Opened database successfully\n");

    return true;

}
/**
 * @brief DB_Local::almacenarUsuario  con esta funcion se guarda los datos del usuario nuevo en la base de datos
 * @param nombreUsuario: el nombre con el cual el usuario va a poder iniciar sesion
 * @param password: la clave del usuario
 * @param Nombre: nombre del usuario
 * @param apellido: apellido del usuario
 * @param documento: documento del paciente
 * @param edad: edad del paciente
 * @return true si puede almacenar correctamente los datos y false si no puede almacenar los datos
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
 * @brief DB_Local::almacenarPaciente con esta funcion se guarda los datos del paciente en la base de datos respectiva
 * @param Nombre: nombre del paciente
 * @param apellido: apellido del paciente
 * @param edad: edad del paciente
 * @param documento: documento del paciente
 * @param ingresos: nivel de ingresos del paciente
 * @param genero: genero del paciente
 * @param raza: raza del paciente
 * @return true si puede guardar correctamente los datos del paciente en la base de datos o false si no puede guardar la informacion
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
 * @brief DB_Local::cerrarDB esta funcion cierra la base de datos
 * @return
 */
bool DB_Local::cerrarDB(){
    sqlite3_close( db );
}
/**
 * @brief DB_Local::funcionLlamadaU  esta funcion me sirve para comparar si la contraseña ingresada es la misma que la que esta
 * en la base de datos es decir si es correcta
 * @param data
 * @param argc
 * @param argv
 * @param azColName
 * @return 0 si es correcta la contraseña o un valor diferente de 0 si es incorrecta
 */
int DB_Local::funcionLlamadaU(void* data,int argc, char **argv, char **azColName){
    char* cont = (char* ) data;
    if (strcmp (cont,argv[1])!=0){
        return 10;
    }
    return 0 ;
}
/**
 * @brief DB_Local::funcionLlamadaU1  esta funcion me sirve para saber si la contraseña es la misma que la que esta
 * en la base de datos, pero esta funcion fue creada para solucionar un error que se encontro al ingresar un usuario
 * no existente en la base de datos
 * @param data
 * @param argc
 * @param argv
 * @param azColName
 * @return 0 si el usuario no existe
 */
int DB_Local::funcionLlamadaU1(void* data,int argc, char **argv, char **azColName){
    char* cont = (char* ) data;
    if (strcmp (cont,argv[1])!=0){
        return 4;
    }
    return 1;
}
/**
 * @brief DB_Local::compararDatosUsuario esta funcion se le pasan los nombres de usuario y la contraseña que se ingreso
 * si el usuario ya esta registrado para comparar que estos datos esten en la base de datos
 * @param nombreUsuario nombre de usuario ingresado por el usuario para comparar que este en la base de datos
 * @param contrasena contraseña del usuario
 * despues de verificar que este el nombre de usuario en la base de datos se llama la funcion llamada u para comparar las contraseñas
 * @return 1 si el nombre de usuario no esta bien 2  si la contraseña es incorrecta y 0 si los datos son correctos
 */
int DB_Local::compararDatosUsuario(string nombreUsuario, string contrasena){
    char *zErrMsg = 0;
    int rc;
    rc = 1 ;
    std::string sql = "SELECT nombreUS, password FROM usuario WHERE nombreUS=('";
    sql+=nombreUsuario;
    sql+="');";
    char * cstr = new char [contrasena.length()+1];
    std::strcpy (cstr, contrasena.c_str());
    rc = sqlite3_exec(db, sql.c_str(), funcionLlamadaU1,(void* ) cstr, &zErrMsg);
    if(rc==0){
        return 1;
    }

    rc = sqlite3_exec(db, sql.c_str(), funcionLlamadaU, (void* ) cstr, &zErrMsg);
    if( rc != 0 ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       return 2;
    }
    else{
      return 0;
    }

}
