#ifndef SMUUKI_GROUPSTAB_H
#define SMUUKI_GROUPSTAB_H

#include "../../forms/GroupsTab/ui_groupstab.h"
#include <QWidget>

class GroupsTab : public QWidget {
Q_OBJECT
public:
    explicit GroupsTab(QWidget *parent = nullptr);
    static GroupsTab *registerView(QWidget *, QLayout *);

    void showEvent(QShowEvent* event_arg) override {
        QWidget::showEvent(event_arg);
        emit refreshTabs();
    }

private:
    Ui::GroupsListForm ui;

    void initTab();
signals:
    void refreshTabs();
};


#endif //SMUUKI_GROUPSTAB_H
