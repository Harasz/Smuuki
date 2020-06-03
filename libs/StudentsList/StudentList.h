#ifndef SMUUKI_STUDENTLIST_H
#define SMUUKI_STUDENTLIST_H

#include "FilterModelStudent.h"
#include "FiltersDialogStudent.h"
#include "../../forms/StudentsTab/ui_studentlist.h"
#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QPoint>
#include <QVariant>

class StudentList: public QWidget {
Q_OBJECT
public:
    explicit StudentList(QWidget* parent = nullptr);

    void initTableModel();

    void refreshList();

    void updateInfoLabel();

    void bind();

private:
    Ui::StudentsList ui{};
    QSqlRelationalTableModel tableModel;
    FilterModelStudent filterModel;

    void handleRemoveRow(uint);

    uint getRowIdByIndex(QModelIndex);

public slots:
    void handleRefreshButton();

private slots:
    void handleFiltersButton();

    void viewContextMenu(QPoint);

    void handleDelKey();

    void handleEditRow(uint);

    void handleAddPayment(uint);
};


#endif //SMUUKI_STUDENTLIST_H
