#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void onTimeOut();

    void on_progressSlider_sliderPressed();

    void on_progressSlider_sliderMoved(int position);

    void on_progressSlider_sliderReleased();

    void on_voiceSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    QMediaPlayer* player2;
    QAudioOutput* audioOutput2;
    QVideoWidget* video;
    QString currMedia;
    QTimer *timer;
};
#endif // MAINWINDOW_H
