#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow:: SettingsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::SettingsWindow){
    ui -> setupUi(this);
    this -> setWindowIcon(QIcon(":/Icons/favicon.ico"));
    QSettings settings("BrainWave");
    ui -> editWindowSize -> setText(QString::number(settings.value("windowSize", 10).toInt()));
    ui -> editWindowHeight -> setText(QString::number(settings.value("picHeight", 1200).toInt()));
    ui -> editWindowWidth -> setText(QString::number(settings.value("picWidth", 2000).toInt()));
}

SettingsWindow::~SettingsWindow(){
    delete ui;
}

void SettingsWindow:: closeEvent(QCloseEvent *event){
    event -> ignore();
    on_actionCancel_triggered();
}

void SettingsWindow::on_actionSave_triggered(){
    QSettings settings("BrainWave");
    bool ok = false;
    int windowSize = ui -> editWindowSize -> text().toInt(&ok);
    if (!ok){
        QMessageBox msg;
        msg.setWindowTitle("错误");
        msg.setWindowIcon(QIcon(":/Icons/favicon.ico"));
        msg.setText("平滑参数应为整数");
        msg.exec();
        return;
    }
    int picWidth = ui -> editWindowWidth -> text().toInt(&ok);
    if (!ok){
        QMessageBox msg;
        msg.setWindowTitle("错误");
        msg.setWindowIcon(QIcon(":/Icons/favicon.ico"));
        msg.setText("图片宽度应为整数");
        msg.exec();
        return;
    }
    int picHeight = ui -> editWindowHeight -> text().toInt(&ok);
    if (!ok){
        QMessageBox msg;
        msg.setWindowTitle("错误");
        msg.setWindowIcon(QIcon(":/Icons/favicon.ico"));
        msg.setText("图片高度应为整数");
        msg.exec();
        return;
    }
    settings.setValue("windowSize", windowSize);
    settings.setValue("picHeight", picHeight);
    settings.setValue("picWidth", picWidth);
    on_actionCancel_triggered();
}


void SettingsWindow::on_actionCancel_triggered(){
    this -> setWindowModality(Qt:: NonModal);
    this -> hide();
    delete this;
}

