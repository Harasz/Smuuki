#ifndef SMUUKI_FILTERSDIALOG_H
#define SMUUKI_FILTERSDIALOG_H

#include "../../forms/GroupsTab/ui_groupslistfilters.h"
#include "FilterModel.h"
#include <QDialog>
#include <QAbstractButton>

class FiltersDialog: public QDialog {
Q_OBJECT
public:
    explicit FiltersDialog(FilterModel*, QWidget *parent = nullptr);

    void execFilter();

    void bindSignals();

private:
    Ui::GroupListFilters ui{};
    FilterModel *model;

    void applyFilters();

private slots:
    void resetForm();
    void applyForm();

    void click(QAbstractButton *button);
};


#endif //SMUUKI_FILTERSDIALOG_H
