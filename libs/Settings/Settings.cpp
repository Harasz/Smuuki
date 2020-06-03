//
// Created by Jakub on 18-04-2020.
//

#include "Settings.h"
#include "../DatabasePasswordDialog/DatabasePasswordDialog.h"
#include "../../helpers/Dialog/Dialog.h"
#include <QSettings>
#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include <QSqlDatabase>

Settings::Settings(MainWindow::LocalSettings* localSettings_arg, QWidget *parent_arg): QWidget(parent_arg), ui(), inputs_(), inputsChanged_(), localSettings_(localSettings_arg) {
    ui.setupUi(this);
    loadDatabaseSettings();
    loadLangSettings();
    bindSignals();
    disableAccept();
}


Settings *Settings::registerView(QWidget *widget_arg, QLayout *layout_arg, MainWindow::LocalSettings* localSettings_arg) {
    auto *result = new Settings(localSettings_arg, widget_arg);
    layout_arg->addWidget(result);
    result->hide();
    return result;
}

void Settings::disableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(false);
}

void Settings::enableAccept() {
    auto *btn{ ui.buttonBox->button(QDialogButtonBox::Save) };
    btn->setEnabled(true);
}

void Settings::loadDatabaseSettings() {
    ui.filePath->setText(localSettings_->dbFilePath);
}

void Settings::loadLangSettings() {
    ui.languageCombo->addItem(tr("English"), "en_EN");
    ui.languageCombo->addItem(tr("Polski"), "pl_PL");

    ui.languageCombo->setCurrentIndex(ui.languageCombo->findData(localSettings_->lang));
}

void Settings::restartApp() {
    qApp->exit(-1);
}

void Settings::bindSignals() {
    connect(ui.fileButton, &QPushButton::clicked, this, &Settings::handleSelectFile);
    connect(ui.languageCombo, &QComboBox::currentTextChanged, this, &Settings::handleSelectLang);
    connect(ui.passwordButton, &QPushButton::clicked, this, &Settings::handlePasswordChange);
    connect(ui.newDbButton, &QPushButton::clicked, this, &Settings::handleNewDatabase);
    connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &Settings::handleSave);
    connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &Settings::handleCancel);
}

void Settings::handleSelectFile() {
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(tr("Database file (*.sqlite3 *.sqlite);; All (*.*)"));
    fileDialog.setWindowTitle(tr("Select Database"));
    fileDialog.setDirectory(QDir::homePath());
    fileDialog.exec();

    auto fileName = fileDialog.selectedFiles();

    if (fileName.length() <= 0) return;

    if (fileName[0] != localSettings_->dbFilePath) {
        enableAccept();
        inputsChanged_.databaseFile = true;
        inputs_.databaseFile = fileName[0];
        ui.filePath->setText(fileName[0]);
    }
}

void Settings::handleSave() {
    QSettings settingsObject(
            localSettings_->settingsFilePath,
            QSettings::IniFormat
    );

    if (inputsChanged_.databaseFile) {
        settingsObject.setValue("database", inputs_.databaseFile);
    }

    if (inputsChanged_.language) {
        settingsObject.setValue("lang", inputs_.language);
    }

    restartApp();
}

void Settings::handleCancel() {
    loadLangSettings();
    loadDatabaseSettings();

    inputsChanged_.databaseFile = false;
    inputsChanged_.language = false;

    inputs_.databaseFile = "";
    inputs_.language = "";

    disableAccept();
}

void Settings::handleSelectLang() {
    if (ui.languageCombo->currentData().toString() != localSettings_->lang) {
        inputsChanged_.language = true;
        inputs_.language = ui.languageCombo->currentData().toString();
        enableAccept();
        return;
    }
    inputsChanged_.language = false;
}

void Settings::handlePasswordChange() {
    DatabasePasswordDialog passwordDialog(true);
    auto newPassword{ passwordDialog.getPassword(true) };
    auto database{ QSqlDatabase::database() };
    if (newPassword == "#-1%NO_PASS%") return;

    database.setConnectOptions(QString("QSQLITE_UPDATE_KEY=%1").arg(newPassword));
    Dialog::showInfo(tr("Database password updated. The application will be restarted."));

    restartApp();
}

void Settings::handleNewDatabase() {
    QString newDatabasePath { QFileDialog::getSaveFileName(
            this,
            tr("Create new database"),
            QDir::homePath(),
            tr("Database file (*.sqlite3 *.sqlite);; All (*.*)")
    ) };

    if (newDatabasePath.length() == 0) return;

    DatabasePasswordDialog passwordDialog(true);
    auto password{passwordDialog.getPassword(true)};
    if (password == "#-1%NO_PASS%") return;

    auto database{ QSqlDatabase::addDatabase("SQLITECIPHER", "NEW") };
    database.setDatabaseName(newDatabasePath);
    database.setPassword(password);
    database.setConnectOptions("QSQLITE_CREATE_KEY");

    if (!database.open()) {
        Dialog::showFatalError(tr("Cannot create new database."), false);
        return;
    }

    Dialog::showInfo("A new database has been created. Save the settings to use it.");
    inputsChanged_.databaseFile = true;
    inputs_.databaseFile = newDatabasePath;
    ui.filePath->setText(newDatabasePath);
    enableAccept();
}

