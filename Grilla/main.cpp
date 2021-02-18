#include "principal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Principal w;
    w.setMinutos_para_considerar_deslogueado( 1 );
    w.show();

    return a.exec();
}
