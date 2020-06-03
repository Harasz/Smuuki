#ifndef SMUUKI_SETTINGS_H
#define SMUUKI_SETTINGS_H

#include "../../forms/Settings/ui_settings.h"
#include "../MainWindow/MainWindow.h"
#include <QWidget>

struct SettingsInput {
    QString databaseFile;
    QString language;
};

struct SettingsInputChanged {
    bool databaseFile;
    bool language;
};

class Settings: public QWidget {
Q_OBJECT
public:
    explicit Settings(MainWindow::LocalSettings *, QWidget *parent = nullptr);
    static Settings *registerView(QWidget *, QLayout *, MainWindow::LocalSettings*);

private:
    Ui::Settings ui;
    SettingsInput inputs_;
    SettingsInputChanged inputsChanged_{};
    MainWindow::LocalSettings *localSettings_;

    void disableAccept();

    void enableAccept();

    void bindSignals();

    void loadLangSettings();

    void loadDatabaseSettings();

    void restartApp();

private slots:
    void handleSelectFile();

    void handleSelectLang();

    void handlePasswordChange();

    void handleNewDatabase();

    void handleSave();

    void handleCancel();
};

#endif //SMUUKI_SETTINGS_H
