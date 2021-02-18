#include "alumnito.h"

Alumnito::Alumnito( QWidget * parent ) : QLabel( parent ),
                                         manager( new QNetworkAccessManager( this ) )
{

    connect( manager, SIGNAL( finished( QNetworkReply * ) ), this, SLOT( slot_descargaFinalizada( QNetworkReply * ) ) );

}

Alumnito::~Alumnito()
{
}

void Alumnito::descargarImagen( QString url_imagen )
{
    manager->get( QNetworkRequest( QUrl( url_imagen ) ) );
}

QString Alumnito::getUsuario() const
{
    return usuario;
}

void Alumnito::setUsuario(const QString &value)
{
    usuario = value;
}

bool Alumnito::isImageCargada()
{
    return ! im.isNull();
}

void Alumnito::slot_descargaFinalizada( QNetworkReply * reply )
{
    im = QImage::fromData( reply->readAll() );

    if ( ! im.isNull() )  {
        QPixmap pixmap = QPixmap::fromImage( im.scaled( this->width(), this->height() ) );
        this->setPixmap( pixmap );
    }
}






