#include <QApplication>
#include <QPushButton>
int main(int argc, char * argv[]) {
    QApplication app(argc, argv);

    // Button Quit
    QPushButton buttonQuit("Quitter");
    buttonQuit.show();

    QObject::connect(&buttonQuit, SIGNAL(clicked()), &app, SLOT(quit()));

    return app.exec();
}
