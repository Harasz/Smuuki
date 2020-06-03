#include "StudentsTab.h"
#include "../AddStudentForm/AddStudentForm.h"
#include "../StudentsList/StudentList.h"

StudentsTab::StudentsTab(QWidget *parent_arg): QWidget(parent_arg), ui() {
    ui.setupUi(this);
    initTab();
}

StudentsTab *StudentsTab::registerView(QWidget *widget_arg, QLayout *layout_arg) {
    auto *result = new StudentsTab(widget_arg);
    layout_arg->addWidget(result);
    result->hide();
    return result;
}

void StudentsTab::initTab() {
    auto* listStudentTab = new StudentList(ui.studentTabWidget);
    ui.studentTabWidget->addTab(listStudentTab, "listStudentTab");
    ui.studentTabWidget->setTabText(ui.studentTabWidget->indexOf(listStudentTab), tr("Student List"));

    auto* addStudentTab = new AddStudentForm(ui.studentTabWidget);
    ui.studentTabWidget->addTab(addStudentTab, "addStudentTab");
    ui.studentTabWidget->setTabText(ui.studentTabWidget->indexOf(addStudentTab), tr("Add Student"));

    connect(addStudentTab, &AddStudentForm::studentAdded, listStudentTab, &StudentList::handleRefreshButton);
    connect(this, &StudentsTab::refreshTabs, listStudentTab, &StudentList::handleRefreshButton);
    connect(this, &StudentsTab::refreshTabs, addStudentTab, &AddStudentForm::refreshData);
}
