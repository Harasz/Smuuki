#include "StudentList.h"
#include "FiltersDialogStudent.h"
#include "../../helpers/Dialog/Dialog.h"
#include "../../models/Student/Student.h"
#include "../EditStudentForm/EditStudentForm.h"
#include "../AddInvoiceForm/AddInvoiceForm.h"
#include "../../forms/InvoiceTab/ui_addinvoiceformdialog.h"
#include <QtSql/QSqlQuery>
#include <QMenu>
#include <QPushButton>
#include <QTableView>
#include <QMessageBox>
#include <QShortcut>
#include <QDialog>
#include <QVBoxLayout>

StudentList::StudentList(QWidget* parent_arg): QWidget(parent_arg) {
    ui.setupUi(this);
    this->initTableModel();
    this->bind();
}

void StudentList::initTableModel() {
    tableModel.setTable("students");
    tableModel.setRelation(3, QSqlRelation("groups", "id", "name"));
    tableModel.select();

    // Table headers
    tableModel.setHeaderData(0, Qt::Horizontal, tr("ID"));
    tableModel.setHeaderData(1, Qt::Horizontal, tr("Name"));
    tableModel.setHeaderData(2, Qt::Horizontal, tr("Surname"));
    tableModel.setHeaderData(3, Qt::Horizontal, tr("Group Name"));
    tableModel.setHeaderData(4, Qt::Horizontal, tr("Parent/Guardian"));
    tableModel.setHeaderData(5, Qt::Horizontal, tr("Contact"));

    filterModel.setSourceModel(&tableModel);
    ui.tableView->setModel(&filterModel);

    ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui.tableView->verticalHeader()->hide();
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableView->setSortingEnabled(true);
    ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    updateInfoLabel();
}

void StudentList::refreshList() {
    tableModel.select();
    updateInfoLabel();
}

void StudentList::handleRefreshButton() {
    return refreshList();
}

void StudentList::handleFiltersButton() {
    FiltersDialogStudent filtersDialog(&filterModel, this);
    filtersDialog.execFilter();
    return refreshList();
}

void StudentList::bind() {
    connect(ui.refreshButton, &QPushButton::clicked, this, &StudentList::handleRefreshButton);
    connect(ui.filtersButton, &QPushButton::clicked, this, &StudentList::handleFiltersButton);
    connect(ui.tableView, &QTableView::customContextMenuRequested, this, &StudentList::viewContextMenu);

    auto *deleteKey = new QShortcut(QKeySequence::Delete, this);
    connect(deleteKey, &QShortcut::activated, this, &StudentList::handleDelKey);
}

void StudentList::updateInfoLabel() {
    ui.infoLabel->setText(
            QString(tr("Students listed %1 of %2")).arg(
                    QString::number(filterModel.rowCount()),
                    QString::number(tableModel.rowCount())
                    ));
}

void StudentList::viewContextMenu(QPoint point_arg) {
    QModelIndex index{ ui.tableView->indexAt(point_arg) };
    QMenu *contextMenu{ new QMenu(ui.tableView) };
    QAction *deleteAction{ new QAction(tr("Delete"), this) };
    QAction *editAction{ new QAction(tr("Edit"), this) };
    QAction *addPaymentAction{ new QAction(tr("Add Payment"), this) };
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

    connect(addPaymentAction, &QAction::triggered, [=]( ) {
        this->handleAddPayment(modelId);
    });

    contextMenu->addAction(deleteAction);
    contextMenu->addAction(editAction);
    contextMenu->addAction(addPaymentAction);
    contextMenu->popup(ui.tableView->viewport()->mapToGlobal(point_arg));
}


void StudentList::handleDelKey() {
    auto selectedIndex = ui.tableView->selectionModel()->currentIndex();
    handleRemoveRow(getRowIdByIndex(selectedIndex));
}

void StudentList::handleRemoveRow(uint modelId_arg) {
    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to remove student with ID: %1?").arg(modelId_arg));
    msgBox.setInformativeText(tr("You can not undo this operation, it is permanent."));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Question);
    int answer{ msgBox.exec() };

    if (answer != QMessageBox::Yes) return;

    if (Model::Student::removeStudent(modelId_arg)) {
        refreshList();
    } else {
        Dialog::showWarning(tr("Error while removing student."));
    }
}

uint StudentList::getRowIdByIndex(QModelIndex index_arg) {
    uint modelId{ filterModel.data(filterModel.index(index_arg.row(), 0)).toUInt() };
    return modelId;
}

void StudentList::handleEditRow(uint modelId_arg) {
    EditStudentForm editStudentForm(modelId_arg, this);
    connect(&editStudentForm, &EditStudentForm::studentEdited, this, &StudentList::handleRefreshButton);
    editStudentForm.exec();
}

void StudentList::handleAddPayment(uint modelId_arg) {
    QDialog dialog(this);
    Ui::AddInvoiceFormDialog dialogUi;
    AddInvoiceForm addInvoiceForm(&dialog, modelId_arg);

    dialogUi.setupUi(&dialog);
    dialogUi.layout->addWidget(&addInvoiceForm);
    connect(&addInvoiceForm, &AddInvoiceForm::paymentAdded, &dialog, &QDialog::close);
    connect(&addInvoiceForm, &AddInvoiceForm::discardClicked, &dialog, &QDialog::close);

    dialog.exec();
}
