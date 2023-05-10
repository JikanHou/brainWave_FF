#ifndef PROCESSBARWINDOW_H
#define PROCESSBARWINDOW_H

#include <QMainWindow>

namespace Ui {
class ProcessBarWindow;
}

class ProcessBarWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProcessBarWindow(QWidget *parent = nullptr);
    ~ProcessBarWindow();

private:
    Ui::ProcessBarWindow *ui;
};

#endif // PROCESSBARWINDOW_H
