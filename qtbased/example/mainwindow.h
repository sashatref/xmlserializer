#pragma once

#include <QMainWindow>

#include "testobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_saveButton_clicked();

private:
    TestObject m_settings;
    Ui::MainWindow *ui;
};
