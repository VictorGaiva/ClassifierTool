#ifndef COLOREDPROGRESSBAR_H
#define COLOREDPROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QPaintEvent>

class ColoredProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit ColoredProgressBar(QWidget *parent = 0);
    ~ColoredProgressBar();

protected:

    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // COLOREDPROGRESSBAR_H
