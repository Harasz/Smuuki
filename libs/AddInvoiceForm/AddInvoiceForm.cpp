#include "AddInvoiceForm.h"
#include "../../models/Invoice/Invoice.h"
#include "../../helpers/Dialog/Dialog.h"
#include "../../models/Student/Student.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QTimer>

AddInvoiceForm::AddInvoiceForm(QWidget *parent_arg): QWidget(parent_arg), ui() {
    ui.setupUi(this);
    loadStudentToCombo();
    disableAccept();
    bindSignals();
    ui.successLabel->hide();
}

AddInvoiceForm::AddInvoiceForm(QWidget *parent_arg, uint studentId_arg) : AddInvoiceForm(parent_arg) {
    ui.studentCombo->setCurrentIndex(ui.studentCombo->findData(studentId_arg));
    ui.studentCombo->setDisabled(true);
    disableAccept();
}

AddInvoiceForm::AddInvoiceForm(uint studentId_arg) : AddInvoiceForm(nullptr, studentId_arg) {}

void AddInvoiceForm::disableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(false);
}

void AddInvoiceForm::enableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(true);
}

void AddInvoiceForm::handleTextChange(const QString &text_arg) {
    if (
        !Model::Invoice::isValidDesc(ui.descText->toPlainText()) ||
        !Model::Invoice::isValidPaidAmount(ui.amountSpin->text()) ||
        !Model::Invoice::isValidPaidUntil(ui.untilDateInput->date())
    ) {
        disableAccept();
        return;
    }

    enableAccept();
}

void AddInvoiceForm::bindSignals() {
    connect(ui.studentCombo, &QComboBox::currentTextChanged, this, &AddInvoiceForm::handleTextChange);
    connect(ui.descText, &QTextEdit::textChanged, this,  [this](){handleTextChange(QString());});
    connect(ui.untilDateInput, &QDateEdit::dateChanged, this,  [this](){handleTextChange(QString());});
    connect(ui.amountSpin, &QDoubleSpinBox::textChanged, this, &AddInvoiceForm::handleTextChange);
    connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &AddInvoiceForm::submitForm);

    QPushButton *resetButton{ ui.buttonBox->button(QDialogButtonBox::Discard) };
    connect(resetButton, &QPushButton::clicked, this, &AddInvoiceForm::resetForm);
}

void AddInvoiceForm::submitForm() {
    auto isError{
        Model::Invoice::addInvoice(
            ui.studentCombo->currentData().toUInt(),
            ui.descText->toPlainText(),
            ui.amountSpin->text(),
            ui.untilDateInput->date()
            )
    };

    if (!isError) {
        Dialog::showWarning(tr("Error while registering new payment."));
        disableAccept();
    } else {
        clearForm();
        showSuccessLabel();
        hideSuccessLabel();
        emit paymentAdded();
    }
}

void AddInvoiceForm::resetForm() {
    clearForm();
    emit discardClicked();
}

void AddInvoiceForm::clearForm() {
    ui.studentCombo->setCurrentIndex(-1);
    ui.descText->clear();
    ui.amountSpin->setValue(1.00);
    ui.untilDateInput->setDate(QDate::currentDate());
    disableAccept();
}

void AddInvoiceForm::showSuccessLabel() {
    ui.successLabel->show();
}

void AddInvoiceForm::hideSuccessLabel(uint timeout_arg) {
    QTimer::singleShot(timeout_arg, ui.successLabel, &QWidget::hide);
}

void AddInvoiceForm::loadStudentToCombo() {
    auto studentList{ Model::Student::getAllStudents() };

    ui.studentCombo->clear();

    for (auto student : studentList) {
        ui.studentCombo->addItem(
                QString("%1 %2 (ID: %3)").arg(student.getName(), student.getSurname(), QString::number(student.getId())),
                student.getId()
        );
    }
}

void AddInvoiceForm::refreshData() {
    loadStudentToCombo();
    disableAccept();
}
