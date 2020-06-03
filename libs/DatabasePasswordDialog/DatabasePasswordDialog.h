#ifndef SMUUKI_DATABASEPASSWORDDIALOG_H
#define SMUUKI_DATABASEPASSWORDDIALOG_H

#include "../../forms/DatabasePasswordDialog/ui_passworddialog.h"
#include <QDialog>

class DatabasePasswordDialog: public QDialog {
Q_OBJECT

public:
    explicit DatabasePasswordDialog(bool isConfirm = false);

    QString getPassword(bool changePass = false);

private:
    Ui::PasswordDatabaseDialog ui;
    bool isConfirm;

    void hideConfirmLabels();

    void bindSignals();

    void disableAccept();

    void enableAccept();

private slots:
    void handleTextChange(const QString &);
};


#endif //SMUUKI_DATABASEPASSWORDDIALOG_H
