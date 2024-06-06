#include "widget.h"
#include "ui_widget.h"

//#include "QDebug"
#include <QFile>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    bells = new QSound(":/audio/Let-s hustle again 1.wav");
    //qDebug() << QFile::exists(":/audio/Let-s hustle again 1.wav");

    //CLOCK
    QTimer *timer_clock = new QTimer(this);
    connect(timer_clock, &QTimer::timeout, this,&Widget::showTime);
    timer_clock->start(1000);

    //20m timer
    connect(timer_20m, &QTimer::timeout, this,&Widget::timer20m);
    connect(this,&Widget::sig_timeup_20s,this,&Widget::timer20m);

    //20s timer
    connect(this,&Widget::sig_timeup_20m,this,&Widget::timer20s);
    connect(timer_20s, &QTimer::timeout, this,&Widget::timer20s);

    showTime();

    timer20m();

    setWindowTitle(tr("Eye 20-20-20"));

}


Widget::~Widget()
{
    delete ui;
}

void Widget::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("h:mm:ss");
    if ((time.second() % 2) == 0){
        text[2] = ' ';
        text[5] = ' ';
    }
    ui->clock->display(text);
}

void Widget::timer20s()
{
    static QTime countdown = QTime(0,0,21,0);
    timer_20s->start(1000);
    QWidget::showNormal();
    QTime new_countdown =  countdown.addSecs(-1);
    ui->lineEdit->setText(QString(new_countdown.toString("ss"))+ "s");
    countdown = new_countdown;
    if(new_countdown == QTime(0,0,0,0)){
        countdown = QTime(0,0,21,0);
        timer_20s->stop();
        emit sig_timeup_20s();
        bells->play();
    }

    //qDebug() << "Timer 20s: " << QTime::currentTime() << " " << new_countdown;


}

void Widget::timer20m()
{
    static QTime countdown = QTime(0,21,0,0);
    timer_20m->start(1000);

    QTime new_countdown =  countdown.addSecs(-1);
    ui->timer->display(QString(new_countdown.toString("mm:ss")));
    countdown = new_countdown;
    if(new_countdown == QTime(0,0,0,0)){
        countdown = QTime(0,21,0,0);
        emit sig_timeup_20m();
        timer_20m->stop();
    }

    //qDebug() << "Timer 20m: " << QTime::currentTime() << " " << new_countdown;
}
