
#include "ui/MainWindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("mactintosh"));
    MainWindow window;
    window.show();

    return app.exec();
}
