#ifndef SMUUKI_DIALOG_H
#define SMUUKI_DIALOG_H

#include <QString>
#include <QtWidgets/QMessageBox>

class Dialog {
public:
    static void showFatalError(const QString &, bool exitApp = false);
    static void showWarning(const QString &);
    static void showInfo(const QString &);
};


#endif //SMUUKI_DIALOG_H
