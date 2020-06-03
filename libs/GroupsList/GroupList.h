#ifndef SMUUKI_GROUPLIST_H
#define SMUUKI_GROUPLIST_H

#include "FilterModel.h"
#include "FiltersDialog.h"
#include "../../forms/GroupsTab/ui_groupslist.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QPoint>
#include <QVariant>

class GroupList: public QWidget {
Q_OBJECT
public:
    explicit GroupList(QWidget* parent = nullptr);

    void initTableModel();

    void refreshList();

    void updateInfoLabel();

    void bind();

private:
    Ui::GroupsList ui{};
    QSqlTableModel tableModel;
    FilterModel filterModel;

    void handleRemoveRow(uint);

    void handleEditRow(uint);

    uint getRowIdByIndex(QModelIndex);

public slots:
    void handleRefreshButton();

private slots:
    void handleFiltersButton();

    void viewContextMenu(QPoint);

    void handleDelKey();
};


#endif //SMUUKI_GROUPLIST_H
