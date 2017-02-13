#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    camera = new QCamera;
    player = new QMediaPlayer;
    velocity = 1.0;
    othercamera = false;

    //Iconos de la interfaz
    ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/play.png"));
    ui->CamPushButton->setIcon(QIcon("../MediaPlayer/webcam.png"));
    ui->RewindPushButton->setIcon(QIcon("../MediaPlayer/rewind.png"));
    ui->ForwardPushButton->setIcon(QIcon("../MediaPlayer/forward.png"));
    ui->StopPushButton->setIcon(QIcon("../MediaPlayer/stop.png"));
    ui->ConfigPushButton->setIcon(QIcon("../MediaPlayer/config.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Implementacion de la camara web
void MainWindow::on_CamPushButton_clicked()
{
    camera = new QCamera(name);
    camera->setViewfinder(ui->widget);
    camera->start();
    ui->StopPushButton->setEnabled(true);
    ui->CamPushButton->setEnabled(false);

    if(othercamera){
        ui->statusBar->showMessage(QCamera::deviceDescription(name));

    }else{
        QList<QByteArray> devices = QCamera::availableDevices();
         ui->statusBar->showMessage(QCamera::deviceDescription(devices[0]));
    }

}

//Implementacion del video hacia atras
void MainWindow::on_RewindPushButton_clicked()
{
    velocity -= 1.1; //arreglar
    player->setPlaybackRate(velocity);
}

//Implementacion de Play/Pause
void MainWindow::on_PlayPausePushButton_clicked()
{
    if(camera->status()==QCamera::ActiveStatus||player->state()==QMediaPlayer::StoppedState)
    {
        QString filename= QFileDialog::getOpenFileName(this,tr("Open File"),"../MediaPlayer",tr("Video(*.mp4)"));
        player->setMedia(QUrl::fromLocalFile(filename));
        player->setVideoOutput(ui->widget);
        player->play();
        int Bar = filename.lastIndexOf("/");
        filename.remove(0,Bar+1);
        statusBar()->showMessage(filename);
        ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/pause.png"));
        ui->RewindPushButton->setEnabled(true);
        ui->ForwardPushButton->setEnabled(true);
        ui->StopPushButton->setEnabled(true);

    }else if(player->state()==QMediaPlayer::PausedState){
       player->play();
       ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/pause.png"));
       ui->RewindPushButton->setEnabled(true);
       ui->ForwardPushButton->setEnabled(true);

    }else{
        player->pause();
        ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/play.png"));
        ui->RewindPushButton->setEnabled(false);
        ui->ForwardPushButton->setEnabled(false);
    }
}

//Implementacion del video hacia delante
void MainWindow::on_ForwardPushButton_clicked()
{
    velocity += 0.5;
    player->setPlaybackRate(velocity);
}

//Implementacion del stop
void MainWindow::on_StopPushButton_clicked()
{
    if(camera->status()==QCamera::ActiveStatus)
    {
        camera->stop();
        ui->StopPushButton->setEnabled(false);
        ui->CamPushButton->setEnabled(true);
        statusBar()->clearMessage();
    }
    else if (player->state()==QMediaPlayer::PlayingState||player->state()==QMediaPlayer::PausedState)
    {
        player->stop();
        ui->StopPushButton->setEnabled(false);
        statusBar()->clearMessage();
    }

}

//Implementar la ventana de configuracion de camaras.
void MainWindow::on_ConfigPushButton_clicked()
{
    QList<QByteArray> devices = QCamera::availableDevices();
    QStringList deviceslist;
    for(int i=0;i<devices.size();i++)
    {
        deviceslist<<devices[i];
    }
    QString camname = QInputDialog::getItem(this,"Select camera","Camera", deviceslist, othercamera);
    name = "";
    name.append(camname);
}
