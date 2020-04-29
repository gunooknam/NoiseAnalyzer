#include <stdlib.h>
#include <QWheelEvent>
#include <QLabel>
#include <QPixmap>
#include "MainPaintWidget.h"

#define clip8(var) ((var > 255) ? 255 : (var < 0) ? 0 : var)
#define MAX(x,y) ((x > y)? x : y)

Void MainPaintWidget::MemAlloc_YUV(Int width, Int height) {

    m_width = width;
    m_height = height;
    if(m_Y == nullptr && m_U==nullptr && m_V == nullptr ){
        m_Y = (BYTE*)malloc(sizeof(BYTE) * height * width);
        m_U = (BYTE*)malloc(sizeof(BYTE) * height * width * 1/4);
        m_V = (BYTE*)malloc(sizeof(BYTE) * height * width * 1/4);
    }
}

Void MainPaintWidget::MemFree_YUV(Int height) {
    m_width = 0;
    m_height = 0;
    if (m_Y != nullptr && m_U!=nullptr&& m_V != nullptr){
        free(m_Y);
        free(m_U);
        free(m_V);
        m_Y=nullptr;
        m_U=nullptr;
        m_V=nullptr;
    }

}

Int MainPaintWidget::ReadFrame_YUV(FILE *fp)
{
    Int size = 0;
    size += fread(m_Y, sizeof(BYTE), m_width * m_height , fp);
    size += fread(m_U, sizeof(BYTE), m_width * m_height/4, fp);
    size += fread(m_V, sizeof(BYTE), m_width * m_height/4, fp);
    return size;
}

MainPaintWidget::MainPaintWidget(QWidget *parent)
    : QWidget(parent),
      m_Y(nullptr),
      m_U(nullptr),
      m_V(nullptr),
      m_filename(" "),
      m_width(0),
      m_height(0),
      m_display(0),
      m_pixelX(-1), m_pixelY(-1),
      m_imageWidth(0), m_imageHeight(0),
      m_zoomFactor(double(1.0)),
      m_mouseLeftBtnIsPressed(false),
      m_mouseLeftBtnIsPressedAndMoved(false),
      m_mouseRightBtnIsPressed(false)
{
    QPalette pallette;
    setAutoFillBackground(true);
    pallette.setColor(backgroundRole(), Qt::black);
    setPalette(pallette);
    setAcceptDrops(true);
    setMouseTracking(true);
}

MainPaintWidget::~MainPaintWidget()
{
   MemFree_YUV(m_height);
}


BYTE * MainPaintWidget::getImageComponent(ComponentID i)
{
    return (i == COMPONENT_Y)? m_Y : ((i == COMPONENT_Cb )? m_U : m_V);
}

Void MainPaintWidget::setPixelmap()
{
    BYTE * pY = m_Y;
    BYTE * pU = m_U;
    BYTE * pV = m_V;

    if(m_display == RGB_MODE) // m_RGBmode
    {
        Int width  = m_width;
        Int height = m_height;
        QImage recon = QImage(width, height, QImage::Format_RGB888);
        for (Int i = 0; i < height; i++)
        {
            for (Int j = 0; j < width; j++)
            {
                BYTE Y, U, V;
                Int C, D, E; // type
                UChar R, G, B;
                Y = pY[i * m_width + j];
                U = pU[i/2*m_width/2+j/2];
                V = pV[i/2*m_width/2+j/2];
                C = (Y - 16) * 298;
                D = U - 128;
                E = V - 128;
                R = UChar(clip8((C + 409 * E + 128) >> 8));
                G = UChar(clip8((C - 100 * D - 208 * E + 128) >> 8));
                B = UChar(clip8((C + 516 * D + 128) >> 8));
                recon.setPixel(j, i, qRgb(R, G, B));
            }
        }
        m_reconPixmap = QPixmap::fromImage(recon);
    }
    else // U or V mode
    {
        Int width  = m_width;
        Int height = m_height;
        BYTE* p = getImageComponent(ComponentID(m_display));
        QImage recon = QImage(width, height, QImage::Format_RGB888);

        for (Int i = 0; i < height; i++)
        {
            for (Int j = 0; j < width; j++)
            {
                BYTE Pixel;
                UChar R, G, B;
                if (m_display == COMPONENT_Y)
                    Pixel = pY[i * m_width + j];
                else if (m_display == COMPONENT_Cb)
                    Pixel = pU[i/2*m_width/2+j/2];
                else // COMPONENT_Cr
                    Pixel = pV[i/2*m_width/2+j/2];
                R = UChar(clip8(Pixel));
                G = UChar(clip8(Pixel));
                B = UChar(clip8(Pixel));
                recon.setPixel(j, i, qRgb(R, G, B));
            }
        }
        m_reconPixmap = QPixmap::fromImage(recon);
    }
}



Void MainPaintWidget::paintEvent(QPaintEvent * event)
{
    if (!m_Y) return;
    m_painter.begin(this);
    m_painter.save();
    m_painter.scale(m_zoomFactor, m_zoomFactor);
    m_painter.translate(m_translateOffset / m_zoomFactor);
    setPixelmap();
    drawReconImage();
    m_painter.restore();
    m_painter.end();
}


Void MainPaintWidget::wheelEvent(QWheelEvent *event)
{
    qreal delta = (qreal(event->delta()) / 400.0);

    if (m_zoomFactor > 4)
    {
        delta = (qreal(event->delta()) / 100.0);
    }

    if ((m_zoomFactor + delta) > 0)
    {
        qreal oldZoomFactor = m_zoomFactor;
        m_mouseLeftBtnIsPressed = true;
        m_zoomFactor += delta;
        m_translateOffset = event->pos() - (m_zoomFactor / oldZoomFactor * (event->pos() - m_translateOffset));
        repaint();
        m_mouseLeftBtnIsPressed = false;
    }
}

Void MainPaintWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (m_mouseLeftBtnIsPressed)
    {
        m_mouseLeftBtnIsPressedAndMoved = true;
        m_translateOffset = m_translateOffset + (event->pos() - m_lastPos);
        m_lastPos = event->pos();
        repaint();
    }
    else
    {
        m_pixelX = int((event->pos().rx() - m_translateOffset.rx()) / m_zoomFactor);
        m_pixelY = int((event->pos().ry() - m_translateOffset.ry()) / m_zoomFactor);
    }
}


Void MainPaintWidget::mousePressEvent(QMouseEvent *event)
{
    if(m_Y == nullptr) return;

    if (event->button() == Qt::LeftButton )
    {
        m_lastPos = event->pos();
        m_mouseLeftBtnIsPressed = true;
        m_pressedPixelX = m_pixelX;
        m_pressedPixelY = m_pixelY;
        repaint();
    }
    if (event->button() == Qt::RightButton)
    {
        m_mouseRightBtnIsPressed = true;
        m_lastPos = event->pos();
        m_pressedPixelX = m_pixelX;
        m_pressedPixelY = m_pixelY;
        repaint();
    }
}

Void MainPaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mouseLeftBtnIsPressed = false;
        m_mouseLeftBtnIsPressedAndMoved = false;
    }
    else if (event->button() == Qt::RightButton)
    {
        m_mouseRightBtnIsPressed = false;
    }
}

Void MainPaintWidget::drawReconImage()
{
    if (m_reconPixmap.isNull())
    {
        return;
    }
    m_painter.drawPixmap(0, 0, m_reconPixmap);
}

//RGB_MODE                  = 0,
//  Y_MODE                  = 1,
// Cb_MODE                  = 2,
// Cr_MODE                  = 3

Void MainPaintWidget::NextPicID()
{

    if( m_display == 3)
        m_display = 0;
    else
        m_display++;
}



