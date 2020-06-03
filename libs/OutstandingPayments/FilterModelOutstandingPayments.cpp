#include "FilterModelOutstandingPayments.h"
#include "../../models/Invoice/Invoice.h"
#include <QDebug>

FilterModelOutstandingPayments::FilterModelOutstandingPayments(QObject *parent_arg) : QSortFilterProxyModel(parent_arg) {}

bool FilterModelOutstandingPayments::filterAcceptsRow(int sourceRow_arg, const QModelIndex &sourceParent_arg) const {
    QModelIndex index5{ sourceModel()->index(sourceRow_arg, 5, sourceParent_arg) };
    return Model::Invoice::stringToDate(sourceModel()->data(index5).toString()) <= QDate::currentDate();
}
