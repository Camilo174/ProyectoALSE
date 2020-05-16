#include "clave_erronea.h"
#include "ui_clave_erronea.h"
#include "mainwindow.h"

/**
 * @brief clave_erronea::clave_erronea
 * @param parent
 */

clave_erronea::clave_erronea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clave_erronea)
{
    ui->setupUi(this);
}
/**
 * @brief clave_erronea::~clave_erronea
 */
clave_erronea::~clave_erronea()
{
    delete ui;
}
