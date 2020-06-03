#include "Dialog.h"
#include <QtCore/QtCore>
#include <QMessageBox>

void Dialog::showFatalError(const QString &msg_arg, bool exitApp_arg) {
    QMessageBox errorMessage;
    errorMessage.setWindowTitle(qApp->tr("Fatal error occurred"));
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.setText(msg_arg);
    errorMessage.exec();
    if (exitApp_arg) {
        QCoreApplication::exit(EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
}

void Dialog::showWarning(const QString &msg_arg) {
    QMessageBox warningMessage;
    warningMessage.setWindowTitle(qApp->tr("Warning"));
    warningMessage.setIcon(QMessageBox::Warning);
    warningMessage.setText(msg_arg);
    warningMessage.exec();
}

void Dialog::showInfo(const QString &msg_arg) {
    QMessageBox warningMessage;
    warningMessage.setWindowTitle(qApp->tr("Info"));
    warningMessage.setIcon(QMessageBox::Information);
    warningMessage.setText(msg_arg);
    warningMessage.exec();
}
