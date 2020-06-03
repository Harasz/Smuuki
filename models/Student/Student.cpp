#include <QFile>
#include <QTextStream>
#include <QtCore/QtCore>
#include <QSqlError>
#include <utility>
#include "Student.h"
#include "../../helpers/Dialog/Dialog.h"

Model::Student::Student() {
    id_= 0;
    name_ = QString();
    surname_ = QString();
    parent_ = QString();
    contact_ = QString();
    groupId_ = 0;
    isValid_ = false;
}

Model::Student::Student(uint id_arg, QString name_arg, QString surname_arg, QString parent_arg, QString contact_arg, uint groupId_arg, bool isValid_arg) {
    id_= id_arg;
    name_ = std::move(name_arg);
    surname_ = std::move(surname_arg);
    parent_ = std::move(parent_arg);
    contact_ = std::move(contact_arg);
    groupId_ = groupId_arg;
    isValid_ = isValid_arg;
}

QString Model::Student::getName() {
    return this->name_;
}

QString Model::Student::getSurname() {
    return this->surname_;
}

QString Model::Student::getParent() {
    return this->parent_;
}

QString Model::Student::getContact() {
    return contact_;
}

uint Model::Student::getId() {
    return id_;
}

uint Model::Student::getGroupId() {
    return groupId_;
}

Model::Group Model::Student::getGroup() {
    return Group::getGroupById(groupId_);
}

bool Model::Student::isValid() {
    return isValid_;
}

bool Model::Student::addStudent(const QString& name_arg, const QString& surname_arg, const QString& parent_arg, const QString& contact_arg, uint groupId_arg) {
    if (
        name_arg.isEmpty() || name_arg.isNull() ||
        surname_arg.isEmpty() || surname_arg.isNull() ||
        parent_arg.isEmpty() || parent_arg.isNull()
    ) {
        return false;
    }

    if (!Group::getGroupById(groupId_arg).isValid()) {
        return false;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO students (id, name, surname, \"group\", parentName, contact) VALUES (null, ?, ?, ?, ?, ?);");
    query.addBindValue(name_arg);
    query.addBindValue(surname_arg);
    query.addBindValue(groupId_arg);
    query.addBindValue(parent_arg);
    query.addBindValue(contact_arg);
    return query.exec();
}

bool Model::Student::removeStudent(uint id_arg) {
    QSqlQuery query;

    query.prepare("DELETE FROM students WHERE id=?;");
    query.addBindValue(id_arg);
    return query.exec();
}

bool Model::Student::editStudent(uint id_arg, const QString& name_arg, const QString& surname_arg, const QString& parent_arg, const QString& contact_arg, uint groupId_arg) {
    QSqlQuery query;
    if (!isValidName(name_arg) || !isValidSurname(surname_arg) || !isValidContact(contact_arg) || !isValidParent(parent_arg)) {
        return false;
    }

    query.prepare("UPDATE students SET name=?, surname=?, \"group\"=?, parentName=?, contact=? WHERE id=?");
    query.addBindValue(name_arg);
    query.addBindValue(surname_arg);
    query.addBindValue(groupId_arg);
    query.addBindValue(parent_arg);
    query.addBindValue(contact_arg);
    query.addBindValue(id_arg);
    return query.exec();
}

Model::Student Model::Student::getStudentById(uint id_arg) {
    QSqlQuery query;

    query.prepare("SELECT * FROM students WHERE id=?;");
    query.addBindValue(id_arg);
    query.exec();

    if (!query.next()) {
        return Student();
    }

    return Student(
            query.value(0).toUInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(3).toUInt()
    );
}

bool Model::Student::isValidName(const QString & value_arg) {
    return !(value_arg.isEmpty() || value_arg.isNull());
}

bool Model::Student::isValidSurname(const QString & value_arg) {
    return !(value_arg.isEmpty() || value_arg.isNull());
}

bool Model::Student::isValidParent(const QString & value_arg) {
    return !(value_arg.isEmpty() || value_arg.isNull());
}

bool Model::Student::isValidContact(const QString & value_arg) {
    return true;
}

QList<Model::Student> Model::Student::getAllStudents() {
    QList<Student> studentList;
    QSqlQuery query;

    query.prepare("SELECT * FROM students;");
    query.exec();

    while (query.next()) {
        Student curStudent(
                query.value(0).toUInt(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(3).toUInt()
        );
        studentList.push_back(curStudent);
    }

    return studentList;
}
