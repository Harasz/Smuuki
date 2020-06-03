#ifndef SMUUKI_ADDGROUPFORM_H
#define SMUUKI_ADDGROUPFORM_H

#include "../../forms/GroupsTab/ui_addgroupform.h"
#include <QWidget>

class AddGroupForm : public QWidget {
Q_OBJECT
public:
    explicit AddGroupForm(QWidget*);

private:
    Ui::AddGroupForm ui;

    void bindSignals();

    void disableAccept();

    void enableAccept();

    void clearForm();

    void showSuccessLabel();

    void hideSuccessLabel(uint timeout = 2000); // timeout in milliseconds

signals:
    void groupAdded();

private slots:
    void handleTextChange(const QString &);

    void submitForm();

    void resetForm();

public slots:
    void refreshData();
};


#endif //SMUUKI_ADDGROUPFORM_H
