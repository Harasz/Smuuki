//
// Created by Jakub on 29-04-2020.
//

#ifndef SMUUKI_EDITINVOICEFORM_H
#define SMUUKI_EDITINVOICEFORM_H

#include <QDialog>
#include "../../forms/InvoiceTab/ui_editinvoiceform.h"

class EditInvoiceForm: public QDialog {
Q_OBJECT
public:
    explicit EditInvoiceForm(uint, QWidget *parent = nullptr);
private:
    Ui::EditInvoiceForm ui;
    uint invoiceId_;

    void autoFill();

    void bindSignal();

    void disableSave();

    void enableSave();

    void loadStudentToCombo();

private slots:
    void handleSaveBtn();

    void handleDiscardBtn();

    void handleInputChange(const QString &);

public: signals:
    void invoiceEdited();
};


#endif //SMUUKI_EDITINVOICEFORM_H
