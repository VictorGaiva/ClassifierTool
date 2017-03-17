#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Variables
    this->FileIsOpen = false;
    this->curr_position = 0;
    this->ClassStream = QString("0,0\n");
    this->currClass = 0;
    this->currBT = NULL;

    //Buttons
    this->ui->bt_Pause->setEnabled(false);
    this->ui->bt_Play->setEnabled(false);

    //Some connects
    connect(this->ui->bt_Class1, &QPushButton::clicked, this, &MainWindow::setCurrentClass);
    connect(this->ui->bt_Class2, &QPushButton::clicked, this, &MainWindow::setCurrentClass);
    connect(this->ui->bt_Class3, &QPushButton::clicked, this, &MainWindow::setCurrentClass);
    connect(this->ui->bt_Class4, &QPushButton::clicked, this, &MainWindow::setCurrentClass);
    connect(this->ui->bt_Class5, &QPushButton::clicked, this, &MainWindow::setCurrentClass);
    connect(this->ui->bt_Class6, &QPushButton::clicked, this, &MainWindow::setCurrentClass);

    //player
    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);

    //Timer
    //QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &MainWindow::updateStuff);
    //timer->start(100);

}


void MainWindow::makePlot(){
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1;    // x goes from -1 to 1
      y[i] = qSin(x[i]+((double)this->curr_position/10000));    //le'ts plot a sine wave
    }

    // create graph and assign data to it:
    ui->gv_Graph1->addGraph();
    ui->gv_Graph1->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->gv_Graph1->xAxis->setLabel("x");
    ui->gv_Graph1->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->gv_Graph1->xAxis->setRange(-1, 1);
    ui->gv_Graph1->yAxis->setRange(-1, 1);
    //ui->gv_Graph1->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_OpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Audio"), "C:\\", tr("Audio Files (*.wav *.mp3 *.aac)"));

    try {
        //Adiciona a media ao player
        this->player->setMedia(QUrl::fromLocalFile(fileName));

        //Executa media
        this->player->play();

        //Ativa os botoes
        this->ui->bt_Pause->setEnabled(true);
        this->ui->bt_Play->setEnabled(true);

    } catch (...) {
        qDebug() << "Could not open file " << fileName <<".";
    }
}

void MainWindow::on_bt_Pause_clicked()
{
    this->player->pause();
}

void MainWindow::on_bt_Play_clicked()
{
    this->player->play();
}

void MainWindow::on_bt_Finish_clicked()
{

}

void MainWindow::on_positionChanged(qint64 position)
{
    this->ui->sl_TimeFrameSelector->setValue(position);
    this->curr_position = position;
    MainWindow::makePlot();
    
}

void MainWindow::on_durationChanged(qint64 position)
{
    this->ui->sl_TimeFrameSelector->setMaximum(position);
    this->ui->sl_TimeFrameSelector->setTickInterval(15000);
}


void MainWindow::on_sl_TimeFrameSelector_sliderMoved(int position)
{
    //Mova o timeframe para a posição correta
    this->player->setPosition(position);
}

void MainWindow::on_sl_volumeBar_valueChanged(int value)
{
    this->player->setVolume(value);
}

void MainWindow::on_sl_playbackSpeed_valueChanged(int value)
{
    //Altera a velocidade de reprodução do audio
    qreal value2 = value;
    value2 = qPow(PB_MULTIPLIER, value2-5);
    this->player->setPlaybackRate(value2);

    //Altera a label
    QString newLabel;
    newLabel.sprintf("Playback Speed( %.2fx)",value2);

    this->ui->lb_playbackSpeed->setText(newLabel);
}
void MainWindow::updateStuff(){
    //if(this->FileIsOpen){
        this->curr_position = this->player->position();
        this->ui->sl_TimeFrameSelector->setValue( this->curr_position);
        MainWindow::makePlot();
    //}

}

void MainWindow::setCurrentClass()
{
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());

    //Se for o objeto correto E estiver sendo checado
    if (!buttonWidget)
      return;
    //Continue a execução do programa
    //Isola apenas o numero de classe selecionada
    QString Classe = buttonWidget->objectName().remove("bt_Class");

    //Se algum botao já estiver sendo pressionado, solte-o
    if(this->currBT != NULL)
        this->currBT->setChecked(false);

    //Selecione o novo botao
    this->currBT = qobject_cast<QPushButton*>(buttonWidget);
    //E ative-o
    if(this->currBT)
        this->currBT->setChecked(true);
    else{
        throw("what the fuck");
    }

    //Se a classe atual for diferente da classe já armazenada
    if(Classe.toInt() != this->currClass){
        //Atualize-a
        this->currClass = Classe.toInt();

        //Atualize a string de classe
        if(this->player->mediaStatus() !=  QMediaPlayer::NoMedia){//caso o player ja estiver executando, atualize usando o tempo atual
            this->ClassStream.append(QString::number(this->player->position())); //insira o tempo em mili segundos
            this->ClassStream.append(',');
            this->ClassStream.append(Classe);
            this->ClassStream.append('\n');
        }
        else{
            this->ClassStream.clear();
            this->ClassStream.append("0,");
            this->ClassStream.append(Classe);
            this->ClassStream.append('\n');
        }

        std::cout << this->ClassStream.toStdString();
    }
}
