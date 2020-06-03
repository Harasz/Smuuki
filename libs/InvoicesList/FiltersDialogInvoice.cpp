#include "FiltersDialogInvoice.h"
#include "../../models/Group/Group.h"
#include "../../models/Student/Student.h"
#include <QDebug>
#include <QDialogButtonBox>

FiltersDialogInvoice::FiltersDialogInvoice(FilterModelInvoice *model_arg, QWidget *parent_arg): QDialog(parent_arg), model(model_arg) {
    ui.setupUi(this);
    loadGroupToCombo();
    loadStudentToCombo();

    ui.studentCombo->setCurrentIndex(ui.studentCombo->findData(model->getFilterStudent()));
    ui.groupCombo->setCurrentIndex(ui.groupCombo->findData(model->getFilterGroup()));
    if (model->getFilterIsPaidUntilActive()) {
        ui.paidUntilDate->setDate(model->getFilterPaidUntil());
    }

    bindSignals();
}

void FiltersDialogInvoice::execFilter() {
    exec();
}

void FiltersDialogInvoice::bindSignals() {
    connect(ui.buttonBox, &QDialogButtonBox::clicked, this, &FiltersDialogInvoice::click);
    connect(ui.paidUntilDate, &QDateTimeEdit::dateChanged, this, &FiltersDialogInvoice::dateChanged);
}

void FiltersDialogInvoice::applyForm() {
    applyFilters();
}


void FiltersDialogInvoice::resetForm() {
    ui.studentCombo->setCurrentIndex(-1);
    ui.groupCombo->setCurrentIndex(-1);
    ui.paidUntilDate->setDate(QDate());
    model->setFilterIsPaidUntilActive(false);
    applyFilters();
}

void FiltersDialogInvoice::applyFilters() {
    model->setFilterStudent(ui.studentCombo->currentData().toString());
    model->setFilterGroup(ui.groupCombo->currentData().toString());
    model->setFilterPaidUntil(ui.paidUntilDate->date());
}

void FiltersDialogInvoice::click(QAbstractButton *button) {
    auto *resetButton{ ui.buttonBox->button(QDialogButtonBox::Reset) };
    auto *applyButton{ ui.buttonBox->button(QDialogButtonBox::Apply) };
    auto *castedButton{ reinterpret_cast<QPushButton*>(button) };

    if (castedButton == applyButton) {
        applyForm();
    } else if (castedButton == resetButton) {
        resetForm();
    }
}

void FiltersDialogInvoice::loadGroupToCombo() {
    auto groupList{ Model::Group::getAllGroups() };

    ui.groupCombo->clear();

    for (auto group : groupList) {
        ui.groupCombo->addItem(
                QString("%1 - %2 (%3)").arg(group.getName(), group.getTeacher(), group.getSubject()),
                group.getName()
        );
    }
}

void FiltersDialogInvoice::loadStudentToCombo() {
    auto studentList{ Model::Student::getAllStudents() };

    ui.studentCombo->clear();

    for (auto student : studentList) {
        ui.studentCombo->addItem(
                QString("%1 %2 (ID: %3)").arg(student.getName(), student.getSurname(), QString::number(student.getId())),
                student.getId()
        );
    }
}

void FiltersDialogInvoice::dateChanged() {
    model->setFilterIsPaidUntilActive(true);
}
