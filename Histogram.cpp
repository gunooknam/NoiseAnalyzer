#include "Histogram.h"

Histogram::Histogram(QString name, QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background-color: red");
    m_label = name;


}

void Histogram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    // first QVector 구하기

    QVector<int> m_histogram {  100, 0, 0, 45, 23, 43, 43, 49, 43, 40, 219, 255,
                                244, 70, 219, 255, 3300, 223, 222, 188, 97,
                                67, 23, 23, 52, 12, 11, 19, 4, 5, 0, 0, 0, 0,
                                70, 219, 255, 2000, 223, 222};


    int max_hist_val = 0;
    for (auto &x: m_histogram)
        max_hist_val=x>max_hist_val?x:max_hist_val;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_histogram.isEmpty()) {
        painter.fillRect(0, 0, width(), height(), QColor::fromRgb(255, 255, 0));
        return;
    }

    qreal barWidth = (width()*0.98) / (qreal)m_histogram.size();
    qreal wspolczynnik_proporcji = height()/((qreal)max_hist_val*1.1); // 종횡비

    for (int i = 0; i < m_histogram.size(); ++i)
    {
        int h = m_histogram[i]*wspolczynnik_proporcji;
        int nizej = 20;
        painter.drawLine(10, nizej, 10, height() - nizej);
        QFont font;
        font.setPixelSize(5);
        painter.setFont(font);
        painter.drawText(0, 15, m_label);
        painter.drawText(10, height(), "0");
        painter.drawText(width() - 80, height(), "255(sigma)");

        // draw level
        // left, top, width, height
        QRect r1((barWidth * i) + 10, height() - h - nizej, barWidth, m_histogram[i]*wspolczynnik_proporcji);
        painter.drawRect(r1);
        painter.fillRect(r1, Qt::red);

    }
}
