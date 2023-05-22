#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    void closeEvent(QCloseEvent *event);
private slots:
    void on_actionSave_triggered();

    void on_actionCancel_triggered();

private:
    Ui:: SettingsWindow *ui;

};

#endif // SETTINGSWINDOW_H
