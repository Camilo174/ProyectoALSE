#include "formulario_usuario.h"
#include "ui_formulario_usuario.h"
#include "formulario_paciente.h"
#include "mainwindow.h"

/**
 * @brief formulario_usuario::formulario_usuario es el constructor de la clase
 * @param parent es una ventana de dialogo la cual se va a habilitar desde el mainwindow con el boton de ingreso
 */
formulario_usuario::formulario_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formulario_usuario)
{
    ui->setupUi(this);

    //string claveAdminUI = ui->clvadminNR->text().toStdString();

}
/**
 * @brief formulario_usuario::~formulario_usuario es el destructor de la clase
 */
formulario_usuario::~formulario_usuario()
{
    delete ui;
}
/**
 * @brief formulario_usuario::on_buttonBox_accepted me dice que pasa cuando se oprime el boton "ok"
 * @details cuando se oprima el boton "OK" del formulario_usuario se va a enviar el usuario registrado y la contraseña
 * para verificar que ya este el usuario en la base de datos
 */
void formulario_usuario::on_buttonBox_accepted()
{
    string username = ui->_username->text().toStdString();
    string usrpassword = ui->_usrpassword->text().toStdString();
    emit enviarDatos(username,usrpassword);
}
/**
 * @brief formulario_usuario::on_cdm_RegUsr_clicked me dice que pasa cuando se oprime el boton registrar usuario
 * @details cuando se oprima el boton de  registrar usuario se va traer la informacion de la interfaz y emitirla para
 * despues pasarla a la base de datos.
 */
void formulario_usuario::on_cdm_RegUsr_clicked()
{
    string nameNew = ui->nomuNR->text().toStdString();
    string claveNew = ui->passNR->text().toStdString();
    string apellidoNew = ui->apeNR->text().toStdString();
    string usernameN = ui->usuNR->text().toStdString();
    string claveAdminUI = ui->clvadminNR->text().toStdString();


    int dayNR = ui->fnNR->date().day();
    int monthNR = ui->fnNR->date().month();
    int  yearNR = ui->fnNR->date().year();
    int docId = ui->docNR->text().toInt();

    bool aceptadoUs = true;

    if(claveAdminUI == claveAdmin){
        emit envioDatosUsuarioNew(usernameN,nameNew,apellidoNew,claveNew,docId,dayNR,monthNR,yearNR,aceptadoUs);
        this->close(); // -------->>>>>>>CAMBIO!!!!
    }else{
        clave_erronea a(this);
        a.setModal( true );
        a.show();
        a.exec();
    }
}
