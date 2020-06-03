#ifndef SMUUKI_EDITGROUPFORM_H
#define SMUUKI_EDITGROUPFORM_H

#include "../../forms/GroupsTab/ui_editgroupform.h"
#include <QDialog>

class EditGroupForm: public QDialog {
Q_OBJECT
public:
    explicit EditGroupForm(uint, QWidget *parent = nullptr);

private:
    Ui::EditGroupForm ui;
    uint groupId_;

    void autoFill();

    void bindSignal();

    void disableSave();

    void enableSave();

private slots:
    void handleSaveBtn();

    void handleDiscardBtn();

    void handleInputChange();

public: signals:
    void groupEdited();
};


#endif //SMUUKI_EDITGROUPFORM_H
