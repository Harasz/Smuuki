#include "DatabasePasswordDialog.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

DatabasePasswordDialog::DatabasePasswordDialog(bool isConfirm_arg): isConfirm(isConfirm_arg), ui(), QDialog() {
    ui.setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->bindSignals();

    if (!isConfirm) {
        this->hideConfirmLabels();
    }
}

void DatabasePasswordDialog::hideConfirmLabels() {
    this->setMinimumSize(QSize(380, 190));
    this->setMaximumSize(QSize(380, 190));
    this->resize(380, 190);
    this->ui.confirmPasswordWidget->hide();
}

void DatabasePasswordDialog::bindSignals() {
    connect(ui.passwordInput, &QLineEdit::textChanged, this, &DatabasePasswordDialog::handleTextChange);
    connect(ui.confirmPasswordInput, &QLineEdit::textChanged, this, &DatabasePasswordDialog::handleTextChange);
}

void DatabasePasswordDialog::handleTextChange(const QString &text_arg) {
    if (isConfirm) {
        if (this->ui.confirmPasswordInput->text() != this->ui.passwordInput->text()) {
            this->ui.confirmPasswordLabelError->setText(tr("Passwords must be the same."));
            disableAccept();
            return;
        }
    }

    this->ui.passwordLabelError->setText("");
    this->ui.confirmPasswordLabelError->setText("");
    enableAccept();
}

QString DatabasePasswordDialog::getPassword(bool changePass) {
    int result{ exec() };

    if (result == 0) {
        if (changePass) {
            return "#-1%NO_PASS%";
        }
        QCoreApplication::exit(EXIT_SUCCESS);
        exit(EXIT_SUCCESS);
    }

    return ui.passwordInput->text();
}

void DatabasePasswordDialog::disableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Ok) };
    btn->setEnabled(false);
}

void DatabasePasswordDialog::enableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Ok) };
    btn->setEnabled(true);
}
