#include <QApplication>
#include "libs/MainWindow/MainWindow.h"

int main(int argc, char *argv[])
{
    int currentCode;
    do {
        QApplication app(argc, argv);
        app.setOrganizationName("Smuuki GPL");
        app.setOrganizationDomain("smuuki.app");
        app.setApplicationName("Smuuki");
        app.setApplicationVersion("v0.0.1");

        MainWindow window;
        window.setWindowTitle(MainWindow::tr("Smuuki APP - Manage Your Students Payments"));
        window.showMaximized();
        currentCode = app.exec();
    } while (currentCode == -1);

    return currentCode;
}
