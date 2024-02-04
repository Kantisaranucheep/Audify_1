#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyle>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int iconSize = 40;

    QIcon playIcon = style()->standardIcon(QStyle::SP_MediaPlay);
    QSize actualSize = playIcon.actualSize(QSize(iconSize, iconSize));
    ui->push_play->setIcon(playIcon);
    ui->push_play->setIconSize(actualSize);

    QIcon skipIcon = style()->standardIcon(QStyle::SP_MediaSkipForward);
    QSize skipIconSize = skipIcon.actualSize(QSize(iconSize, iconSize));
    ui->push_skip->setIcon(skipIcon);
    ui->push_skip->setIconSize(skipIconSize);

    QIcon backIcon = style()->standardIcon(QStyle::SP_MediaSkipBackward);
    QSize backIconSize = backIcon.actualSize(QSize(iconSize, iconSize));
    ui->push_back->setIcon(backIcon);
    ui->push_back->setIconSize(backIconSize);

    QIcon volumeIcon = style()->standardIcon(QStyle::SP_MediaVolume);
    QSize volumeIconSize = volumeIcon.actualSize(QSize(iconSize, iconSize));
    ui->volume->setIcon(volumeIcon);
    ui->volume->setIconSize(volumeIconSize);

    // QLabel *label = new QLabel("Playlist");  // Create a QLabel with the text "Playlist"

    // QVBoxLayout *frameLayout = new QVBoxLayout(ui->frame_2);  // Assuming frame_2 is your QFrame
    // frameLayout->addWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
    // Optionally add more cleanup code here
}
