#include "AddStudentForm.h"
#include "../../models/Student/Student.h"
#include "../../helpers/Dialog/Dialog.h"
#include <QPushButton>
#include <QTimer>

AddStudentForm::AddStudentForm (QWidget *parent_arg): QWidget(parent_arg), ui() {
    ui.setupUi(this);
    disableAccept();
    bindSignals();
    loadGroupToCombo();
    ui.successLabel->hide();
}

void AddStudentForm::bindSignals() {
    connect(ui.nameInput, &QLineEdit::textChanged, this, &AddStudentForm::handleTextChange);
    connect(ui.surnameInput, &QLineEdit::textChanged, this,  &AddStudentForm::handleTextChange);
    connect(ui.parentInput, &QLineEdit::textChanged, this,  &AddStudentForm::handleTextChange);
    connect(ui.contactInput, &QLineEdit::textChanged, this,  &AddStudentForm::handleTextChange);
    connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &AddStudentForm::submitForm);

    QPushButton *resetButton{ ui.buttonBox->button(QDialogButtonBox::Discard) };
    connect(resetButton, &QPushButton::clicked, this, &AddStudentForm::resetForm);
}

void AddStudentForm::disableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(false);
}

void AddStudentForm::enableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(true);
}

void AddStudentForm::clearForm() {
    ui.contactInput->clear();
    ui.parentInput->clear();
    ui.nameInput->clear();
    ui.surnameInput->clear();
    ui.groupCombo->setCurrentIndex(-1);
    disableAccept();
}

void AddStudentForm::showSuccessLabel() {
    ui.successLabel->show();
}

void AddStudentForm::hideSuccessLabel(uint timeout_arg) {
    QTimer::singleShot(timeout_arg, ui.successLabel, &QWidget::hide);
}

void AddStudentForm::handleTextChange(const QString &text_arg) {
    if (
            ui.nameInput->text().isEmpty() ||
            ui.surnameInput->text().isEmpty() ||
            ui.parentInput->text().isEmpty() ||
            ui.groupCombo->currentText().isEmpty()
       ) {
        disableAccept();
        return;
    }

    enableAccept();
}

void AddStudentForm::submitForm() {
    auto isError{
        Model::Student::addStudent(
            ui.nameInput->text(),
            ui.surnameInput->text(),
            ui.parentInput->text(),
            ui.contactInput->text(),
            ui.groupCombo->currentData().toUInt()
            )
    };

    if (!isError) {
        Dialog::showWarning(tr("Error while adding new student."));
        disableAccept();
    } else {
        clearForm();
        showSuccessLabel();
        hideSuccessLabel();
        emit studentAdded();
    }
}

void AddStudentForm::resetForm() {
    clearForm();
}

void AddStudentForm::loadGroupToCombo() {
    auto groupList{ Model::Group::getAllGroups() };

    ui.groupCombo->clear();

    for (auto group : groupList) {
        ui.groupCombo->addItem(
                QString("%1 - %2 (%3)").arg(group.getName(), group.getTeacher(), group.getSubject()),
                group.getId()
                );
    }
}

void AddStudentForm::refreshData() {
    loadGroupToCombo();
    disableAccept();
}
