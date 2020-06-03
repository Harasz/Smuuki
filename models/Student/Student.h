#ifndef SMUUKI_STUDENT_H
#define SMUUKI_STUDENT_H

#include "../Group/Group.h"
#include <QString>
#include <QList>
#include <QtSql/QSqlQuery>

namespace Model {
    class Student {
    public:
        Student();

        Student(uint, QString, QString, QString, QString, uint, bool isValid = true);

        QString getName();

        QString getSurname();

        QString getParent();

        QString getContact();

        uint getId();

        uint getGroupId();

        Group getGroup();

        bool isValid();

        static bool addStudent(const QString&, const QString&, const QString&, const QString&, uint);

        static bool removeStudent(uint);

        static bool editStudent(uint, const QString&, const QString&, const QString&, const QString&, uint);

        static Student getStudentById(uint);

        static QList<Student> getAllStudents();

        static bool isValidName(const QString&);

        static bool isValidSurname(const QString&);

        static bool isValidParent(const QString&);

        static bool isValidContact(const QString&);

    private:
        uint id_;
        QString name_;
        QString surname_;
        QString parent_;
        QString contact_;
        uint groupId_;
        bool isValid_;
    };
}

#endif //SMUUKI_STUDENT_H
