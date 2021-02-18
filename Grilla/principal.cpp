#include "principal.h"
#include "ui_principal.h"

#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QStringList>

Principal::Principal(QWidget *parent) : QWidget(parent),
                                        ui(new Ui::Principal),
                                        manager( new QNetworkAccessManager( this ) ),
                                        managerMensajes( new QNetworkAccessManager( this ) ),
                                        timer( new QTimer( this ) ),
                                        cantidad_alumnos_actuales( 0 )
{
    ui->setupUi(this);

    connect( manager, SIGNAL( finished( QNetworkReply * ) ), this, SLOT( slot_descargaFinalizada( QNetworkReply * ) ) );
    connect( managerMensajes, SIGNAL( finished( QNetworkReply * ) ),
             this, SLOT( slot_descargaFinalizadaMensajes( QNetworkReply * ) ) );

    connect( timer, SIGNAL( timeout() ), this, SLOT( slot_timer() ) );

    ui->alumno0->hide();
    ui->alumno1->hide();
    ui->alumno2->hide();
    ui->alumno3->hide();
    ui->alumno4->hide();
    ui->alumno5->hide();
    ui->alumno6->hide();
    ui->alumno7->hide();
    ui->alumno8->hide();

    ui->l0->hide();
    ui->l1->hide();
    ui->l2->hide();
    ui->l3->hide();
    ui->l4->hide();
    ui->l5->hide();
    ui->l6->hide();
    ui->l7->hide();
    ui->l8->hide();

    timer->start( 2000 );
}

Principal::~Principal()
{
    delete ui;
}

void Principal::setMinutos_para_considerar_deslogueado(int value)
{
    minutos_para_considerar_deslogueado = value;
}

void Principal::slot_timer()  {
    manager->get( QNetworkRequest( QUrl( "http://www.vayra.com.ar/clase360/consultas.php?consulta=archivos" ) ) );

    managerMensajes->get( QNetworkRequest(
             QUrl( "http://www.vayra.com.ar/clase360/consultas.php?consulta=mensajes&cantidad=30" ) ) );
}

void Principal::slot_descargaFinalizada( QNetworkReply * reply )  {

    int index_alumno = -1;

    QString str = reply->readAll().simplified();

    QStringList archivos = str.split( "<br>" );
    archivos.sort();

    dibujarGrilla();

    for( int i = 0 ; i < archivos.size() ; i++ )  {

        if ( archivos.at( i ).isEmpty() )
            continue;

        QFileInfo fileInfo( archivos.at( i ) );
        QString nombre = fileInfo.baseName();  // Es solo en nombre, sin el .jpg

        QStringList usuario_tiempo = nombre.split( "_" );

       // qDebug() << usuario_tiempo << i;

        QString usuario;
        QString tiempo_del_archivo;

        if ( usuario_tiempo.size() == 2 )  {
            usuario = usuario_tiempo.at( 0 );
            tiempo_del_archivo = usuario_tiempo.at( 1 );
        }

        int seg = this->minutos_para_considerar_deslogueado * 60;

        // Cuando entra a este if es porque el archivo es desde hace menos de estos seg segundos
        if( QDateTime::fromString( tiempo_del_archivo, "yyyyMMddHHmmss" ).addSecs( seg ) > QDateTime::currentDateTime() )  {
            index_alumno++;

          //  qDebug() << "index_alumno" << index_alumno;

            switch ( index_alumno ) {

            case 0:
                qDebug() << "0" << usuario;
                cargarDatos(usuario, ui->alumno0, ui->l0, tiempo_del_archivo);
                break;

            case 1:
                qDebug() << "1" << usuario;
                cargarDatos(usuario, ui->alumno1, ui->l1, tiempo_del_archivo);
                break;

            case 2:
                qDebug() << "2" << usuario;
                cargarDatos(usuario, ui->alumno2, ui->l2, tiempo_del_archivo);
                break;

           case 3:
                qDebug() << "3" << usuario;
                cargarDatos(usuario,ui->alumno3, ui->l3, tiempo_del_archivo);
                break;

            case 4:
                qDebug() << "4" << usuario;
                cargarDatos(usuario, ui->alumno4, ui->l4, tiempo_del_archivo);
                break;

            case 5:
                qDebug() << "5" << usuario;
                cargarDatos(usuario,ui->alumno5, ui->l5, tiempo_del_archivo);
                break;

            case 6:
                qDebug() << "6" << usuario;
                cargarDatos(usuario,ui->alumno6, ui->l6, tiempo_del_archivo);
                break;

            case 7:
                qDebug() << "7" << usuario;
                cargarDatos(usuario,ui->alumno7, ui->l7, tiempo_del_archivo);
                break;

            case 8:
                qDebug() << "8" << usuario;
                cargarDatos(usuario,ui->alumno8, ui->l8, tiempo_del_archivo);
                break;

            default:
                break;
            }
        }
    }

    this->cantidad_alumnos_actuales = index_alumno + 1;

    this->dibujarAlumnos();
}

void Principal::dibujarGrilla(){

    int anchoMensajes = this->width() / 3;

    ui->teMensajes->resize( anchoMensajes, this->height() );
    ui->teMensajes->move( this->width() - anchoMensajes, 0 );

    int ancho = this->width() - anchoMensajes;
    int alto = this->height();
    int anchoFoto = ancho / 4;
    int altoFoto = anchoFoto * 240 / 330;

    ui->alumno0->resize(anchoFoto, altoFoto);
    ui->alumno0->move(1, alto / 2 - altoFoto / 2 );

    ui->alumno1->resize(anchoFoto, altoFoto);
    ui->alumno1->move( alto / 2 - altoFoto / 5,  alto / 2 - altoFoto / 2);

    ui->alumno2->resize(anchoFoto, altoFoto);
    ui->alumno2->move(alto - altoFoto/2.5,  alto / 2 - altoFoto / 2);

    ui->alumno3->resize(anchoFoto, altoFoto);
    ui->alumno3->move(1, alto/15);

    ui->alumno4->resize(anchoFoto, altoFoto);
    ui->alumno4->move(alto / 2 - altoFoto / 5, alto/15 );

    ui->alumno5->resize(anchoFoto, altoFoto);
    ui->alumno5->move(alto - altoFoto/2.5, alto/15);

    ui->alumno6->resize(anchoFoto, altoFoto);
    ui->alumno6->move(1, alto - anchoFoto);

    ui->alumno7->resize(anchoFoto, altoFoto);
    ui->alumno7->move(alto / 2 - altoFoto / 5, alto - anchoFoto);

    ui->alumno8->resize(anchoFoto, altoFoto);
    ui->alumno8->move(alto - altoFoto/2.5, alto - anchoFoto);
}

void Principal::cargarDatos(QString usuario, Alumnito *alumno, QLabel *alumnoTexto, QString tiempo){
   alumno->setUsuario(usuario);
   alumno->descargarImagen( "http://www.vayra.com.ar/clase360/fotos/" + usuario + "_" +
                                              tiempo + ".jpg" );

    if (alumno->isImageCargada() )  {
        alumnoTexto->setText( usuario );
        alumnoTexto->resize( alumno->width(), alumnoTexto->height() );
        alumnoTexto->move( alumno->pos().x() + alumno->width() / 2 - alumnoTexto->width() / 2, alumno->pos().y() + alumno->height());
    }
}

void Principal::slot_descargaFinalizadaMensajes( QNetworkReply * reply )  {

    ui->teMensajes->clear();

    QString str = reply->readAll().simplified();

    qDebug() << str;

    QStringList mensajes = str.split( "<br>" );

    qDebug() << mensajes;

    for( int i = 0 ; i < mensajes.size() ; i++ )  {

        if ( mensajes.at( i ).isEmpty() )
            continue;

        QStringList usuario_mensaje = mensajes.at( i ).split( "::" );
        if ( usuario_mensaje.size() == 2 )  {
            QString usuario = usuario_mensaje.at( 0 );
            QString mensaje = usuario_mensaje.at( 1 );

            QString mensajeParaMostrar = "<strong>" + usuario + "</strong> : " + mensaje;

            ui->teMensajes->append( mensajeParaMostrar );
        }

    }

}

void Principal::dibujarAlumnos()  {

    int alumnosLogueados = this->cantidad_alumnos_actuales;

    switch(alumnosLogueados){

        case 0:
                sacarLogu(0);
                break;

        case 1:
                ui->alumno0->show(); ui->l0->show();
                sacarLogu(1);
                break;

        case 2:
                ui->alumno0->show();ui->l0->show();
                ui->alumno1->show();ui->l1->show();
                sacarLogu(2);
                break;
        case 3:
                ui->alumno0->show();ui->l0->show();
                ui->alumno1->show();ui->l1->show();
                ui->alumno2->show();ui->l2->show();
                sacarLogu(3);
                break;

        case 4:
                ui->alumno0->show(); ui->l0->show();
                ui->alumno1->show(); ui->l1->show();
                ui->alumno2->show(); ui->l2->show();
                ui->alumno3->show(); ui->l3->show();
                sacarLogu(4);
                break;

        case 5:
                ui->alumno0->show(); ui->l0->show();
                ui->alumno1->show(); ui->l1->show();
                ui->alumno2->show(); ui->l2->show();
                ui->alumno3->show(); ui->l3->show();
                ui->alumno4->show(); ui->l4->show();
                sacarLogu(5);
                break;

        case 6:
                ui->alumno0->show(); ui->l0->show();
                ui->alumno1->show(); ui->l1->show();
                ui->alumno2->show(); ui->l2->show();
                ui->alumno3->show(); ui->l3->show();
                ui->alumno4->show(); ui->l4->show();
                ui->alumno5->show(); ui->l5->show();
                sacarLogu(6);
                break;


        case 7:
                ui->alumno0->show(); ui->l0->show();
                ui->alumno1->show(); ui->l1->show();
                ui->alumno2->show(); ui->l2->show();
                ui->alumno3->show(); ui->l3->show();
                ui->alumno4->show(); ui->l4->show();
                ui->alumno5->show(); ui->l5->show();
                ui->alumno6->show();ui->l6->show();
                sacarLogu(7);
                break;

        case 8:
                ui->alumno0->show(); ui->l0->show();
                ui->alumno1->show(); ui->l1->show();
                ui->alumno2->show(); ui->l2->show();
                ui->alumno3->show(); ui->l3->show();
                ui->alumno4->show(); ui->l4->show();
                ui->alumno5->show(); ui->l5->show();
                ui->alumno6->show();ui->l6->show();
                ui->alumno7->show(); ui->l7->show();
                sacarLogu(8);
                break;

        case 9:
                ui->alumno0->show(); ui->l0->show();
                ui->alumno1->show(); ui->l1->show();
                ui->alumno2->show(); ui->l2->show();
                ui->alumno3->show(); ui->l3->show();
                ui->alumno4->show(); ui->l4->show();
                ui->alumno5->show(); ui->l5->show();
                ui->alumno6->show();ui->l6->show();
                ui->alumno7->show(); ui->l7->show();
                ui->alumno8->show(); ui->l8->show();
                sacarLogu(9);
                break;
        default: ;
    }
}

void Principal::sacarLogu(int index){
    switch(index){
        case 0:
            sacarLogueados(ui->alumno0, ui->l0);
        case 1:
            sacarLogueados(ui->alumno1, ui->l1);
        case 2:
            sacarLogueados(ui->alumno2, ui->l2);
        case 3:
            sacarLogueados(ui->alumno3, ui->l3);
        case 4:
            sacarLogueados(ui->alumno4, ui->l4);
        case 5:
            sacarLogueados(ui->alumno5, ui->l5);
        case 6:
            sacarLogueados(ui->alumno6, ui->l6);
        case 7:
            sacarLogueados(ui->alumno7, ui->l7);
        case 8:
            sacarLogueados(ui->alumno8, ui->l8);
        default:;
    }
}

void Principal::sacarLogueados(Alumnito *alumno, QLabel *alumnoTexto){
    alumno->hide();
    alumnoTexto->hide();
}
