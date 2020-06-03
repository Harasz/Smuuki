QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += release

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    models/Student/Student.cpp \
    models/Group/Group.cpp \
    models/Invoice/Invoice.cpp \
    libs/MainWindow/MainWindow.cpp \
    libs/StudentsTab/StudentsTab.cpp \
    libs/GroupsTab/GroupsTab.cpp \
            libs/InvoiceTab/InvoicesTab.cpp  \
            libs/GroupsList/GroupList.cpp \
            libs/GroupsList/FiltersDialog.cpp  \
            libs/GroupsList/FilterModel.cpp \
            libs/StudentsList/StudentList.cpp \
            libs/StudentsList/FiltersDialogStudent.cpp \
            libs/StudentsList/FilterModelStudent.cpp \
            libs/DatabasePasswordDialog/DatabasePasswordDialog.cpp \
            libs/AddGroupForm/AddGroupForm.cpp \
            libs/AddStudentForm/AddStudentForm.cpp \
            libs/EditStudentForm/EditStudentForm.cpp \
            libs/EditGroupForm/EditStudentForm.cpp \
            libs/InvoicesList/InvoicesList.cpp  \
            libs/InvoicesList/FilterModelInvoice.cpp \
            libs/InvoicesList/FiltersDialogInvoice.cpp \
            libs/AddInvoiceForm/AddInvoiceForm.cpp \
            libs/Settings/Settings.cpp \
            libs/OutstandingPayments/OutstandingPayments.cpp \
            helpers/Dialog/Dialog.cpp \

HEADERS += \
     helpers/Dialog/Dialog.h \
     libs/Settings/Settings.h \
     libs/AddInvoiceForm/AddInvoiceForm.h \
     libs/InvoicesList/FiltersDialogInvoice.h \
     libs/InvoicesList/FilterModelInvoice.h \
     libs/InvoicesList/InvoicesList.h \
     libs/EditGroupForm/EditGroupForm.h \
     libs/EditStudentForm/EditStudentForm.h \
     libs/AddStudentForm/AddStudentForm.h \
     libs/AddGroupForm/AddGroupForm.h \
     libs/DatabasePasswordDialog/DatabasePasswordDialog.h \
     libs/StudentsList/FilterModelStudent.h \
     libs/StudentsList/FiltersDialogStudent.h \
     libs/StudentsList/StudentList.h \
     libs/GroupsList/FilterModel.h \
     libs/GroupsList/FiltersDialog.h \
     libs/GroupsList/GroupList.h \
     libs/InvoiceTab/InvoicesTab.h \
     libs/GroupsTab/GroupsTab.h \
     libs/StudentsTab/StudentsTab.h \
     libs/MainWindow/MainWindow.h \
     libs/OutstandingPayments/OutstandingPayments.h \
     models/Invoice/Invoice.h \
     models/Group/Group.h \
     models/Student/Student.h

FORMS += \
    forms/MainWindow/MainWindow.ui \
    forms/StudentsTab/AddStudentForm.ui \
    forms/StudentsTab/EditStudentForm.ui \
    forms/StudentsTab/StudentList.ui \
    forms/StudentsTab/StudentListFilters.ui \
    forms/StudentsTab/StudentTab.ui \
    forms/Settings/Settings.ui \
    forms/InvoiceTab/AddInvoiceForm.ui \
    forms/InvoiceTab/AddInvoiceFormDialog.ui \
    forms/InvoiceTab/AddInvoiceFormWrapper.ui \
    forms/InvoiceTab/InvoiceList.ui \
    forms/InvoiceTab/InvoicesListFilters.ui \
    forms/InvoiceTab/InvoicesTab.ui \
    forms/GroupsTab/AddGroupForm.ui \
    forms/GroupsTab/EditGroupForm.ui \
    forms/GroupsTab/GroupsList.ui \
    forms/GroupsTab/GroupsListFilters.ui \
    forms/GroupsTab/GroupsTab.ui \
    forms/DatabasePasswordDialog/PasswordDialog.ui \
    forms/MainWindow/OutstandingPayments.ui

TRANSLATIONS += \
    translations/smuuki_PL.ts \
    translations/smuuki_EN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
