#include "FilterModelStudent.h"
#include <utility>

FilterModelStudent::FilterModelStudent(QObject *parent_arg) : QSortFilterProxyModel(parent_arg) {}

void FilterModelStudent::setFilterName(QString value_arg) {
    input.name = std::move(value_arg);
    invalidateFilter();
}

QString FilterModelStudent::getFilterName() {
    return input.name;
}

void FilterModelStudent::setFilterSurname(QString value_arg) {
    input.surname = std::move(value_arg);
    invalidateFilter();
}

QString FilterModelStudent::getFilterSurname() {
    return input.surname;
}

void FilterModelStudent::setFilterGroup(QString value_arg) {
    input.group = std::move(value_arg);
    invalidateFilter();
}

QString FilterModelStudent::getFilterGroup() {
    return input.group;
}

void FilterModelStudent::setFilterParent(QString value_arg) {
    input.parent = std::move(value_arg);
    invalidateFilter();
}

QString FilterModelStudent::getFilterParent() {
    return input.parent;
}

bool FilterModelStudent::filterAcceptsRow(int sourceRow_arg, const QModelIndex &sourceParent_arg) const {
    QModelIndex index1{ sourceModel()->index(sourceRow_arg, 1, sourceParent_arg) };
    QModelIndex index2{ sourceModel()->index(sourceRow_arg, 2, sourceParent_arg) };
    QModelIndex index3{ sourceModel()->index(sourceRow_arg, 3, sourceParent_arg) };
    QModelIndex index4{ sourceModel()->index(sourceRow_arg, 4, sourceParent_arg) };
    bool result{ true };

    if (!input.name.isEmpty() && !input.name.isNull()) {
        result = result && sourceModel()->data(index1).toString().toLower().contains(input.name.toLower());
    }

    if (!input.surname.isEmpty() && !input.surname.isNull()) {
        result = result && sourceModel()->data(index2).toString().toLower().contains(input.surname.toLower());
    }

    if (!input.parent.isEmpty() && !input.parent.isNull()) {
        result = result && sourceModel()->data(index4).toString().toLower().contains(input.parent.toLower());
    }

    if (!input.group.isEmpty() && !input.group.isNull()) {
        result = result && sourceModel()->data(index3).toString() == input.group;
    }

    return result;
}
