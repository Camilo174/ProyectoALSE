#include "formulario_paciente.h"
#include "ui_formulario_paciente.h"


using namespace std;
/**
 * @brief formulario_paciente::formulario_paciente es el constructor de la clase
 * @param parent es una ventana de dialogo la cual se va a habilitar desde el mainwindow con el boton de registro
 */
formulario_paciente::formulario_paciente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formulario_paciente)
{
    ui->setupUi(this);
}
/**
 * @brief formulario_paciente::~formulario_paciente es el destructor de la clase
 */
formulario_paciente::~formulario_paciente()
{
    delete ui;
}
/**
 * @brief formulario_paciente::on_buttonBox_accepted  me dice que pasa cuando se oprime el boton "ok"
 * traigo de la interfaz la informacion correspondiente, luego se calcula la edad del paciente y se verifica cual
 * fue la opcion marcada por el paciente en el genero,raza y nivel de ingresos, para luego enviarla con el emit
 * al mainWindow
 */
void formulario_paciente::on_buttonBox_accepted()
{
    formulario_paciente b(this);
    //connect( &b, &formulario_paciente::enviarDatosPnt, this, &MainWindow::reciboDatosPaciente);
    string NombrePnt = ui->nombre_pnt->text().toStdString();
    string ApellidoPnt = ui->apellido_pnt->text().toStdString();
    int docPnt = ui->doc_pnt->text().toInt();

    string generoPnt;
    string nivelSEpnt;
    string razaPnt;

    int anoN = ui->fechaN_pnt->date().year();
    int mesN = ui->fechaN_pnt->date().month();
    int diaN = ui->fechaN_pnt->date().day();

    /**
    * @brief fecha_actual se trae la fecha actual con la funcion de  QDate::currentDate() la cual se va a utilizar para
    * calcular la edad del paciente
    */
    QDate fecha_actual = QDate::currentDate();
    int anoA = fecha_actual.year();
    int mesA = fecha_actual.month();
    int diaA = fecha_actual.day();
    int edad = calcular_edad(anoN, mesN, diaN, anoA, mesA, diaA);

    bool genero_fem = ui->fem_pnt->isChecked();
    //bool genero_mas = ui->fem_pnt->isChecked();

    if(genero_fem){
        generoPnt = "Femenino";}
    else{
        generoPnt = "Masculino";
    }

    bool mezt = ui->mezt->isChecked();
    bool afro = ui->afro->isChecked();
    //bool indi = ui->indi->isChecked();

    if(mezt){
        razaPnt = "Mestizo";
    }else{
        if(afro){
            razaPnt = "Afrodescendiente";
        }
        else{
            razaPnt = "Indigena";
        }
    }

    bool alto = ui->alto_pnt->isChecked();
    bool medio = ui->medio_pnt->isChecked();
    //bool bajo = ui->bajo_pnt->isChecked();

    if(alto){
        nivelSEpnt = "Alto";
    }else{
        if(medio){
            nivelSEpnt = "Medio";
        }
        else{
            nivelSEpnt = "Bajo";
        }
    }

    bool aceptado = true;

    emit enviarDatosPnt(NombrePnt,ApellidoPnt,edad,docPnt,generoPnt,razaPnt,nivelSEpnt,aceptado);
}
/**
 * @brief formulario_paciente::calcular_edad esta funcion es para calcular la edad y se le pasan los siguientes parametros
 * @param anoN: año de nacimiento del paciente
 * @param mesN: mes de nacimiento del paciente
 * @param diaN: día de nacimiento del paciente
 * @param ano_actual: año actual del sistema
 * @param mes_actual: mes actual del sistema
 * @param dia_actual: dia actual del sistema
 * @details para obtener la edad se debe restar la fecha de nacimiento de la fecha actual como el sistema toma solo
 * los ultimos dos digitos del año entonces cuando el año es menor al 2000 se restara 100 para que se calcule
 * correctamente, si el mes actual es mayor al mes de nacimiento quiere decir que la edad es la diferencia de
 * los años,si el mes actual es menor al de nacimiento quiere decir que la edad va a ser la diferencia de años
 * menos 1 ya que no habra cumplido años la persona, si el mes actual es igual se compara los dias para calcular
 * la edad correctamente.
 * @return la edad del paciente
 */
int formulario_paciente::calcular_edad(int anoN, int mesN, int diaN, int ano_actual, int mes_actual, int dia_actual)
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
