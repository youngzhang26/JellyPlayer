#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QtWidgets/QFileDialog>
#include <QStandardItemModel>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    player2 = new QMediaPlayer;
    video = new QVideoWidget(ui->videoWidget);
    video->setGeometry(QRect(0, 0, 711, 431));
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput2 = new QAudioOutput;
    player2->setAudioOutput(audioOutput2);
    // connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    audioOutput->setVolume(100);
    audioOutput2->setVolume(100);

    QStringList musicList;
    QStringListModel *model = new QStringListModel(musicList);
    ui->listView->setModel(model);

    timer = new QTimer;
    int maxValue = 1000;
    ui->progressSlider->setRange(0, maxValue);
    ui->voiceSlider->setRange(0, 100);
    ui->voiceSlider->setValue(100);
    timer->setInterval(100);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

void MainWindow::onTimeOut()
{
    int maxValue = 1000;
    if (player->isPlaying()) {
        ui->progressSlider->setValue(player->position()*maxValue/player->duration());
    } else if (player2->isPlaying()) {
        ui->progressSlider->setValue(player2->position()*maxValue/player2->duration());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (currMedia.contains(".mp4")) {
        player2->play();
    } else {
        player->play();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (currMedia.contains(".mp4")) {
        player2->pause();
    } else {
        player->pause();
    }
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString a = index.data(0).toString();
}


void MainWindow::on_pushButton_3_clicked()
{
    QStringList s = QFileDialog::getOpenFileNames(this, tr("选择"), "D:\\", tr("music file (*.mp3; *.wav; *.mp4)"));
    QStringListModel *model = dynamic_cast<QStringListModel *>(ui->listView->model());
    int cnt = s.size();
    QStringList item = model->stringList();
    for (int i= 0; i < cnt; ++i) {
        item.append(s.at(i));
    }
    model->setStringList(item);
    ui->listView->setModel(model);
}


void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QString s = index.data(0).toString();
    ui->label->setText("当前播放:" + s);
    currMedia = s;
    if (currMedia.contains(".mp4")) {
        player->stop();
        video->show();
        video->setAutoFillBackground(true);

        player2->setVideoOutput(video);
        player2->setSource(QUrl::fromLocalFile(currMedia));
        player2->play();
    } else {
        player2->stop();
        video->hide();
        player->setSource(currMedia);
        player->play();
    }
}

void MainWindow::on_progressSlider_sliderMoved(int position)
{
    int maxValue = 1000;
    if (player->isPlaying()) {
        player->setPosition(position*player->duration()/maxValue);
    } else if (player2->isPlaying()) {
        player2->setPosition(position*player2->duration()/maxValue);
    }
}

void MainWindow::on_progressSlider_sliderPressed()
{
    timer->stop();
}

void MainWindow::on_progressSlider_sliderReleased()
{
    timer->start();
}



void MainWindow::on_voiceSlider_sliderMoved(int position)
{
    if (player->isPlaying()) {
        audioOutput->setVolume(position);
    } else if (player2->isPlaying()) {
        audioOutput2->setVolume(position);
    }
}

