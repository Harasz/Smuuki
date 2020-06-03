//
// Created by Jakub on 14-03-2020.
//

#ifndef SMUUKI_INVOICESTAB_H
#define SMUUKI_INVOICESTAB_H

#include <QWidget>
#include "../../forms/InvoiceTab/ui_invoicestab.h"


class InvoicesTab : public QWidget {
Q_OBJECT
public:
    explicit InvoicesTab(QWidget *parent = nullptr);
    static InvoicesTab *registerView(QWidget *widget, QLayout *layout);

    void showEvent(QShowEvent* event) override {
        QWidget::showEvent( event );
        emit refreshTabs();
    }

private:
    Ui::InvoiceTab ui;

    void initTab();

signals:
    void refreshTabs();
};


#endif //SMUUKI_INVOICESTAB_H
