#include "Invoice.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtCore/QVariant>
#include <QRegularExpression>
#include <utility>

Model::Invoice::Invoice() {
    isValid_ = false;
    id_ = 0;
    studentId_ = 0;
    desc_ = QString();
    paidAmount_ = QString();
    paidUntil_ = QDate();
}

Model::Invoice::Invoice(uint id_arg, uint studentId_arg, QString desc_arg, QString paidAmount_arg, const QString& paidUntil_arg, bool isValid_arg) {
    id_ = id_arg;
    isValid_ = isValid_arg;
    studentId_ = studentId_arg;
    desc_ = std::move(desc_arg);
    paidAmount_ = std::move(paidAmount_arg);
    paidUntil_ = stringToDate(paidUntil_arg);
}

uint Model::Invoice::getId() {
    return id_;
}

QString Model::Invoice::getDesc() {
    return desc_;
}

QString Model::Invoice::getPaidAmount() {
    return paidAmount_;
}

QDate Model::Invoice::getPaidUntil() {
    return paidUntil_;
}

uint Model::Invoice::getStudentId() {
    return studentId_;
}

bool Model::Invoice::isValid() {
    return isValid_;
}

bool Model::Invoice::addInvoice(uint studentId_arg, const QString & desc_arg, const QString & paidAmount_arg, const QDate & paidUntil_arg) {
    QSqlQuery query;
    if (
        !isValidDesc(desc_arg) ||
        !isValidPaidAmount(paidAmount_arg) ||
        !isValidPaidUntil(paidUntil_arg) ||
        !isValidPaidUntilUser(studentId_arg, paidUntil_arg)
    ) {
        return false;
    }

    query.prepare("INSERT INTO invoices (id, studentId, desc, paidAmount, paidUntil) VALUES (null, ?, ?, ?, ?)");
    query.addBindValue(studentId_arg);
    query.addBindValue(desc_arg);
    query.addBindValue(paidAmount_arg);
    query.addBindValue(dateToString(paidUntil_arg));
    return query.exec();
}

bool Model::Invoice::removeInvoice(uint id_arg) {
    QSqlQuery query;

    query.prepare("DELETE FROM invoices WHERE id=?;");
    query.addBindValue(id_arg);
    return query.exec();
}

bool Model::Invoice::editInvoice(uint id_arg, uint studentId_arg, const QString & desc_arg, const QString & paidAmount_arg, const QDate & paidUntil_arg) {
    QSqlQuery query;
    if (
        !isValidDesc(desc_arg) ||
        !isValidPaidAmount(paidAmount_arg) ||
        !isValidPaidUntil(paidUntil_arg)
    ) {
        return false;
    }

    query.prepare("UPDATE invoices SET studentId=?, desc=?, paidAmount=?, paidUntil=? WHERE id=?");
    query.addBindValue(studentId_arg);
    query.addBindValue(desc_arg);
    query.addBindValue(paidAmount_arg);
    query.addBindValue(paidUntil_arg);
    query.addBindValue(id_arg);
    return query.exec();
}

Model::Invoice Model::Invoice::getInvoiceById(uint id_arg) {
    QSqlQuery query;

    query.prepare("SELECT * FROM invoices WHERE id=?;");
    query.addBindValue(id_arg);
    query.exec();

    if (!query.next()) {
        return Invoice();
    }

    return Invoice(
            query.value(0).toUInt(),
            query.value(1).toUInt(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString()
            );
}

QList<Model::Invoice> Model::Invoice::getAllInvoices() {
    QList<Invoice> InvoiceList;
    QSqlQuery query;

    query.prepare("SELECT * FROM invoices;");
    query.exec();

    while (query.next()) {
        Invoice curInvoice(
                query.value(0).toUInt(),
                query.value(1).toUInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString()
                );
        InvoiceList.push_back(curInvoice);
    }

    return InvoiceList;
}

bool Model::Invoice::isValidDesc(const QString & value_arg) {
    return true;
}

bool Model::Invoice::isValidPaidAmount(const QString & value_arg) {
    return !(value_arg.isEmpty() || value_arg.isNull()) && value_arg.contains(QRegExp(R"(^\d+.\d{2} PLN$)"));
}

bool Model::Invoice::isValidPaidUntil(const QDate & value_arg) {
    return value_arg.isValid();
}

bool Model::Invoice::isValidPaidUntilFormat(const QString& value_arg) {
    return value_arg.contains(QRegExp(R"(^\d{2}-\d{2}-\d{4}$)"));
}

bool Model::Invoice::isValidPaidUntilUser(uint studentId_arg, const QDate & date_arg) {
    QSqlQuery query;
    query.prepare("SELECT paidUntil FROM invoices WHERE studentId=?");
    query.addBindValue(studentId_arg);
    query.exec();

    while (query.next()) {
        if (stringToDate(query.value(0).toString()) >= date_arg) return false;
    }
    return true;
}

bool Model::Invoice::isValidPaidUntilUser(uint studentId_arg, const QString & date_arg) {
    if (!isValidPaidUntilFormat(date_arg)) return false;
    auto formattedDate{stringToDate(date_arg)};
    return isValidPaidUntilUser(studentId_arg, formattedDate);
}

QString Model::Invoice::dateToString(QDate value_arg) {
    return value_arg.toString("dd-MM-yyyy");
}

QDate Model::Invoice::stringToDate(const QString& value_arg) {
    if (!isValidPaidUntilFormat(value_arg)) return {};
    return QDate::fromString(value_arg, "dd-MM-yyyy");
}
