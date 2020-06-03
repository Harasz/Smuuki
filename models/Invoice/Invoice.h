#ifndef SMUUKI_INVOICE_H
#define SMUUKI_INVOICE_H

#include <QString>
#include <QDate>
#include <QtGlobal>

namespace Model {
    class Invoice {
    public:
        Invoice(uint, uint, QString, QString, const QString&, bool isValid = true);

        Invoice();

        QString getDesc();

        QString getPaidAmount();

        QDate getPaidUntil();

        uint getId();

        uint getStudentId();

        bool isValid();

        static bool addInvoice(uint, const QString &, const QString &, const QDate &);

        static bool removeInvoice(uint);

        static bool editInvoice(uint, uint, const QString &, const QString &, const QDate &);

        static Invoice getInvoiceById(uint);

        static QList<Invoice> getAllInvoices();

        static bool isValidDesc(const QString &);

        static bool isValidPaidAmount(const QString &);

        static bool isValidPaidUntil(const QDate &);

        static bool isValidPaidUntilFormat(const QString &);

        static bool isValidPaidUntilUser(uint, const QString &);

        static bool isValidPaidUntilUser(uint, const QDate &);

        static QString dateToString(QDate);

        static QDate stringToDate(const QString&);

    private:
        uint id_;
        uint studentId_;
        QString desc_;
        QDate paidUntil_;
        QString paidAmount_;
        bool isValid_;
    };
}

#endif //SMUUKI_INVOICE_H
