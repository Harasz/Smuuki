#include "EditInvoiceForm.h"
#include "../../models/Invoice/Invoice.h"
#include "../../models/Student/Student.h"
#include "../../helpers/Dialog/Dialog.h"
#include <QPushButton>

EditInvoiceForm::EditInvoiceForm(uint invoiceId_arg, QWidget *parent_arg): QDialog(parent_arg), invoiceId_(invoiceId_arg), ui() {
    ui.setupUi(this);
    bindSignal();
    loadStudentToCombo();
    autoFill();
    disableSave();
}

void EditInvoiceForm::autoFill() {
    auto invoice{ Model::Invoice::getInvoiceById(invoiceId_) };
    auto invoiceAmount{ invoice.getPaidAmount().replace(",", ".") };

    ui.studentCombo->setCurrentIndex(ui.studentCombo->findData(invoice.getStudentId()));
    ui.descText->setText(invoice.getDesc());
    ui.amountSpin->setValue(invoiceAmount.mid(0, invoiceAmount.length() - 4).toDouble());
    ui.untilDateInput->setDate(invoice.getPaidUntil());
}

void EditInvoiceForm::bindSignal() {
    auto *discardButton{ ui.buttonBox->button(QDialogButtonBox::Discard) };
    connect(discardButton, &QPushButton::clicked, this, &EditInvoiceForm::handleDiscardBtn);

    auto *saveButton{ ui.buttonBox->button(QDialogButtonBox::Save) };
    connect(saveButton, &QPushButton::clicked, this, &EditInvoiceForm::handleSaveBtn);

    connect(ui.descText, &QTextEdit::textChanged, this,  [this](){handleInputChange(QString());});
    connect(ui.untilDateInput, &QDateEdit::dateChanged, this,  [this](){handleInputChange(QString());});
    connect(ui.amountSpin, &QDoubleSpinBox::textChanged, this, &EditInvoiceForm::handleInputChange);
}

void EditInvoiceForm::disableSave() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(false);
}

void EditInvoiceForm::enableSave() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(true);
}

void EditInvoiceForm::handleSaveBtn() {
    auto isError{ Model::Invoice::editInvoice(
            invoiceId_,
            ui.studentCombo->currentData().toUInt(),
            ui.descText->toPlainText(),
            ui.amountSpin->text(),
            ui.untilDateInput->date())
    };

    if (!isError) {
        Dialog::showWarning(tr("Error while editing invoice."));
        disableSave();
    } else {
        emit invoiceEdited();
        close();
    }
}

void EditInvoiceForm::handleDiscardBtn() {
    close();
}

void EditInvoiceForm::handleInputChange(const QString & text_arg) {
    if (
            !Model::Invoice::isValidDesc(ui.descText->toPlainText()) ||
            !Model::Invoice::isValidPaidAmount(ui.amountSpin->text()) ||
            !Model::Invoice::isValidPaidUntil(ui.untilDateInput->date())
            ) {
        disableSave();
        return;
    }

    enableSave();
}

void EditInvoiceForm::loadStudentToCombo() {
    auto studentList{ Model::Student::getAllStudents() };

    ui.studentCombo->clear();

    for (auto student : studentList) {
        ui.studentCombo->addItem(
                QString("%1 %2 (ID: %3)").arg(student.getName(), student.getSurname(), QString::number(student.getId())),
                student.getId()
        );
    }
}
