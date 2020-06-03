#include "OutstandingPayments.h"
#include <QDebug>

OutstandingPayments::OutstandingPayments(QWidget *parent_arg): QDialog(parent_arg), ui() {
    ui.setupUi(this);
    initTableModal();
    if (filterModel.rowCount() == 0) close();
}

void OutstandingPayments::initTableModal() {
    tableModel.setQuery("SELECT max(i.id), s.name, s.surname, i.desc, i.paidAmount, i.paidUntil FROM invoices as i, students as s WHERE i.studentId = s.id GROUP BY i.studentId;");
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
}

int OutstandingPayments::getOutstandingPayments() {
    return filterModel.rowCount();
}
