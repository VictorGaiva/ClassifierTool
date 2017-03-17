#include "coloredprogressbar.h"

#include <QPainter>
#include <QBrush>
#include <QStyle>
#include <QPen>
#include <QColor>

ColoredProgressBar::ColoredProgressBar(QWidget *parent) : QProgressBar(parent)
{

}

ColoredProgressBar::~ColoredProgressBar()
{

}

void ColoredProgressBar::paintEvent(QPaintEvent*)
{
    int val = value();
    int pos = QStyle::sliderPositionFromValue(minimum(), maximum(), val, width());

    int pos60 = QStyle::sliderPositionFromValue(minimum(), maximum(), 60, width());
    int pos80 = QStyle::sliderPositionFromValue(minimum(), maximum(), 80, width());

    QPainter p(this);
    p.setPen(Qt::green);
    p.setBrush(QBrush(Qt::green));

    if(val >= 0 && val <= 60)
    {
        p.drawRect(0,0,pos,height());
    }
    else if(val > 60 && val <= 80)
    {
        p.drawRect(0,0,pos60,height());
        p.setPen(QColor(255,127,0));
        p.setBrush(QBrush(QColor(255,127,0)));
        p.drawRect(pos60, 0, pos - pos60, height());
    }
    else
    {
        p.drawRect(0,0,pos60,height());
        p.setPen(QColor(255,127,0));
        p.setBrush(QBrush(QColor(255,127,0)));
        p.drawRect(pos60, 0, pos80 - pos60,height());
        p.setPen(Qt::red);
        p.setBrush(QBrush(Qt::red));
        p.drawRect(pos80, 0, pos - pos80, height());
    }

    p.setPen(Qt::lightGray);
    p.setBrush(QBrush(Qt::lightGray));
    p.drawRect(pos, 0, width(), height());


    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));
    p.drawText(0,0, width(), height(), Qt::AlignCenter, QString::number(val) + "%");
}
