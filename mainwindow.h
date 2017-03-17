#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//My includes
#include <QFileDialog>
#include <QDebug>
#include <QMediaPlayer>
#include "qcustomplot.h"

//My defines
#define PB_MULTIPLIER 1.4

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Flags
    bool FileIsOpen;

    //variables
    QMediaPlayer *player;

private slots:
    void updateStuff();

    void on_bt_OpenFile_clicked();

    void on_bt_Pause_clicked();

    void on_bt_Play_clicked();

    void on_bt_Finish_clicked();

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void on_sl_TimeFrameSelector_sliderMoved(int position);

    void on_sl_volumeBar_valueChanged(int value);

    void makePlot();

    void on_sl_playbackSpeed_valueChanged(int value);

    void setCurrentClass();

private:
    Ui::MainWindow *ui;
    int curr_position;
    QTimer *timer;
    QString ClassStream;
    int currClass;
    QPushButton* currBT;

};

#endif // MAINWINDOW_H
