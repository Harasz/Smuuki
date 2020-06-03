#ifndef SMUUKI_IFILTERMODEL_H
#define SMUUKI_IFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QDate>

class FilterModelInvoice: public QSortFilterProxyModel {
public:
    struct FilterInput {
        QString student{""};
        QString group{""};
        QDate paidUntil{};
        bool isPaidUntilActive{false};
    };

    explicit FilterModelInvoice(QObject *parent = nullptr);

    void setFilterStudent(QString);
    QString getFilterStudent();

    void setFilterGroup(QString);
    QString getFilterGroup();

    void setFilterPaidUntil(QDate);
    QDate getFilterPaidUntil();

    void setFilterIsPaidUntilActive(bool);
    bool getFilterIsPaidUntilActive();

protected:
    bool filterAcceptsRow(int, const QModelIndex &) const override;

private:
    FilterInput input;
};


#endif //SMUUKI_IFILTERMODEL_H
