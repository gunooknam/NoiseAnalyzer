#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include <QWidget>
#include <QPainter>
#include <QRect>
#include <QDebug>

class Histogram : public QWidget
{
    Q_OBJECT
public:
    explicit Histogram(QString name, QWidget *parent = nullptr);

private :
    QString m_label;




signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

};




#endif // HISTOGRAM_H
