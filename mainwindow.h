#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultiMedia>
#include <QMediaPlayer>
#include <QtWidgets>
#include <QAudioOutput>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);

    void on_push_play_clicked();

    void on_push_skip_clicked();


    void on_push_back_clicked();

    void on_actionOpen_Audio_File_triggered();

    void on_volume_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    bool IS_MUTE = false;
    bool isPause = false;
    QMediaPlayer *MPlayer;
    QAudioOutput *audioOutput;

    qint64 duration;
    void updateDuration(qint64 duration);

};
#endif // MAINWINDOW_H
