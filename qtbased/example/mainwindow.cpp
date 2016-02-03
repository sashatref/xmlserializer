#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выберите файл...");
    if(path.isEmpty()) return;
    if(XmlSerializer::load(m_settings, path, "Settings"))
    {
        ui->logBrowser->append(QString("Файл <%1> успешно загружен").arg(path));
    } else
    {
        ui->logBrowser->append(QString("Ошибка загрузки файла <%1>").arg(path));
    }

    ui->logBrowser->append(m_settings.toString());
}

void MainWindow::on_saveButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Выберите файл...");
    if(path.isEmpty()) return;
    if(XmlSerializer::save(m_settings, path, "Settings"))
    {
        ui->logBrowser->append(QString("Файл <%1> успешно сохранен").arg(path));
    } else
    {
        ui->logBrowser->append(QString("Ошибка сохранения файла <%1>").arg(path));
    }
}
