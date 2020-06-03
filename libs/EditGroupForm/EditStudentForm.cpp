#include "EditGroupForm.h"
#include "../../models/Group/Group.h"
#include "../../helpers/Dialog/Dialog.h"
#include <QPushButton>
#include <QLineEdit>

EditGroupForm::EditGroupForm(uint groupId_arg, QWidget *parent_arg): QDialog(parent_arg), ui(), groupId_(groupId_arg) {
    ui.setupUi(this);
    bindSignal();
    autoFill();
    disableSave();
}

void EditGroupForm::autoFill() {
    auto group{ Model::Group::getGroupById(groupId_) };

    ui.nameInput->setText(group.getName());
    ui.teacherInput->setText(group.getTeacher());
    ui.subjectInput->setText(group.getSubject());
}

void EditGroupForm::bindSignal() {
    auto *discardButton{ ui.buttonBox->button(QDialogButtonBox::Discard) };
    connect(discardButton, &QPushButton::clicked, this, &EditGroupForm::handleDiscardBtn);

    auto *saveButton{ ui.buttonBox->button(QDialogButtonBox::Save) };
    connect(saveButton, &QPushButton::clicked, this, &EditGroupForm::handleSaveBtn);

    connect(ui.nameInput, &QLineEdit::textChanged, this, &EditGroupForm::handleInputChange);
    connect(ui.subjectInput, &QLineEdit::textChanged, this, &EditGroupForm::handleInputChange);
    connect(ui.teacherInput, &QLineEdit::textChanged, this, &EditGroupForm::handleInputChange);
}

void EditGroupForm::disableSave() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(false);
}

void EditGroupForm::enableSave() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(true);
}

void EditGroupForm::handleSaveBtn() {
    auto isError{ Model::Group::editGroup(groupId_, ui.nameInput->text(), ui.teacherInput->text(), ui.subjectInput->text()) };

    if (!isError) {
        Dialog::showWarning(tr("Error while editing group."));
        disableSave();
    } else {
        emit groupEdited();
        close();
    }
}

void EditGroupForm::handleDiscardBtn() {
    close();
}

void EditGroupForm::handleInputChange() {
    if (
        Model::Group::isValidName(ui.nameInput->text()) &&
        Model::Group::isValidTeacher(ui.teacherInput->text()) &&
        Model::Group::isValidSubject(ui.subjectInput->text())
    ) {
        return enableSave();
    }
    return disableSave();
}
