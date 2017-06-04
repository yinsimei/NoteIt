#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "notemanager.h"

int main(int argc, char * argv[]) {
    try {
        QApplication app(argc, argv);
        MainWindow mw;
        mw.show();
        return app.exec();
    } catch (NotesException e) {
        qDebug() << "Unhanded Exception: " << e.getMsg().c_str();
    }
}
