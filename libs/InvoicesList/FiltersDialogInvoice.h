#ifndef SMUUKI_IFILTERSDIALOG_H
#define SMUUKI_IFILTERSDIALOG_H

#include "../../forms/InvoiceTab/ui_invoiceslistfilters.h"
#include "FilterModelInvoice.h"
#include <QDialog>
#include <QAbstractButton>

class FiltersDialogInvoice: public QDialog {
Q_OBJECT
public:
    explicit FiltersDialogInvoice(FilterModelInvoice *, QWidget *parent = nullptr);

    void execFilter();

    void bindSignals();

private:
    Ui::InvoicesListFilters ui{};
    FilterModelInvoice *model;

    void applyFilters();

    void loadGroupToCombo();

    void loadStudentToCombo();

private slots:
    void resetForm();

    void applyForm();

    void click(QAbstractButton *);

    void dateChanged();
};


#endif //SMUUKI_IFILTERSDIALOG_H
