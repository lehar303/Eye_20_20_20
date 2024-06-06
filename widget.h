#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QTimer"
#include "QTime"
#include <QSound>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void showTime();
    void timer20s();
    void timer20m();
    QTimer *timer_20s = new QTimer(this);
    QTimer *timer_20m = new QTimer(this);

    QSound *bells ;


signals:
    void sig_timeup_20m();
    void sig_timeup_20s();


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
