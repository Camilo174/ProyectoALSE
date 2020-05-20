#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QString>
#include<QDate>
#include<QTime>

#include <formulario_paciente.h>
#include <formulario_usuario.h>
#include <datos_usuario.h>

/**
 * @brief MainWindow::MainWindow
 * @param parent es la clase padre de todas las ventanas es decir es nuestro mainWindow
 * @details  se abre la base de datos, y se declaran dos variables para nuestros botones en los
 * cuales van a estar en dos estados prendidos y apagados entoces rd:apagado, rl encendido,
 * ademas se van a reconocer los botones que se tienen en la aplicacion, y desabilito los
 * dos botones para ir habilitandolos a medida que se va ejecutando la aplicacion
 */


MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    base.abrirDB("/home/alseuser/ProyectoALSE/base_datos");

    ui->setupUi(this);

    rd = new QPixmap("/home/alseuser/ProyectoALSE/12.png"); //led apagado
    rl = new QPixmap("/home/alseuser/ProyectoALSE/13.png"); //led encendido


    ui->boton_1->setIcon(*rd);
    ui->boton_1->setIconSize(rd->rect().size());
    ui->boton_2->setIcon(*rd);
    ui->boton_2->setIconSize(rd->rect().size());
    ui->boton_3->setIcon(*rd);
    ui->boton_3->setIconSize(rd->rect().size());
    ui->boton_4->setIcon(*rd);
    ui->boton_4->setIconSize(rd->rect().size());
    ui->boton_5->setIcon(*rd);
    ui->boton_5->setIconSize(rd->rect().size());
    ui->boton_6->setIcon(*rd);
    ui->boton_6->setIconSize(rd->rect().size());
    ui->boton_7->setIcon(*rd);
    ui->boton_7->setIconSize(rd->rect().size());
    ui->boton_8->setIcon(*rd);
    ui->boton_8->setIconSize(rd->rect().size());
    ui->boton_9->setIcon(*rd);
    ui->boton_9->setIconSize(rd->rect().size());
    ui->boton_10->setIcon(*rd);
    ui->boton_10->setIconSize(rd->rect().size());

    ui->cmd_inicio->setEnabled(false);
    ui->RegPnt->setEnabled(false);
}
/**
 * @brief MainWindow::~MainWindow este es el destructor de la clase
 * @details el cual nos sirve para cerrar la base de datos y borrar la informacion que esta en la pantalla la cual ya ha sido almacenada en la base de datos
 */
MainWindow::~MainWindow()
{
    base.cerrarDB();
    delete ui;
}
/**
 * @brief MainWindow::reciboDatosUsuarioReg  esta funcion es para recibir los datos de un usuario ya registrado
 * los cuales estan en una base de datos ya guardada y a esta funcion se le pasan los siguientes parametros
 * @param username: es el nombre de usuario que se ingresa, la cual se va a verificar que este en la base de datos
 * @param password: es la contraseña  ingresada la cual se va a validar
 * @details luego de validar que el nombre de usuario este en la base de datos y la contraseña este correcta se habilitara
 * el boton para registrar un paciente, dado el caso que la contraseña sea incorrecta se llama la ventana de clave_erronea.
 *
 */
void MainWindow::reciboDatosUsuarioReg(string username, string password)
{

    if(base.compararDatosUsuario(username,password)==0){
        ui->RegPnt->setEnabled(true);
        ui->_lbl_username->setText(QString::fromStdString(username));
    }
    else if(base.compararDatosUsuario(username,password)==2){
        clave_erronea b;
        b.setModal( true );
        b.show();
        b.exec();
        ui->RegPnt->setEnabled(false);
        }
    else {
        clave_erronea b;
        b.setModal( true );
        b.show();
        b.exec();
        ui->RegPnt->setEnabled(false);
    }
}
/**
 * @brief MainWindow::calcular_edad  esta funcion es para calcular la edad y se le pasan los siguientes parametros
 * @param anoN: año de nacimiento
 * @param mesN: mes de nacimiento
 * @param diaN: dia de nacimiento
 * @param ano_actual: año actual
 * @param mes_actual: mes actual
 * @param dia_actual: día actual
 * @details para obtener la edad se debe restar la fecha de nacimiento de la fecha actual como el sistema toma solo
 * los ultimos dos digitos del año entonces cuando el año es menor al 2000 se restara 100 para que se calcule
 * correctamente, si el mes actual es mayor al mes de nacimiento quiere decir que la edad es la diferencia de
 * los años,si el mes actual es menor al de nacimiento quiere decir que la edad va a ser la diferencia de años
 * menos 1 ya que no habra cumplido años la persona, si el mes actual es igual se compara los dias para calcular
 * la edad correctamente.
 * @return la edad correcta del usuario nuevo
 */
int MainWindow::calcular_edad(int anoN, int mesN, int diaN, int ano_actual, int mes_actual, int dia_actual)
{
    int edad;
    if(anoN>ano_actual){
        anoN -= 100;
    }

    if(mes_actual>mesN){
        edad = ano_actual - anoN;
    }
    else{
        if(mesN == mes_actual){
            if(dia_actual<diaN){
                edad = ano_actual - anoN -1;
            }
            else{
                edad = ano_actual -anoN;
            }
        }
        else{
            edad = ano_actual - anoN -1;
        }
    }

    return edad;
}
/**
 * @brief MainWindow::reciboDatosUsuarioNew  desde la interfaz se deben pedir los datos de un usuario nuevo si
 * no esta registrado, para guardar los datos solicitados en la respectiva base de datos
 * @param usernameN: es el nombre de usuario el cual se va a utilizar para iniciar sesión
 * @param nameN: el nombre de la persona
 * @param apellidoN: el apellido de la persona
 * @param passwordN: la clave utilizada para iniciiar sesión
 * @param docIdN: el documento de identidad de la persona
 * @param dayNR: el día de nacimiento de la persona
 * @param monthNR: el mes de nacimiento de la persona
 * @param yearNR: el año de nacimiento de la persona
 * @param aceptadoUs: boton para activar la siguiente opcion y continuar con la aplicacion
 */
void MainWindow::reciboDatosUsuarioNew(string usernameN, string nameN, string apellidoN, string passwordN, int docIdN, int dayNR, int monthNR, int yearNR,bool aceptadoUs)
{
    string usuarioNew = usernameN;
    string claveNew = passwordN;
    string nameNew = nameN;
    string apellidoNew = apellidoN;
    int docId = docIdN;

    int diaN = dayNR;
    int mesN = monthNR;
    int anoN = yearNR;
    /**
    * @brief fecha_actual con la opcion de Qdate::currentDate() traigo la fecha actual del sistema para poder calcular la edad
    * de la persona hasta la fecha actual, la cual va a costar de tres partes y voy a igualarla a los enteros ya
    * dispuestos para luego mandarlos a la funcion de calcular_edad vista anteriormente.
    */
    QDate fecha_actual = QDate::currentDate();
    int dia_actual = fecha_actual.day();
    int mes_actual = fecha_actual.month();
    int ano_actual = fecha_actual.year();

    int edad = calcular_edad(anoN, mesN, diaN, ano_actual, mes_actual, dia_actual);

    ui->_lbl_username->setText(QString::fromStdString(usuarioNew));
    ui->_lbl_usrnombre->setText(QString::fromStdString(nameNew));
    ui->_lbl_usrapellido->setText(QString::fromStdString(apellidoNew));

    if(aceptadoUs){ui->RegPnt->setEnabled(true);}

    base.almacenarUsuario(usuarioNew,claveNew,nameNew,apellidoNew,docId,edad);
}
/**
 * @brief MainWindow::reciboDatosPaciente desde la interfaz se deben pedir los datos de un paciente,
 *  para guardar los datos solicitados en la respectiva base de datos los parametros que se le envian son
 * @param nombrePnt: nombre paciente
 * @param apellidoPnt: apellido paciente
 * @param edad: edad del paciente
 * @param docPnt: documento del paciente
 * @param generoPnt: genero del paciente
 * @param razaPnt: raza del paciente
 * @param nivelSEpnt: ingresos economicos del paciente
 * @param aceptado: boton para guardar los datos
 */
void MainWindow::reciboDatosPaciente(string nombrePnt, string apellidoPnt, int edad, long docPnt, string generoPnt, string razaPnt, string nivelSEpnt, bool aceptado)
{
  ui->_lbl_pntnombre->setText(QString::fromStdString(nombrePnt));
  ui->_lbl_apellido->setText(QString::fromStdString(apellidoPnt));
  ui->_lbl_edadpnt->setText(QString::fromStdString((std::to_string(edad))));
  ui->_lbl_genero->setText(QString::fromStdString(generoPnt));
  ui->_lbl_idpnt->setText(QString::fromStdString(std::to_string(docPnt)));

  /** con la siguiente linea se manda la informacion a la base de datos abierta por la funcion de almacenar paciente
  **/
  base.almacenarPaciente(nombrePnt,apellidoPnt,edad,docPnt,nivelSEpnt,generoPnt,razaPnt);

  /** con la siguiente linea despues de pedir los datos del paciente se va a habilitar el boton de iniciar y continuar
  *  con la aplicacion
  **/
  if(aceptado){ui->cmd_inicio->setEnabled(true);}

}
/**
 * @brief MainWindow::on_cmd_ingreso_clicked es el primer boton que se va a activar
 * @details cuando se oprime este boton se va a llamar a la ventana de formulario usuario en la cual hay dos opciones
 * ingresar con un usuario ya registrado o registrar un usuario nuevo
 */
void MainWindow::on_cmd_ingreso_clicked()
{
    formulario_usuario a(this);
    a.setModal( true );
    /**
     * @brief connect con esto conecto las dos ventanas y envio los datos o recibo los datos necesarios
     */
    connect( &a, &formulario_usuario::enviarDatos, this, &MainWindow::reciboDatosUsuarioReg );
    connect( &a, &formulario_usuario::envioDatosUsuarioNew, this, &MainWindow::reciboDatosUsuarioNew );
    a.show();
    a.exec();
}
/**
 * @brief MainWindow::on_RegPnt_clicked es el segundo boton que se va a habilitar
 * @details cuando se oprime este boton se va a llamar a la ventana de formulario paciente en la cual se va a ingresar
 * un paciente
 */
void MainWindow::on_RegPnt_clicked()
{
    formulario_paciente b(this);
    b.setModal( true );
    connect( &b, &formulario_paciente::enviarDatosPnt, this, &MainWindow::reciboDatosPaciente);
    b.show();
    b.exec();
}
/**
 * @brief MainWindow::on_cmd_inicio_clicked es el tercer boton que se va a habilitar
 * @details cuando se oprime este boton se va a dar inicio a la prueba de habilidad,la cual actualiza la hora de inicio
 * de la prueba, va contando los aciertos y errores que se tiene en la prueba, se inicializa el texto del final de prueba
 * en blanco, luego se llama a la funcion randon para determinar cual boton se va a encender se realizan dos conect con
 * los cuales se va a contar, se tienen dos contadores el primero es el de cambio de estado el cual es de 1 segundo y el
 * otro es el de terminar prueba el cual es determinado por el tiempo seleccionado en la interfaz, se dio un tiempo de 3 segundos
 * para iniciar la prueba y este tiempo tambien tiene que ser sumado al de final de la prueba despues de inicializar estos tiempos
 * se empiezan a contar.
 */
void MainWindow::on_cmd_inicio_clicked()
{
    QTime hora = QTime::currentTime();
    ui->hora_inicio->setTime(hora);

    int tiempo_prueba = ui->_tiempo_prueba->value();
    tiempo_prueba *= 1000;

    _aciertos = _errores = 0;
    ui->_lbl_aciertos->setText(QString::fromStdString(std::to_string(_aciertos)));
    ui->_lbl_errores->setText(QString::fromStdString(std::to_string(_errores)));

    ui->_lbl_finPrueba->setText("");

    _estado = random1_10();
    _timer1 = new QTimer(this);
    _timer2 = new QTimer(this);
    connect(_timer1, &QTimer::timeout, this, &MainWindow::cambio_estado );
    connect(_timer2, &QTimer::timeout, this, &MainWindow::terminar_prueba );
    _timer1->setInterval( 3000 );
    _timer2->setInterval(tiempo_prueba + 3000);
    _timer2->start();
    _timer1->start();
}
/**
 * @brief MainWindow::random1_10 me devuelve un valor aleatorio entre 1 y 10 el cual me va a decir que boton se va
 * a encender
 * @return valor aleatorio entre 1 y 10
 */
int MainWindow::random1_10()
{
    return rand() % 10 + 1;
}
/**
 * @brief MainWindow::terminar_prueba me va a imprimir el resumen de la prueba en la consola
 */
void MainWindow::terminar_prueba()
{
    QTime hora = QTime::currentTime();

    ui->hora_final->setTime(hora);

    for(unsigned int i; i < datos_prueba.size(); i++){
        cout<< "Estado: " << datos_prueba[i].ac_error << "----->";
        cout<< " Boton oprimidio: " << datos_prueba[i].btn_oprimido << " Boton correcto: " << datos_prueba[i].btn_correcto;
        cout<< " Hora: " << datos_prueba[i].hora.hour() <<"."<< datos_prueba[i].hora.minute() <<"."<< datos_prueba[i].hora.second();
        cout << "." << datos_prueba[i].hora.msec();
        cout<<endl;
    }

    _estado = 11;
}

//CAMBIO DE ESTADO-------------------------
/**
 * @brief MainWindow::cambio_estado cambia el boton que se encuentra encendido en la interfaz
 * @details dependiendo el valor aleatorio devuelto por la funcion random1_10 me va a cambiar el boton encendido en la
 * interfaz con ayuda de la funcion switch, con las siguientes lineas de codigo lo que se hace es darle el tiempo de 1
 * segundo para el boton encendido  "_timer1->setInterval( 1000 );", "_timer1->start();", cuando se sale del break se
 * vuelve a llamar la funcion cambio de estado, cuando se termine el tiempo de prueba se va a llamar la funcion terminar
 * prueba la cual me va a devolver que el estado es igual a 11 con la cual se va a detener la prueba y se detienen los dos
 * timers
 */
void MainWindow::cambio_estado()
{
    if(_estado==11){
        _estado=11;
    }else{_estado = random1_10();}

    switch (_estado) {
    case 1:
        ui->boton_1->setIcon(*rl);
        ui->boton_1->setIconSize(rl->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 2:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rl);
        ui->boton_2->setIconSize(rl->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 3:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rl);
        ui->boton_3->setIconSize(rl->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 4:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rl);
        ui->boton_4->setIconSize(rl->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 5:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rl);
        ui->boton_5->setIconSize(rl->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 6:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rl);
        ui->boton_6->setIconSize(rl->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 7:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rl);
        ui->boton_7->setIconSize(rl->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 8:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rl);
        ui->boton_8->setIconSize(rl->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 9:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rl);
        ui->boton_9->setIconSize(rl->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    case 10:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rl);
        ui->boton_10->setIconSize(rl->rect().size());
        _timer1->setInterval( 1000 );
        _timer1->start();
        break;
    default:
        ui->boton_1->setIcon(*rd);
        ui->boton_1->setIconSize(rd->rect().size());
        ui->boton_2->setIcon(*rd);
        ui->boton_2->setIconSize(rd->rect().size());
        ui->boton_3->setIcon(*rd);
        ui->boton_3->setIconSize(rd->rect().size());
        ui->boton_4->setIcon(*rd);
        ui->boton_4->setIconSize(rd->rect().size());
        ui->boton_5->setIcon(*rd);
        ui->boton_5->setIconSize(rd->rect().size());
        ui->boton_6->setIcon(*rd);
        ui->boton_6->setIconSize(rd->rect().size());
        ui->boton_7->setIcon(*rd);
        ui->boton_7->setIconSize(rd->rect().size());
        ui->boton_8->setIcon(*rd);
        ui->boton_8->setIconSize(rd->rect().size());
        ui->boton_9->setIcon(*rd);
        ui->boton_9->setIconSize(rd->rect().size());
        ui->boton_10->setIcon(*rd);
        ui->boton_10->setIconSize(rd->rect().size());
        _timer1->setInterval(500);
        _timer1->stop();
        _timer2->stop();
        ui->_lbl_finPrueba->setText("Fin de la prueba.");
        break;
    }
}
//-----------------------------------------
/**
 * @brief MainWindow::on_boton_1_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_1_clicked()
{
    estado = 1;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_2_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_2_clicked()
{
    estado = 2;
    verificar_click(2);
}
/**
 * @brief MainWindow::on_boton_3_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_3_clicked()
{
    estado = 3;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_4_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_4_clicked()
{
    estado = 4;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_5_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_5_clicked()
{
    estado = 5;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_6_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_6_clicked()
{
    estado = 6;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_7_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_7_clicked()
{
    estado = 7;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_8_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_8_clicked()
{
    estado = 8;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_9_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_9_clicked()
{
    estado = 9;
    verificar_click(estado);
}
/**
 * @brief MainWindow::on_boton_10_clicked cada vez que se oprima este boton se va a llamar al slot de este boton
 */
void MainWindow::on_boton_10_clicked()
{
   estado = 10;
   verificar_click(estado);
}
/**
 * @brief MainWindow::verificar_click  esta funcion es un slot la cual va a verificar si el boton oprimido es el mismo
 * que el boton activado
 * @param estado es el estado del boton oprimido
 * @details el cual se va a pasar el estado real del boton que esta prendido, si esto es correcto muestra
 * en la interfaz que fue correcto y aumentan los aciertos que se van mostrando en la interfaz, si esto es incorrecto
 * muestra en la interfaz que fue un error y la cantidad de estos son mostrados en la consola
 */
void MainWindow::verificar_click(int estado)
{
    prueba a;
    QTime tiempo = QTime::currentTime();
    a.hora = tiempo;
    a.btn_correcto = _estado;
    a.btn_oprimido = estado;

    if(_estado == estado){
        _estado = estado;
        _aciertos++;
        a.ac_error = "Correcto";
        datos_prueba.push_back(a);
        ui->_lbl_aciertos->setText(QString::fromStdString(std::to_string(_aciertos)));
        cambio_estado();
    }
    else{_errores++;
        a.ac_error = "Error";
        datos_prueba.push_back(a);
        ui->_lbl_errores->setText(QString::fromStdString(std::to_string(_errores -1)));
         cambio_estado();}
}

