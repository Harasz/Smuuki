#ifndef SMUUKI_SFILTERSDIALOG_H
#define SMUUKI_SFILTERSDIALOG_H

#include "../../forms/StudentsTab/ui_studentlistfilters.h"
#include "FilterModelStudent.h"
#include <QDialog>
#include <QAbstractButton>

class FiltersDialogStudent: public QDialog {
Q_OBJECT
public:
    explicit FiltersDialogStudent(FilterModelStudent *, QWidget *parent = nullptr);

    void execFilter();

    void bindSignals();

private:
    Ui::StudentListFilters ui{};
    FilterModelStudent *model;

    void applyFilters();

    void loadGroupToCombo();

private slots:
    void resetForm();

    void applyForm();

    void click(QAbstractButton *);
};


#endif //SMUUKI_SFILTERSDIALOG_H
