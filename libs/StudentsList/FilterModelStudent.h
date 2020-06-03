#ifndef SMUUKI_SFILTERMODEL_H
#define SMUUKI_SFILTERMODEL_H

#include <QSortFilterProxyModel>

class FilterModelStudent: public QSortFilterProxyModel {
public:
    struct FilterInput {
        QString name{""};
        QString surname{""};
        QString group{""};
        QString parent{""};
    };

    explicit FilterModelStudent(QObject *parent = nullptr);

    void setFilterName(QString);
    QString getFilterName();

    void setFilterSurname(QString);
    QString getFilterSurname();

    void setFilterGroup(QString);
    QString getFilterGroup();

    void setFilterParent(QString);
    QString getFilterParent();

protected:
    bool filterAcceptsRow(int, const QModelIndex &) const override;

private:
    FilterInput input;
};

#endif //SMUUKI_SFILTERMODEL_H
