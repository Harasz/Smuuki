#ifndef SMUUKI_OUTSTANDINGPAYMENTS_H
#define SMUUKI_OUTSTANDINGPAYMENTS_H

#include "../../forms/MainWindow/ui_outstandingpayments.h"
#include "FilterModelOutstandingPayments.h"
#include <QDialog>
#include <QSqlQueryModel>

class OutstandingPayments: public QDialog {
Q_OBJECT
public:
    explicit OutstandingPayments(QWidget *);

    int getOutstandingPayments();
private:
    Ui::OutstandPayments ui;
    QSqlQueryModel tableModel;
    FilterModelOutstandingPayments filterModel;

    void initTableModal();
};


#endif //SMUUKI_OUTSTANDINGPAYMENTS_H
