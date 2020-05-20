#ifndef FORMULARIO_PACIENTE_H
#define FORMULARIO_PACIENTE_H

#include <QDialog>
#include <string>
#include <QButtonGroup>
#include <QDate>
#include "mainwindow.h"

using namespace std;

namespace Ui {
class formulario_paciente;
}
/**
 * @brief The formulario_paciente class se defiene como una ventana de dialogo, en los atributos publicos se define el
 * constructor y destructor de la clase, en señales se tiene la funcion enviarDatosPnt la cual es necesaria para enviar
 * los datos del paciente, en los slots privados estan las funciones con sus respectivos parametros y se define
 * el boton "OK" o "cancel" y en los atributos privados la ventana
 */

class formulario_paciente : public QDialog
{
    Q_OBJECT

public:
    explicit formulario_paciente(QWidget *parent = 0);
    ~formulario_paciente();

signals:
    void enviarDatosPnt( string nombrePnt,string apellidoPnt,int edad,long docPnt,string generoPnt,string razaPnt,string nivelSEpnt,bool aceptado);

private slots:
    int calcular_edad(int anoN, int mesN, int diaN, int ano_actual, int mes_actual, int dia_actual);

    void on_buttonBox_accepted();

private:
    Ui::formulario_paciente *ui;
};

#endif // FORMULARIO_PACIENTE_H
