#include "FilterModelInvoice.h"
#include "../../models/Invoice/Invoice.h"
#include <utility>
#include <QSqlQuery>

FilterModelInvoice::FilterModelInvoice(QObject *parent_arg) : QSortFilterProxyModel(parent_arg) {}

void FilterModelInvoice::setFilterStudent(QString value_arg) {
    input.student = std::move(value_arg);
    invalidateFilter();
}

QString FilterModelInvoice::getFilterStudent() {
    return input.student;
}

void FilterModelInvoice::setFilterGroup(QString value_arg) {
    input.group = std::move(value_arg);
    invalidateFilter();
}

QString FilterModelInvoice::getFilterGroup() {
    return input.group;
}

void FilterModelInvoice::setFilterPaidUntil(QDate value_arg) {
    input.paidUntil = value_arg;
    invalidateFilter();
}

QDate FilterModelInvoice::getFilterPaidUntil() {
    return input.paidUntil;
}

void FilterModelInvoice::setFilterIsPaidUntilActive(bool value_arg) {
    input.isPaidUntilActive = value_arg;
}

bool FilterModelInvoice::getFilterIsPaidUntilActive() {
    return input.isPaidUntilActive;
}

bool FilterModelInvoice::filterAcceptsRow(int sourceRow_arg, const QModelIndex &sourceParent_arg) const {
    QModelIndex index0{ sourceModel()->index(sourceRow_arg, 0, sourceParent_arg) };
    QModelIndex index5{ sourceModel()->index(sourceRow_arg, 5, sourceParent_arg) };
    bool result{ true };

    QSqlQuery query;
    query.prepare("SELECT groups.name, students.id FROM groups, students, invoices WHERE students.\"group\" = groups.id AND invoices.studentId = students.id AND invoices.id = ?");
    query.addBindValue(index0.data().toUInt());
    query.exec();
    query.next();

    if (!input.student.isEmpty() && !input.student.isNull()) {
        result = result && query.value(1).toString() == input.student;
    }

    if (!input.group.isEmpty() && !input.group.isNull()) {
        result = result && query.value(0).toString() == input.group;
    }

    if (input.isPaidUntilActive) {
        result = result && Model::Invoice::stringToDate(sourceModel()->data(index5).toString()) >= input.paidUntil;
    }

    return result;
}
