#ifndef CLAVE_ERRONEA_H
#define CLAVE_ERRONEA_H

#include <QDialog>
#include <string>


using namespace std;

namespace Ui {
class clave_erronea;
}
/**
 * @brief The clave_erronea class se define como una ventana de dialogo, en los atributos publicos se define
 * el constructor y destructor de la clase y en los atributos privados la ventana
 */
class clave_erronea : public QDialog
{
    Q_OBJECT

public:
    explicit clave_erronea(QWidget *parent = 0);
    ~clave_erronea();

private:
    Ui::clave_erronea *ui;
};

#endif // CLAVE_ERRONEA_H
