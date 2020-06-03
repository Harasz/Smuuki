#include "MainWindow.h"
#include "../StudentsTab/StudentsTab.h"
#include "../GroupsTab/GroupsTab.h"
#include "../InvoiceTab/InvoicesTab.h"
#include "../Settings/Settings.h"
#include "../OutstandingPayments/OutstandingPayments.h"
#include "../../helpers/Dialog/Dialog.h"
#include "../DatabasePasswordDialog/DatabasePasswordDialog.h"
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>
#include <QFile>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDirIterator>
#include <QPushButton>

MainWindow::MainWindow() : QMainWindow(), ui(), translator() {
    ui.setupUi(this);
    loadSettings();
    loadLang();
    initDatabase();

    bindButtons();
    registerViews();

    changeActiveButton(ui.studentsTabButton);
    changeView("studentsTabButton");
    showOutstandingPayments();
}

void MainWindow::changeActiveButton(QPushButton *btn_arg) {
    btn_arg->setProperty("active", true);
    if (activeButton != nullptr) {
        activeButton->setProperty("active", false);
        MainWindow::updateStyle(activeButton);
    }
    MainWindow::updateStyle(btn_arg);
    activeButton = btn_arg;
}

void MainWindow::handleButtonClick() {
    auto *clickedButton{ qobject_cast<QPushButton *>(sender()) };

    if (clickedButton) {
        changeActiveButton(clickedButton);
        changeView(clickedButton->objectName());
    }
}

void MainWindow::bindButtons() {
    connect(ui.studentsTabButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui.groupsTabButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui.invoicesTabButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui.settingsTabButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
}

MainWindow::~MainWindow() {
    delete activeButton;
}

void MainWindow::updateStyle(QWidget *object_arg) {
    object_arg->style()->unpolish(object_arg);
    object_arg->style()->polish(object_arg);
}

void MainWindow::changeView(const QString &name_arg) {
    if (activeView != nullptr) {
        activeView->hide();
    }
    viewsMap[name_arg]->show();
    activeView = viewsMap[name_arg];
}

void MainWindow::registerViews() {
    viewsMap.insert(std::pair<QString, QWidget *>("studentsTabButton",
                                                  StudentsTab::registerView(ui.mainWidget, ui.mainWidgetLayout)));
    viewsMap.insert(std::pair<QString, QWidget *>("invoicesTabButton",
                                                  InvoicesTab::registerView(ui.mainWidget, ui.mainWidgetLayout)));
    viewsMap.insert(std::pair<QString, QWidget *>("groupsTabButton",
                                                  GroupsTab::registerView(ui.mainWidget, ui.mainWidgetLayout)));
    viewsMap.insert(std::pair<QString, QWidget *>("settingsTabButton",
                                                  Settings::registerView(ui.mainWidget, ui.mainWidgetLayout, &settings)));
}

void MainWindow::loadSettings() {
    settings.dataDirPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    settings.settingsFilePath = settings.dataDirPath + +"/config.ini";
    QSettings settingsObject(
            settings.settingsFilePath,
            QSettings::IniFormat
    );

    if (!settingsObject.contains("database")) {
        settingsObject.setValue("database", settings.dataDirPath + "/database.sqlite");
        settingsObject.sync();
    }

    settings.dbFilePath = settingsObject.value("database").toString();

    QString defaultLocale = QLocale::system().name();
    settings.lang = settingsObject.value("lang", defaultLocale).toString();
}

void MainWindow::initDatabase() {
    bool isCreatedDatabaseFile{ false };

    if (!QSqlDatabase::isDriverAvailable("SQLITECIPHER")) {
        Dialog::showFatalError(tr("Cannot load database driver."), true);
    }

    if (!QFile::exists(settings.dbFilePath)) {
        isCreatedDatabaseFile = true;
    }

    DatabasePasswordDialog passwordDialog(isCreatedDatabaseFile);

    auto database{ QSqlDatabase::addDatabase("SQLITECIPHER") };
    database.setDatabaseName(settings.dbFilePath);

    while (true) {
        database.setPassword(passwordDialog.getPassword());
        if (isCreatedDatabaseFile) {
            database.setConnectOptions("QSQLITE_CREATE_KEY");
        }

        if (!database.open()) {
            if ("Invalid password. Maybe cipher not match?" == database.lastError().driverText()) {
                Dialog::showFatalError(tr("Invalid database password."), false);
            } else {
                Dialog::showFatalError(tr("Cannot open database."), true);
            }
        } else {
            break;
        }
    }

    QSqlQuery query;
    QDirIterator it(":SQLTable/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFile file(it.next());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            Dialog::showFatalError(tr("Smuuki cannot load important config file. Application can run incorrectly."));
        }

        QTextStream in(&file);
        QString sql = in.readAll();
        if (sql.length() == 0)
            continue;

        query.prepare(sql);
        query.exec();
        query.clear();
        file.close();
    }
}

void MainWindow::loadLang() {
    QString langId = settings.lang;
    langId.truncate(langId.lastIndexOf('_'));

    QLocale locale{langId};
    QLocale::setDefault(locale);

    qApp->removeTranslator(&translator);
    qApp->removeTranslator(&translatorQt);

    QString path = QApplication::applicationDirPath().append("/translations/");

    if(translator.load(path + QString("smuuki_%1.qm").arg(langId.toUpper()))) {
        qApp->installTranslator(&translator);
    }

    if(translatorQt.load(path + QString("qt_%1.qm").arg(langId))) {
        qApp->installTranslator(&translatorQt);
    }

    ui.retranslateUi(this);
}

void MainWindow::showOutstandingPayments() {
    OutstandingPayments outstandingPayments{this};
    if (outstandingPayments.getOutstandingPayments() > 0) outstandingPayments.exec();
}
