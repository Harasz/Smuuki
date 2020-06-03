cmake_minimum_required(VERSION 3.1.0)

project(Smuuki)

set(CMAKE_PREFIX_PATH "J:\\Qt\\5.14.1\\mingw73_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()


find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

list(APPEND SourceList main.cpp)

# TRANSLATION
list(APPEND SourceList
        translations/smuuki_EN.ts
        translations/smuuki_PL.ts
        )
configure_file(translations/smuuki_EN.qm translations/smuuki_EN.qm COPYONLY)
configure_file(translations/smuuki_PL.qm translations/smuuki_PL.qm COPYONLY)

# RESOURCES
list(APPEND SourceList
        sql.qrc
        )

# LIBS
list(APPEND SourceList
        models/Student/Student.cpp models/Student/Student.h
        models/Group/Group.cpp models/Group/Group.h
        models/Invoice/Invoice.cpp models/Invoice/Invoice.h
        libs/MainWindow/MainWindow.cpp libs/MainWindow/MainWindow.h
        libs/StudentsTab/StudentsTab.cpp libs/StudentsTab/StudentsTab.h
        libs/GroupsTab/GroupsTab.cpp libs/GroupsTab/GroupsTab.h
        libs/InvoiceTab/InvoicesTab.cpp libs/InvoiceTab/InvoicesTab.h
        libs/GroupsList/GroupList.cpp libs/GroupsList/GroupList.h
        libs/GroupsList/FiltersDialog.cpp libs/GroupsList/FiltersDialog.h
        libs/GroupsList/FilterModel.cpp libs/GroupsList/FilterModel.h
        libs/StudentsList/StudentList.cpp libs/StudentsList/StudentList.h
        libs/StudentsList/FiltersDialogStudent.cpp libs/StudentsList/FiltersDialogStudent.h
        libs/StudentsList/FilterModelStudent.cpp libs/StudentsList/FilterModelStudent.h
        libs/DatabasePasswordDialog/DatabasePasswordDialog.cpp libs/DatabasePasswordDialog/DatabasePasswordDialog.h
        libs/AddGroupForm/AddGroupForm.cpp libs/AddGroupForm/AddGroupForm.h
        libs/AddStudentForm/AddStudentForm.cpp libs/AddStudentForm/AddStudentForm.h
        libs/EditStudentForm/EditStudentForm.cpp libs/EditStudentForm/EditStudentForm.h
        libs/EditGroupForm/EditStudentForm.cpp libs/EditGroupForm/EditGroupForm.h
        libs/InvoicesList/InvoicesList.cpp libs/InvoicesList/InvoicesList.h
        libs/InvoicesList/FilterModelInvoice.cpp libs/InvoicesList/FilterModelInvoice.h
        libs/InvoicesList/FiltersDialogInvoice.cpp libs/InvoicesList/FiltersDialogInvoice.h
        libs/AddInvoiceForm/AddInvoiceForm.cpp libs/AddInvoiceForm/AddInvoiceForm.h
        libs/Settings/Settings.cpp libs/Settings/Settings.h
        helpers/Dialog/Dialog.cpp helpers/Dialog/Dialog.h
        libs/EditInvoiceForm/EditInvoiceForm.cpp libs/EditInvoiceForm/EditInvoiceForm.h
        libs/OutstandingPayments/OutstandingPayments.cpp libs/OutstandingPayments/OutstandingPayments.h
        libs/OutstandingPayments/FilterModelOutstandingPayments.cpp libs/OutstandingPayments/FilterModelOutstandingPayments.h
        )

add_executable(Smuuki WIN32 ${SourceList})
target_link_libraries(Smuuki Qt5::Widgets Qt5::Sql)