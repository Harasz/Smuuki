#ifndef SMUUKI_EDITSTUDENTFORM_H
#define SMUUKI_EDITSTUDENTFORM_H

#include "../../forms/StudentsTab/ui_editstudentform.h"
#include <QDialog>

class EditStudentForm: public QDialog {
Q_OBJECT
public:
    explicit EditStudentForm(uint, QWidget *parent = nullptr);

private:
    Ui::EditStudentForm ui;
    uint studentId_;

    void loadGroupToCombo();

    void autoFill();

    void bindSignal();

    void disableSave();

    void enableSave();

private slots:
    void handleSaveBtn();

    void handleDiscardBtn();

    void handleInputChange();

public: signals:
    void studentEdited();
};


#endif //SMUUKI_EDITSTUDENTFORM_H
