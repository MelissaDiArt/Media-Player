#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_PlayPushButton_clicked()
{

}

void MainWindow::on_WebCamPushButton_clicked()
{
    QCamera* camera = new QCamera;
    camera->setViewfinder(ui->View);
    camera->start();
}
