#ifndef ALUMNITO_H
#define ALUMNITO_H

#include <QLabel>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

class Alumnito : public QLabel
{
    Q_OBJECT

public:
    explicit Alumnito( QWidget * parent = 0 );
    ~Alumnito();

    void descargarImagen( QString url_imagen );

    QString getUsuario() const;
    void setUsuario(const QString &value);

    bool isImageCargada();

private:

    QImage im;
    QString usuario, nombre, apellido;
    QNetworkAccessManager * manager;

private slots:
    void slot_descargaFinalizada( QNetworkReply * reply );

};

#endif // ALUMNITO_H
