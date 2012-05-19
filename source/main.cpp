#include <QtGui/QApplication>
#include "mainform.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QTranslator tTranslation;
    tTranslation.load("tr_" + QLocale::system().name(), ":/main/translations/translations");
    app.installTranslator(&tTranslation);
    MainForm w;
    w.show();
    
    return app.exec();
}
