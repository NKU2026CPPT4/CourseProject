#include <QApplication>
#include <QLabel>
#include <QScreen>

int main(int argc, char *argv[]) {
    // Initialize the Qt Application
    QApplication app(argc, argv);

    // Create a simple label widget
    QLabel label("Qt Environment is OK!");
    label.setAlignment(Qt::AlignCenter);
    label.resize(300, 150);

    // Show the widget
    label.show();

    // Enter the event loop
    return app.exec();
}