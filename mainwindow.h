#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "patientinfo.h"
#include "settingswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PatientInfo *currentInfo;

    PatientInfo LoadFromFile(const QString &filepath);
    void ShowInfo(const PatientInfo &info);
    void AnalyseBw(QString filename, QVector<double> bw);

private slots:
    void on_actionImport_triggered();
    void on_actionAnalyse_triggered();
    void on_actionSettings_triggered();
};
#endif // MAINWINDOW_H
