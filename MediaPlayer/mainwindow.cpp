#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    camera = new QCamera;
    player = new QMediaPlayer;
    othercamera = false;

    //Iconos de la interfaz
    ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/Iconos/play.png"));
    ui->CamPushButton->setIcon(QIcon("../MediaPlayer/Iconos/webcam.png"));
    ui->RewindPushButton->setIcon(QIcon("../MediaPlayer/Iconos/rewind.png"));
    ui->ForwardPushButton->setIcon(QIcon("../MediaPlayer/Iconos/forward.png"));
    ui->StopPushButton->setIcon(QIcon("../MediaPlayer/Iconos/stop.png"));
    ui->ConfigPushButton->setIcon(QIcon("../MediaPlayer/Iconos/config.png"));
    ui->VolumePushButton->setIcon(QIcon("../MediaPlayer/Iconos/audio.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Implementacion de la camara web
void MainWindow::on_CamPushButton_clicked()
{
    camera = new QCamera(name);
    player->stop();
    camera->setViewfinder(ui->widget);

    camera->start();
    ui->StopPushButton->setEnabled(true);
    ui->CamPushButton->setEnabled(false);
    ui->VolumePushButton->setEnabled(false);
    ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/Iconos/play.png"));

    if(othercamera){
        ui->statusBar->showMessage(name);
    }else{
        QList<QCameraInfo> devices = QCameraInfo::availableCameras();
        ui->statusBar->showMessage(devices[0].description());
    }

}

//Implementacion del video hacia atras
void MainWindow::on_RewindPushButton_clicked()
{
    qint64 size = player->duration();
    qint64 percentage = size/10;
    qint64 actual_position = player->position();
    player->setPosition(actual_position-percentage);
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
        ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/Iconos/pause.png"));
        ui->RewindPushButton->setEnabled(true);
        ui->ForwardPushButton->setEnabled(true);
        ui->StopPushButton->setEnabled(true);
        ui->VolumePushButton->setEnabled(true);

    }else if(player->state()==QMediaPlayer::PausedState){
       player->play();
       ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/Iconos/pause.png"));
       ui->RewindPushButton->setEnabled(true);
       ui->ForwardPushButton->setEnabled(true);
        ui->VolumePushButton->setEnabled(true);

    }else{
        player->pause();
        ui->PlayPausePushButton->setIcon(QIcon("../MediaPlayer/Iconos/play.png"));
        ui->RewindPushButton->setEnabled(false);
        ui->ForwardPushButton->setEnabled(false);
        ui->VolumePushButton->setEnabled(false);
    }
}

//Implementacion del video hacia delante
void MainWindow::on_ForwardPushButton_clicked()
{
    qint64 size = player->duration();
    qint64 percentage = size/10;
    qint64 actual_position = player->position();
    player->setPosition(actual_position+percentage);
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
    QList<QCameraInfo> devices = QCameraInfo::availableCameras();
    QStringList deviceslist;
    for(int i=0;i<devices.size();i++)
    {
        deviceslist<<devices[i].description();
    }
    QString camname = QInputDialog::getItem(this,"Select camera","Camera", deviceslist, othercamera);
    name = "";
    name.append(camname);
}

void MainWindow::on_VolumePushButton_clicked()
{
    if(player->isMuted()){
        player->setMuted(false);
        ui->VolumePushButton->setIcon(QIcon("../MediaPlayer/Iconos/audio.png"));

    } else {
        player->setMuted(true);
        ui->VolumePushButton->setIcon(QIcon("../MediaPlayer/Iconos/mute.png"));
    }
}
