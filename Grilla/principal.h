#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QVector>
#include <QTimer>
#include <QGridLayout>

#include "alumnito.h"

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();

    void setMinutos_para_considerar_deslogueado(int value);

private:
    Ui::Principal *ui;

    QNetworkAccessManager * manager;
    QNetworkAccessManager * managerMensajes;
    int minutos_para_considerar_deslogueado;  // Si el archivo es mas viejo que estos minutos, entocnes usuario deslogueado

    QTimer * timer;

    int cantidad_alumnos_actuales;

    void dibujarAlumnos();


private slots:
    void slot_descargaFinalizada( QNetworkReply * reply );
    void slot_descargaFinalizadaMensajes( QNetworkReply * reply );
    void slot_timer();
    void dibujarGrilla();
    void cargarDatos(QString usuario, Alumnito *alumno, QLabel *alumnoTexto, QString tiempo);
    void sacarLogueados(Alumnito *alumno, QLabel *alumnoTexto);
    void sacarLogu(int index);

};

#endif // PRINCIPAL_H
