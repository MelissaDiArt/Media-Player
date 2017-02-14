#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QIcon>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QList>
#include <QInputDialog>
#include <QCameraInfo>

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
    void on_CamPushButton_clicked();

    void on_RewindPushButton_clicked();

    void on_PlayPausePushButton_clicked();

    void on_ForwardPushButton_clicked();

    void on_StopPushButton_clicked();

    void on_ConfigPushButton_clicked();

    void on_VolumePushButton_clicked();

private:
    Ui::MainWindow *ui;
    QCamera* camera;
    QMediaPlayer* player;
    QByteArray name;
    bool othercamera;
};

#endif // MAINWINDOW_H
