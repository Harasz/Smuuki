#include "InvoicesTab.h"
#include "../AddInvoiceForm/AddInvoiceForm.h"
#include "../InvoicesList/InvoicesList.h"

InvoicesTab::InvoicesTab(QWidget *parent_arg): QWidget(parent_arg), ui() {
    ui.setupUi(this);
    this->initTab();
}

InvoicesTab *InvoicesTab::registerView(QWidget *widget_arg, QLayout *layout_arg) {
    auto *result = new InvoicesTab(widget_arg);
    layout_arg->addWidget(result);
    result->hide();
    return result;
}

void InvoicesTab::initTab() {
    auto* listInvoiceTab = new InvoicesList(ui.invoiceTabWidget);
    ui.invoiceTabWidget->addTab(listInvoiceTab, "listInvoiceTab");
    ui.invoiceTabWidget->setTabText(ui.invoiceTabWidget->indexOf(listInvoiceTab), tr("Payment List"));

    auto* addInvoiceTab = new AddInvoiceForm(ui.invoiceTabWidget);
    ui.invoiceTabWidget->addTab(addInvoiceTab, "addInvoiceTab");
    ui.invoiceTabWidget->setTabText(ui.invoiceTabWidget->indexOf(addInvoiceTab), tr("Add Payment"));

    connect(addInvoiceTab, &AddInvoiceForm::paymentAdded, listInvoiceTab, &InvoicesList::handleRefreshButton);
    connect(this, &InvoicesTab::refreshTabs, listInvoiceTab, &InvoicesList::handleRefreshButton);
    connect(this, &InvoicesTab::refreshTabs, addInvoiceTab, &AddInvoiceForm::refreshData);
}
