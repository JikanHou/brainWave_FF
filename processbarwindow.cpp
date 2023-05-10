#include "processbarwindow.h"
#include "ui_processbarwindow.h"

ProcessBarWindow::ProcessBarWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProcessBarWindow)
{
    ui->setupUi(this);
}

ProcessBarWindow::~ProcessBarWindow()
{
    delete ui;
}
