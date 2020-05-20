#ifndef FORMULARIO_USUARIO_H
#define FORMULARIO_USUARIO_H

#include <QDialog>
#include <string>
#include <QDate>
#include "mainwindow.h"
#include "clave_erronea.h"

using namespace std;

namespace Ui {
class formulario_usuario;
}
/**
 * @brief The formulario_usuario class se defiene como una ventana de dialogo en sus atributos publicos se encuentra el
 * constructor y destructor de la clase, en signals, en esta clase se tienen dos señales una para enviar los datos del usuario
 * nuevo y comparar y la otra para enviar los datos de un usuario nuevo, en sus slots se tienen dos opciones de ingreso uno
 * con el boton "OK" y otro con el boton "registra usuario" y  en sus atributos privados se define la clave del
 * administrador para no dejar registrar cualquier usuario y la definicion del ui
 */
class formulario_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit formulario_usuario(QWidget *parent = 0);
    ~formulario_usuario();
signals:
    void enviarDatos( string username, string usrpassword );

    void envioDatosUsuarioNew(string usernameN,string nameN,string apellidoN,string passwordN,int docIdN,int dayNR,int monthNR,int yearNR,bool aceptadoUs); //falta fecha

private slots:
    void on_buttonBox_accepted();

    void on_cdm_RegUsr_clicked();

private:
    Ui::formulario_usuario *ui;

    string claveAdmin = "123";
};

#endif // FORMULARIO_USUARIO_H
