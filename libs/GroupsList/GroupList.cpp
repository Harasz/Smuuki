#include "GroupList.h"
#include "FiltersDialog.h"
#include "../../helpers/Dialog/Dialog.h"
#include "../../models/Group/Group.h"
#include "../EditGroupForm/EditGroupForm.h"
#include <QtSql/QSqlQuery>
#include <QMenu>
#include <QDebug>
#include <QPushButton>
#include <QTableView>
#include <QMessageBox>
#include <QShortcut>

GroupList::GroupList(QWidget* parent_arg): QWidget(parent_arg) {
    ui.setupUi(this);
    this->initTableModel();
    this->bind();
}

void GroupList::initTableModel() {
    tableModel.setTable("groups");
    tableModel.select();

    // Table headers
    tableModel.setHeaderData(0, Qt::Horizontal, tr("ID"));
    tableModel.setHeaderData(1, Qt::Horizontal, tr("Group Name"));
    tableModel.setHeaderData(2, Qt::Horizontal, tr("Teacher"));
    tableModel.setHeaderData(3, Qt::Horizontal, tr("Subject"));

    filterModel.setSourceModel(&tableModel);
    ui.tableView->setModel(&filterModel);

    ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui.tableView->verticalHeader()->hide();
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableView->setSortingEnabled(true);
    ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui.tableView->setEditTriggers(QTableView::NoEditTriggers);
    updateInfoLabel();
}

void GroupList::refreshList() {
    tableModel.select();
    updateInfoLabel();
}

void GroupList::handleRefreshButton() {
    return refreshList();
}

void GroupList::handleFiltersButton() {
    FiltersDialog filtersDialog(&filterModel, this);
    filtersDialog.execFilter();
    return refreshList();
}

void GroupList::bind() {
    connect(ui.refreshButton, &QPushButton::clicked, this, &GroupList::handleRefreshButton);
    connect(ui.filtersButton, &QPushButton::clicked, this, &GroupList::handleFiltersButton);
    connect(ui.tableView, &QTableView::customContextMenuRequested, this, &GroupList::viewContextMenu);

    auto *deleteKey = new QShortcut(QKeySequence::Delete, this);
    connect(deleteKey, &QShortcut::activated, this, &GroupList::handleDelKey);
}

void GroupList::updateInfoLabel() {
    ui.infoLabel->setText(
            QString(tr("Groups listed %1 of %2")).arg(
                    QString::number(filterModel.rowCount()),
                    QString::number(tableModel.rowCount())
                    ));
}

void GroupList::viewContextMenu(QPoint point_arg) {
    QModelIndex index{ ui.tableView->indexAt(point_arg) };
    QMenu *contextMenu{ new QMenu(ui.tableView) };
    QAction *deleteAction{ new QAction(tr("Delete"), this) };
    QAction *editAction{ new QAction(tr("Edit"), this) };
    uint modelId{ getRowIdByIndex(index) };
    contextMenu->setStyleSheet("");

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


void GroupList::handleDelKey() {
    auto selectedIndex{ ui.tableView->selectionModel()->currentIndex() };
    handleRemoveRow(getRowIdByIndex(selectedIndex));
}

void GroupList::handleRemoveRow(uint modelId_arg) {
    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to remove group with ID: %1?").arg(modelId_arg));
    msgBox.setInformativeText(tr("You can not undo this operation, it is permanent."));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Question);
    int answer{ msgBox.exec() };

    if (answer != QMessageBox::Yes) return;

    if (Model::Group::removeGroup(modelId_arg)) {
        refreshList();
    } else {
        Dialog::showWarning(tr("Error while removing group."));
    }
}

uint GroupList::getRowIdByIndex(QModelIndex index_arg) {
    uint modelId{ filterModel.data(filterModel.index(index_arg.row(), 0)).toUInt() };
    return modelId;
}

void GroupList::handleEditRow(uint modelId_arg) {
    EditGroupForm editGroupForm(modelId_arg, this);
    connect(&editGroupForm, &EditGroupForm::groupEdited, this, &GroupList::handleRefreshButton);
    editGroupForm.exec();
}
