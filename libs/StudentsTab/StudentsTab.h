#ifndef SMUUKI_STUDENTSTAB_H
#define SMUUKI_STUDENTSTAB_H

#include "../../forms/StudentsTab/ui_studenttab.h"
#include <QWidget>
#include <QLayout>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

class StudentsTab : public QWidget {
Q_OBJECT
public:
    explicit StudentsTab(QWidget *parent = nullptr);
    static StudentsTab *registerView(QWidget *, QLayout *);

    void showEvent(QShowEvent* event_arg) override {
        QWidget::showEvent(event_arg);
        emit refreshTabs();
    }

private:
    Ui::StudentTab ui;

    void initTab();

signals:
    void refreshTabs();
};


#endif //SMUUKI_STUDENTSTAB_H
