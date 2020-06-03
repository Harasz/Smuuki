#ifndef SMUUKI_FILTERMODEL_H
#define SMUUKI_FILTERMODEL_H

#include <QSortFilterProxyModel>

class FilterModel: public QSortFilterProxyModel {
public:
    struct FilterInput {
        QString name{""};
        QString teacher{""};
        QString subject{""};
    };

    explicit FilterModel(QObject *parent = nullptr);

    void setFilterName(QString);
    QString getFilterName();

    void setFilterTeacher(QString);
    QString getFilterTeacher();

    void setFilterSubject(QString);
    QString getFilterSubject();

protected:
    bool filterAcceptsRow(int, const QModelIndex &) const override;

private:
    FilterInput input;
};


#endif //SMUUKI_FILTERMODEL_H
