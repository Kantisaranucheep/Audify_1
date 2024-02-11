#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyle>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();

    MPlayer->setAudioOutput(audioOutput);

    int iconSize = 40;

    ui->push_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->push_play->setIconSize(QSize(iconSize, iconSize));

    ui->push_skip->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->push_skip->setIconSize(QSize(iconSize, iconSize));

    ui->push_back->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->push_back->setIconSize(QSize(iconSize, iconSize));

    ui->volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->volume->setIconSize(QSize(iconSize, iconSize));

    ui->horizontalSlider_2->setMinimum(0);
    ui->horizontalSlider_2->setMaximum(100);
    ui->horizontalSlider_2->setValue(30);

    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);


    ui->horizontalSlider->setRange(0, MPlayer->duration()/1000);
    audioOutput->setVolume(ui->horizontalSlider_2->value() / 100.0);


}


MainWindow::~MainWindow()
{
    delete ui;
    delete MPlayer;
    delete audioOutput;
    // Optionally add more cleanup code here
}

void MainWindow::durationChanged(qint64 duration) {

    mduration = duration/1000;
    ui->horizontalSlider->setMaximum(mduration);
}


void MainWindow::positionChanged(qint64 progress) {

    if (!ui->horizontalSlider->isSliderDown()) {
        ui->horizontalSlider->setValue(progress / 1000);
    }
    updateDuration(progress / 1000);
}

void MainWindow::updateDuration(qint64 position) {
    qint64 totalSeconds = position;
    QTime currentTime((totalSeconds / 3600) % 60, (totalSeconds / 60) % 60, totalSeconds % 60, (totalSeconds*1000)%1000);
    ui->label_duration1->setText(currentTime.toString("mm:ss"));

    // qint64 totalDuration = MPlayer->duration() / 1000;
    QTime totalDurationTime((mduration / 3600) % 60, (mduration / 60) % 60, mduration% 60, (mduration*1000)%1000);
    ui->label_duration2->setText(totalDurationTime.toString("mm:ss"));
}



void MainWindow::on_actionOpen_Audio_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "", tr("MP3 Files (*.mp3)"));

    if (!fileName.isEmpty()) {
        // Set media content to the selected file
        MPlayer->setSource(QUrl::fromLocalFile(fileName));
        audioOutput->setVolume(ui->horizontalSlider_2->value());
        // Update the label with the file name
        QFileInfo fileInfo(fileName);
        ui->label_File_Name->setText(fileInfo.fileName());

        // Optional: Start playing the media when a new file is loaded
    }
}

void MainWindow::on_push_play_clicked()
{
    if (isPause == false)
    {
        // Resume functionality
        QIcon playIcon = style()->standardIcon(QStyle::SP_MediaPlay);
        ui->push_play->setIcon(playIcon);

        MPlayer->pause();

        isPause = true;
    }
    else
    {
        // Pause functionality
        QIcon pauseIcon = style()->standardIcon(QStyle::SP_MediaPause);
        ui->push_play->setIcon(pauseIcon);

        MPlayer->play();

        isPause = false;
    }
}

void MainWindow::on_volume_clicked()
{
    if (IS_MUTE == false) {
        QIcon volumeIcon = style()->standardIcon(QStyle::SP_MediaVolume);
        ui->volume->setIcon(volumeIcon);
        audioOutput->setMuted(false); // Set to false to unmute
        IS_MUTE = true;
    } else {
        QIcon volumeMutedIcon = style()->standardIcon(QStyle::SP_MediaVolumeMuted);
        ui->volume->setIcon(volumeMutedIcon);
        audioOutput->setMuted(true); // Set to true to mute
        IS_MUTE = false;
    }
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);

    if (value == 0) {
        ui->volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    } else {
        ui->volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }    // Set volume between 0.0 and 1.0
}

void MainWindow::on_push_skip_clicked()
{

}

void MainWindow::on_push_back_clicked()
{

}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if (!ui->horizontalSlider->isSliderDown()) {
        // Slider is not being dragged, update label only
        updateDuration(value);
    } else {
        // Slider is being dragged, update MediaPlayer position
        MPlayer->setPosition(value * 1000);
        updateDuration(value);
    }
}

void MainWindow::handleMediaPlayerError() {
    qDebug() << "MediaPlayer Error: " << MPlayer->errorString();
}


