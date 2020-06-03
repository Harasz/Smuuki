#include "FiltersDialog.h"
#include <QDebug>
#include <QDialogButtonBox>

FiltersDialog::FiltersDialog(FilterModel *model_arg, QWidget *parent_arg): QDialog(parent_arg), model(model_arg) {
    ui.setupUi(this);
    ui.groupNameInput->setText(model->getFilterName());
    ui.groupSubjectInput->setText(model->getFilterSubject());
    ui.groupTeacherInput->setText(model->getFilterTeacher());

    bindSignals();
}

void FiltersDialog::execFilter() {
    this->exec();
}

void FiltersDialog::bindSignals() {
    connect(ui.buttonBox, &QDialogButtonBox::clicked, this, &FiltersDialog::click);
}

void FiltersDialog::applyForm() {
    applyFilters();
}


void FiltersDialog::resetForm() {
    ui.groupNameInput->clear();
    ui.groupSubjectInput->clear();
    ui.groupTeacherInput->clear();
    applyFilters();
}

void FiltersDialog::applyFilters() {
    model->setFilterName(ui.groupNameInput->text());
    model->setFilterSubject(ui.groupSubjectInput->text());
    model->setFilterTeacher(ui.groupTeacherInput->text());
}

void FiltersDialog::click(QAbstractButton *button) {
    auto *resetButton{ ui.buttonBox->button(QDialogButtonBox::Reset) };
    auto *applyButton{ ui.buttonBox->button(QDialogButtonBox::Apply) };
    auto *castedButton{ reinterpret_cast<QPushButton*>(button) };
    if (castedButton == applyButton) {
        applyForm();
    } else if (castedButton == resetButton) {
        resetForm();
    }
}
