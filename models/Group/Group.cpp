#include "Group.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtCore/QVariant>
#include <utility>

Model::Group::Group() {
    isValid_ = false;
    id_ = 0;
    name_ = QString();
    teacher_= QString();
    subject_ = QString();
}

Model::Group::Group(uint id_arg, QString name_arg, QString teacher_arg, QString subject_arg, bool isValid_arg) {
    id_ = id_arg;
    isValid_ = isValid_arg;
    name_ = std::move(name_arg);
    teacher_= std::move(teacher_arg);
    subject_ = std::move(subject_arg);
}

QString Model::Group::getName() {
    return name_;
}

QString Model::Group::getTeacher() {
    return teacher_;
}

QString Model::Group::getSubject() {
    return subject_;
}

uint Model::Group::getId() {
    return id_;
}

bool Model::Group::isValid() {
    return isValid_;
}

bool Model::Group::addGroup(const QString& name_arg, const QString& teacher_arg, const QString& subject_arg) {
    QSqlQuery query;
    if (!isValidName(name_arg) || !isValidSubject(subject_arg) || !isValidTeacher(teacher_arg)) {
        return false;
    }

    query.prepare("INSERT INTO groups (id, name, teacher, subject) VALUES (null, ?, ?, ?)");
    query.addBindValue(name_arg);
    query.addBindValue(teacher_arg);
    query.addBindValue(subject_arg);
    return query.exec();
}

bool Model::Group::removeGroup(uint id_arg) {
    QSqlQuery query;

    query.prepare("DELETE FROM groups WHERE id=?;");
    query.addBindValue(id_arg);
    return query.exec();
}

bool Model::Group::editGroup(uint id_arg, const QString & name_arg, const QString & teacher_arg, const QString & subject_arg) {
    QSqlQuery query;
    if (!isValidName(name_arg) || !isValidSubject(subject_arg) || !isValidTeacher(teacher_arg)) {
        return false;
    }

    query.prepare("UPDATE groups SET name=?, teacher=?, subject=? WHERE id=?");
    query.addBindValue(name_arg);
    query.addBindValue(teacher_arg);
    query.addBindValue(subject_arg);
    query.addBindValue(id_arg);
    return query.exec();
}

Model::Group Model::Group::getGroupById(uint id_arg) {
    QSqlQuery query;

    query.prepare("SELECT * FROM groups WHERE id=?;");
    query.addBindValue(id_arg);
    query.exec();

    if (!query.next()) {
        return Group();
    }

    return Group(
            query.value(0).toUInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString()
            );
}

QList<Model::Group> Model::Group::getAllGroups() {
    QList<Group> groupList;
    QSqlQuery query;

    query.prepare("SELECT * FROM groups;");
    query.exec();

    while (query.next()) {
        Group curGroup(
                query.value(0).toUInt(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(3).toString()
                );
        groupList.push_back(curGroup);
    }

    return groupList;
}

bool Model::Group::isValidName(const QString & value_arg) {
    return !(value_arg.isEmpty() || value_arg.isNull());
}

bool Model::Group::isValidSubject(const QString & value_arg) {
    return !(value_arg.isEmpty() || value_arg.isNull());
}

bool Model::Group::isValidTeacher(const QString & value_arg) {
    return !(value_arg.isEmpty() || value_arg.isNull());
}
