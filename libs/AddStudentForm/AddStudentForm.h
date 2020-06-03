#ifndef SMUUKI_ADDSTUDENTFORM_H
#define SMUUKI_ADDSTUDENTFORM_H

#include "../../forms/StudentsTab/ui_addstudentform.h"
#include <QWidget>

class AddStudentForm : public QWidget {
Q_OBJECT
public:
    explicit AddStudentForm(QWidget*);

private:
    Ui::AddStudentForm ui;

    void loadGroupToCombo();

    void bindSignals();

    void disableAccept();

    void enableAccept();

    void clearForm();

    void showSuccessLabel();

    void hideSuccessLabel(uint timeout = 2000); // timeout in milliseconds

signals:
    void studentAdded();

private slots:
    void handleTextChange(const QString &);

    void submitForm();

    void resetForm();

public slots:
    void refreshData();
};


#endif //SMUUKI_ADDSTUDENTFORM_H
