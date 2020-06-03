#ifndef SMUUKI_INVOICELIST_H
#define SMUUKI_INVOICELIST_H

#include "FilterModelInvoice.h"
#include "FiltersDialogInvoice.h"
#include "../../forms/InvoiceTab/ui_invoicelist.h"
#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QPoint>
#include <QVariant>

class InvoicesList: public QWidget {
Q_OBJECT
public:
    explicit InvoicesList(QWidget* parent = nullptr);

    void initTableModel();

    void refreshList();

    void updateInfoLabel();

    void bind();

private:
    Ui::InvoicesList ui{};
    QSqlRelationalTableModel tableModel;
    FilterModelInvoice filterModel;

    void handleRemoveRow(uint);

    uint getRowIdByIndex(QModelIndex);

public slots:
    void handleRefreshButton();

private slots:
    void handleFiltersButton();

    void viewContextMenu(QPoint);

    void handleDelKey();

    void handleEditRow(uint);
};


#endif //SMUUKI_INVOICELIST_H
