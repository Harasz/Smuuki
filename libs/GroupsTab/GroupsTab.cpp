#include "GroupsTab.h"
#include "../AddGroupForm/AddGroupForm.h"
#include "../GroupsList/GroupList.h"

GroupsTab::GroupsTab(QWidget *parent_arg): QWidget(parent_arg), ui() {
    ui.setupUi(this);
    this->initTab();
}

GroupsTab *GroupsTab::registerView(QWidget *widget_arg, QLayout *layout_arg) {
    auto *result = new GroupsTab(widget_arg);
    layout_arg->addWidget(result);
    result->hide();
    return result;
}

void GroupsTab::initTab() {
    auto* listGroupTab = new GroupList(ui.groupTabWidget);
    ui.groupTabWidget->addTab(listGroupTab, "listGroupTab");
    ui.groupTabWidget->setTabText(ui.groupTabWidget->indexOf(listGroupTab), tr("Group List"));

    auto* addGroupTab = new AddGroupForm(ui.groupTabWidget);
    ui.groupTabWidget->addTab(addGroupTab, "addGroupTab");
    ui.groupTabWidget->setTabText(ui.groupTabWidget->indexOf(addGroupTab), tr("Add Group"));

    connect(addGroupTab, &AddGroupForm::groupAdded, listGroupTab, &GroupList::handleRefreshButton);
    connect(this, &GroupsTab::refreshTabs, addGroupTab, &AddGroupForm::refreshData);
    connect(this, &GroupsTab::refreshTabs, listGroupTab, &GroupList::handleRefreshButton);
}
