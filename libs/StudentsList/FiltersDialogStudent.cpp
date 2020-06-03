#include "FiltersDialogStudent.h"
#include "../../models/Group/Group.h"
#include <QDebug>
#include <QDialogButtonBox>

FiltersDialogStudent::FiltersDialogStudent(FilterModelStudent *model_arg, QWidget *parent_arg): QDialog(parent_arg), model(model_arg) {
    ui.setupUi(this);
    loadGroupToCombo();

    ui.studentNameInput->setText(model->getFilterName());
    ui.studentParentInput->setText(model->getFilterParent());
    ui.studentSurnameInput->setText(model->getFilterSurname());
    ui.groupCombo->setCurrentIndex(ui.groupCombo->findData(model->getFilterGroup()));

    bindSignals();
}

void FiltersDialogStudent::execFilter() {
    exec();
}

void FiltersDialogStudent::bindSignals() {
    connect(ui.buttonBox, &QDialogButtonBox::clicked, this, &FiltersDialogStudent::click);
}

void FiltersDialogStudent::applyForm() {
    applyFilters();
}


void FiltersDialogStudent::resetForm() {
    ui.studentSurnameInput->clear();
    ui.studentParentInput->clear();
    ui.studentNameInput->clear();
    ui.groupCombo->setCurrentIndex(-1);
    applyFilters();
}

void FiltersDialogStudent::applyFilters() {
    model->setFilterName(ui.studentNameInput->text());
    model->setFilterParent(ui.studentParentInput->text());
    model->setFilterSurname(ui.studentSurnameInput->text());
    model->setFilterGroup(ui.groupCombo->currentData().toString());
}

void FiltersDialogStudent::click(QAbstractButton *button_arg) {
    auto *resetButton{ ui.buttonBox->button(QDialogButtonBox::Reset) };
    auto *applyButton{ ui.buttonBox->button(QDialogButtonBox::Apply) };
    auto *castedButton{ reinterpret_cast<QPushButton*>(button_arg) };

    if (castedButton == applyButton) {
        applyForm();
    } else if (castedButton == resetButton) {
        resetForm();
    }
}

void FiltersDialogStudent::loadGroupToCombo() {
    auto groupList{ Model::Group::getAllGroups() };

    ui.groupCombo->clear();

    for (auto group : groupList) {
        ui.groupCombo->addItem(
                QString("%1 - %2 (%3)").arg(group.getName(), group.getTeacher(), group.getSubject()),
                group.getName()
        );
    }
}
