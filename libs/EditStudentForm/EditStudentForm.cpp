#include "EditStudentForm.h"
#include "../../models/Student/Student.h"
#include "../../helpers/Dialog/Dialog.h"
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>

EditStudentForm::EditStudentForm(uint studentId_arg, QWidget *parent_arg): QDialog(parent_arg), ui(), studentId_(studentId_arg) {
    ui.setupUi(this);
    loadGroupToCombo();
    bindSignal();
    autoFill();
    disableSave();
}

void EditStudentForm::loadGroupToCombo() {
    auto groupList{ Model::Group::getAllGroups() };

    ui.groupCombo->clear();

    for (auto group : groupList) {
        ui.groupCombo->addItem(
                QString("%1 - %2 (%3)").arg(group.getName(), group.getTeacher(), group.getSubject()),
                group.getId()
        );
    }
}

void EditStudentForm::autoFill() {
    auto student{ Model::Student::getStudentById(studentId_) };

    ui.nameInput->setText(student.getName());
    ui.surnameInput->setText(student.getSurname());
    ui.contactInput->setText(student.getContact());
    ui.parentInput->setText(student.getParent());
    ui.groupCombo->setCurrentIndex(ui.groupCombo->findData(student.getGroupId()));
}

void EditStudentForm::bindSignal() {
    auto *discardButton{ ui.buttonBox->button(QDialogButtonBox::Discard) };
    connect(discardButton, &QPushButton::clicked, this, &EditStudentForm::handleDiscardBtn);

    auto *saveButton{ ui.buttonBox->button(QDialogButtonBox::Save) };
    connect(saveButton, &QPushButton::clicked, this, &EditStudentForm::handleSaveBtn);

    connect(ui.nameInput, &QLineEdit::textChanged, this, &EditStudentForm::handleInputChange);
    connect(ui.surnameInput, &QLineEdit::textChanged, this, &EditStudentForm::handleInputChange);
    connect(ui.parentInput, &QLineEdit::textChanged, this, &EditStudentForm::handleInputChange);
    connect(ui.contactInput, &QLineEdit::textChanged, this, &EditStudentForm::handleInputChange);
    connect(ui.groupCombo, &QComboBox::currentTextChanged, this, &EditStudentForm::handleInputChange);
}

void EditStudentForm::disableSave() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(false);
}

void EditStudentForm::enableSave() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(true);
}

void EditStudentForm::handleSaveBtn() {
    auto isError{
        Model::Student::editStudent(
                studentId_, ui.nameInput->text(),
                ui.surnameInput->text(),
                ui.parentInput->text(),
                ui.contactInput->text(),
                ui.groupCombo->currentData().toUInt()
                )
    };

    if (!isError) {
        Dialog::showWarning(tr("Error while editing student."));
        disableSave();
    } else {
        emit studentEdited();
        close();
    }
}

void EditStudentForm::handleDiscardBtn() {
    close();
}

void EditStudentForm::handleInputChange() {
    if (
        Model::Student::isValidName(ui.nameInput->text()) &&
        Model::Student::isValidSurname(ui.surnameInput->text()) &&
        Model::Student::isValidParent(ui.parentInput->text()) &&
        Model::Student::isValidContact(ui.contactInput->text())
    ) {
        return enableSave();
    }
    return disableSave();
}
