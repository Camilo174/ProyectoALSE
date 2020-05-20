#include "clave_erronea.h"
#include "ui_clave_erronea.h"
#include "mainwindow.h"

/**
 * @brief clave_erronea::clave_erronea es una ventana de dialogo la cual va a aparecer si el usuario o
 * la contraseña son incorrectos o cuando la clave del administrador para ingresar un usuario nuevo es incorrecta
 * a la guardada por el sistema
 * @param parent
 */

clave_erronea::clave_erronea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clave_erronea)
{
    ui->setupUi(this);
}
/**
 * @brief clave_erronea::~clave_erronea es el destructor de la clase
 */
clave_erronea::~clave_erronea()
{
    delete ui;
}
