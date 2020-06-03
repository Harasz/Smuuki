#include "InvoicesList.h"
#include "FiltersDialogInvoice.h"
#include "../../helpers/Dialog/Dialog.h"
#include "../../models/Invoice/Invoice.h"
#include "../EditInvoiceForm/EditInvoiceForm.h"
#include <QtSql/QSqlQuery>
#include <QMenu>
#include <QPushButton>
#include <QTableView>
#include <QMessageBox>
#include <QShortcut>
#include <QVBoxLayout>

InvoicesList::InvoicesList(QWidget* parent_arg): QWidget(parent_arg) {
    ui.setupUi(this);
    this->initTableModel();
    this->bind();
}

void InvoicesList::initTableModel() {
    tableModel.setTable("invoices");
    tableModel.setRelation(1, QSqlRelation("students", "id", "name, surname"));
    tableModel.select();

    // Table headers
    tableModel.setHeaderData(0, Qt::Horizontal, tr("ID"));
    tableModel.setHeaderData(1, Qt::Horizontal, tr("Student Name"));
    tableModel.setHeaderData(2, Qt::Horizontal, tr("Student Surname"));
    tableModel.setHeaderData(3, Qt::Horizontal, tr("Description"));
    tableModel.setHeaderData(4, Qt::Horizontal, tr("Paid Amount"));
    tableModel.setHeaderData(5, Qt::Horizontal, tr("Paid Until"));

    filterModel.setSourceModel(&tableModel);
    ui.tableView->setModel(&filterModel);

    ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    ui.tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    ui.tableView->verticalHeader()->hide();
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableView->setSortingEnabled(true);
    ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    updateInfoLabel();
}

void InvoicesList::refreshList() {
    tableModel.select();
    updateInfoLabel();
}

void InvoicesList::handleRefreshButton() {
    return refreshList();
}

void InvoicesList::handleFiltersButton() {
    FiltersDialogInvoice filtersDialog(&filterModel, this);
    filtersDialog.execFilter();
    return refreshList();
}

void InvoicesList::bind() {
    connect(ui.refreshButton, &QPushButton::clicked, this, &InvoicesList::handleRefreshButton);
    connect(ui.filtersButton, &QPushButton::clicked, this, &InvoicesList::handleFiltersButton);
    connect(ui.tableView, &QTableView::customContextMenuRequested, this, &InvoicesList::viewContextMenu);

    auto *deleteKey = new QShortcut(QKeySequence::Delete, this);
    connect(deleteKey, &QShortcut::activated, this, &InvoicesList::handleDelKey);
}

void InvoicesList::updateInfoLabel() {
    ui.infoLabel->setText(
            QString(tr("Invoices listed %1 of %2")).arg(
                    QString::number(filterModel.rowCount()),
                    QString::number(tableModel.rowCount())
                    ));
}

void InvoicesList::viewContextMenu(QPoint point_arg) {
    QModelIndex index{ ui.tableView->indexAt(point_arg) };
    QMenu *contextMenu{ new QMenu(ui.tableView) };
    QAction *deleteAction{ new QAction(tr("Delete"), this) };
    QAction *editAction{ new QAction(tr("Edit"), this) };
    uint modelId{ getRowIdByIndex(index) };

    // If item exists
    if (modelId <= 0) {
        delete deleteAction;
        delete contextMenu;
        return;
    }

    connect(deleteAction, &QAction::triggered, [=]( ) {
        this->handleRemoveRow(modelId);
    });

    connect(editAction, &QAction::triggered, [=]( ) {
        this->handleEditRow(modelId);
    });

    contextMenu->addAction(deleteAction);
    contextMenu->addAction(editAction);
    contextMenu->popup(ui.tableView->viewport()->mapToGlobal(point_arg));
}


void InvoicesList::handleDelKey() {
    auto selectedIndex{ ui.tableView->selectionModel()->currentIndex() };
    handleRemoveRow(getRowIdByIndex(selectedIndex));
}

void InvoicesList::handleRemoveRow(uint modelId_arg) {
    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to remove payment with ID: %1?").arg(modelId_arg));
    msgBox.setInformativeText(tr("You can not undo this operation, it is permanent."));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Question);
    int answer{ msgBox.exec() };

    if (answer != QMessageBox::Yes) return;

    if (Model::Invoice::removeInvoice(modelId_arg)) {
        refreshList();
    } else {
        Dialog::showWarning(tr("Error while removing payment."));
    }
}

uint InvoicesList::getRowIdByIndex(QModelIndex index_arg) {
    uint modelId{ filterModel.data(filterModel.index(index_arg.row(), 0)).toUInt() };
    return modelId;
}

void InvoicesList::handleEditRow(uint modelId_arg) {
    EditInvoiceForm editInvoiceForm(modelId_arg, this);
    connect(&editInvoiceForm, &EditInvoiceForm::invoiceEdited, this, &InvoicesList::handleRefreshButton);
    editInvoiceForm.exec();
}
