#ifndef SMUUKI_MAINWINDOW_H
#define SMUUKI_MAINWINDOW_H

#include "../../forms/MainWindow/ui_mainwindow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTranslator>
#include <map>

class MainWindow final : public QMainWindow {
Q_OBJECT
public:
    struct LocalSettings {
        QString dataDirPath;
        QString settingsFilePath;
        QString dbFilePath;
        QString lang;
    };

    explicit MainWindow();

    ~MainWindow() override;

private:
    QPushButton *activeButton = nullptr;
    QWidget *activeView = nullptr;
    std::map<QString, QWidget *> viewsMap;
    Ui::MainWindow ui{};
    LocalSettings settings;
    QTranslator translator;
    QTranslator translatorQt;

    void changeActiveButton(QPushButton *);

    static void updateStyle(QWidget *);

    void changeView(const QString &);

    void bindButtons();

    void registerViews();

    void loadSettings();

    void initDatabase();

    void loadLang();

    void showOutstandingPayments();

private slots:

    void handleButtonClick();
};


#endif //SMUUKI_MAINWINDOW_H
