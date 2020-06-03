#include "FilterModel.h"
#include <utility>

FilterModel::FilterModel(QObject *parent_arg) : QSortFilterProxyModel(parent_arg) {}

void FilterModel::setFilterName(QString value_arg) {
    input.name = std::move(value_arg);
    invalidateFilter();
}

QString FilterModel::getFilterName() {
    return input.name;
}

void FilterModel::setFilterTeacher(QString value_arg) {
    input.teacher = std::move(value_arg);
    invalidateFilter();
}

QString FilterModel::getFilterTeacher() {
    return input.teacher;
}

void FilterModel::setFilterSubject(QString value_arg) {
    input.subject = std::move(value_arg);
    invalidateFilter();
}

QString FilterModel::getFilterSubject() {
    return input.subject;
}

bool FilterModel::filterAcceptsRow(int sourceRow_arg, const QModelIndex &sourceParent_arg) const {
    QModelIndex index1{ sourceModel()->index(sourceRow_arg, 1, sourceParent_arg) };
    QModelIndex index2{ sourceModel()->index(sourceRow_arg, 2, sourceParent_arg) };
    QModelIndex index3{ sourceModel()->index(sourceRow_arg, 3, sourceParent_arg) };
    bool result{ true };

    if (!input.name.isEmpty() && !input.name.isNull()) {
        result = result && sourceModel()->data(index1).toString().toLower().contains(input.name.toLower());
    }

    if (!input.teacher.isEmpty() && !input.teacher.isNull()) {
        result = result && sourceModel()->data(index2).toString().toLower().contains(input.teacher.toLower());
    }

    if (!input.subject.isEmpty() && !input.subject.isNull()) {
        result = result && sourceModel()->data(index3).toString().toLower().contains(input.subject.toLower());
    }

    return result;
}
