#ifndef SMUUKI_GROUP_H
#define SMUUKI_GROUP_H

#include <QString>
#include <QtGlobal>

namespace Model {
    class Group {
    public:
        Group(uint, QString, QString, QString, bool isValid = true);

        Group();

        QString getName();

        QString getTeacher();

        QString getSubject();

        uint getId();

        bool isValid();

        static bool addGroup(const QString &, const QString &, const QString &);

        static bool removeGroup(uint);

        static bool editGroup(uint, const QString &, const QString &, const QString &);

        static Group getGroupById(uint);

        static QList<Group> getAllGroups();

        static bool isValidName(const QString &);

        static bool isValidSubject(const QString &);

        static bool isValidTeacher(const QString &);

    private:
        uint id_;
        QString name_;
        QString teacher_;
        QString subject_;
        bool isValid_;
    };
}

#endif //SMUUKI_GROUP_H
