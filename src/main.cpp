#include <QApplication>
#include "AppController.h"
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    AppController controller;
    if (!controller.initialize()) {
        qDebug() << "Failed to initialize application";
        return 1;
    }
    
    QWidget* mainWidget = controller.getMainWidget();
    mainWidget->resize(1200, 800);
    mainWidget->show();
    
    return app.exec();
}




