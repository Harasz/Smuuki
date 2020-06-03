#ifndef SMUUKI_ADDINVOICEFORM_H
#define SMUUKI_ADDINVOICEFORM_H

#include "../../forms/InvoiceTab/ui_addinvoiceform.h"
#include <QWidget>

class AddInvoiceForm : public QWidget {
Q_OBJECT
public:
    explicit AddInvoiceForm(QWidget*);

    explicit AddInvoiceForm(QWidget*, uint);

    explicit AddInvoiceForm(uint);

private:
    Ui::AddInvoiceForm ui;

    void bindSignals();

    void disableAccept();

    void enableAccept();

    void clearForm();

    void showSuccessLabel();

    void hideSuccessLabel(uint timeout = 2000); // timeout in milliseconds

    void loadStudentToCombo();

signals:
    void paymentAdded();

    void discardClicked();

private slots:
    void handleTextChange(const QString &);

    void submitForm();

    void resetForm();

public slots:
    void refreshData();
};


#endif //SMUUKI_ADDINVOICEFORM_H
