#pragma once

#include <QWidget>
#include <QPainter>
#include <QImage>
#include "Define.h"

#define BYTE unsigned char

class MainPaintWidget : public QWidget
{
	Q_OBJECT

public:
	MainPaintWidget(QWidget *parent);
    ~MainPaintWidget()      override;
    inline Void setWidth(Int width)           {   m_width  =  width;        }
    inline Void setHeight(Int height)         {   m_height = height;        }
    inline Int getWidth()                     {   return m_width;           }
    inline Int getHeight()                    {   return m_height;          }
    inline BYTE * getYPointer()               {   return m_Y;               }
    inline BYTE * getUPointer()               {   return m_U;               }
    inline BYTE * getVPointer()               {   return m_V;               }
    inline QString getFilename()              {   return m_filename;        }
    inline void setFilename(QString name)     {   m_filename=name;          }
    inline BYTE access(int h, int w)          {   return m_Y[h*m_width + w];}
    Void MemAlloc_YUV(Int width, Int height);
    Void MemFree_YUV(Int height);
    Int  ReadFrame_YUV(FILE * fp);
    Void setData();
    Void setPixelmap();
	Void setDrawMode(Int idx);
    BYTE * getImageComponent(ComponentID i);
    Void NextPicID();
    Void PrevPicID();
    UShort getDisplayMode()            {   return m_display;   }


private:
	Void paintEvent(QPaintEvent* event) override;
	Void wheelEvent(QWheelEvent *event) override;
	Void mouseMoveEvent(QMouseEvent *event) override;
	Void mousePressEvent(QMouseEvent *event) override;
	Void mouseReleaseEvent(QMouseEvent *event) override;

private:
	Void drawReconImage();
    // ----> image define
    Int m_width;
    Int m_height;
    // ----> yuv memory pointer//
    BYTE * m_Y;
    BYTE * m_U;
    BYTE * m_V;
    QString m_filename;

private:

	QPixmap m_reconPixmap;
	Int m_pixelX;
	Int m_pixelY;
	UInt m_imageWidth;
	UInt m_imageHeight;
	QPainter m_painter;
	QPointF m_translateOffset;
	qreal m_zoomFactor;
	Bool m_mouseLeftBtnIsPressed;
	Bool m_mouseLeftBtnIsPressedAndMoved;
	Bool m_mouseRightBtnIsPressed;
    Int m_pressedPixelX;
    Int m_pressedPixelY;
    QPointF m_lastPos;
    UShort m_display;

};
