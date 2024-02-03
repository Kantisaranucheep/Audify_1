#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyle>

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
}

MainWindow::~MainWindow()
{
    delete ui;
    // Optionally add more cleanup code here
}
