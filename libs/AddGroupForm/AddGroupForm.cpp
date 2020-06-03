#include "AddGroupForm.h"
#include "../../models/Group/Group.h"
#include "../../helpers/Dialog/Dialog.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QTimer>

AddGroupForm::AddGroupForm(QWidget *parent_arg): QWidget(parent_arg), ui() {
    ui.setupUi(this);
    disableAccept();
    bindSignals();
    ui.successLabel->hide();
}

void AddGroupForm::disableAccept() {
    auto *btn{ ui.formButtonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(false);
}

void AddGroupForm::enableAccept() {
    auto *btn{ ui.formButtonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(true);
}

void AddGroupForm::handleTextChange(const QString &text_arg) {
    if (ui.subjectInput->text().isEmpty() || ui.teacherInput->text().isEmpty() || ui.nameInput->text().isEmpty()) {
        disableAccept();
        return;
    }

    enableAccept();
}

void AddGroupForm::bindSignals() {
    connect(ui.teacherInput, &QLineEdit::textChanged, this, &AddGroupForm::handleTextChange);
    connect(ui.nameInput, &QLineEdit::textChanged, this,  &AddGroupForm::handleTextChange);
    connect(ui.subjectInput, &QLineEdit::textChanged, this,  &AddGroupForm::handleTextChange);
    connect(ui.formButtonBox, &QDialogButtonBox::accepted, this, &AddGroupForm::submitForm);

    QPushButton *resetButton{ ui.formButtonBox->button(QDialogButtonBox::Discard) };
    connect(resetButton, &QPushButton::clicked, this, &AddGroupForm::resetForm);
}

void AddGroupForm::submitForm() {
    auto isError{ Model::Group::addGroup(ui.nameInput->text(), ui.teacherInput->text(), ui.subjectInput->text()) };

    if (!isError) {
        Dialog::showWarning(tr("Error while adding new group."));
        disableAccept();
    } else {
        clearForm();
        showSuccessLabel();
        hideSuccessLabel();
        emit groupAdded();
    }
}

void AddGroupForm::resetForm() {
    clearForm();
}

void AddGroupForm::clearForm() {
    ui.nameInput->clear();
    ui.teacherInput->clear();
    ui.subjectInput->clear();
    disableAccept();
}

void AddGroupForm::showSuccessLabel() {
    ui.successLabel->show();
}

void AddGroupForm::hideSuccessLabel(uint timeout) {
    QTimer::singleShot(timeout, ui.successLabel, &QWidget::hide);
}

void AddGroupForm::refreshData() {}
