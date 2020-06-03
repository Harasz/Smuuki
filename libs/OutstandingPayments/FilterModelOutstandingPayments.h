#ifndef SMUUKI_OFILTERMODEL_H
#define SMUUKI_OFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QDate>

class FilterModelOutstandingPayments: public QSortFilterProxyModel {
public:
    explicit FilterModelOutstandingPayments(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int, const QModelIndex &) const override;
};

#endif //SMUUKI_OFILTERMODEL_H
