#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_NoiseAnalyzer.h"
#include <QMessageBox>
#include <random>
#include <math.h>
#include "Dialog.h"
#include "Histogram.h"
#include <QtCharts/QChartView>

using namespace QtCharts; // setting namespace
using namespace std;
using namespace cv;
class NoiseAnalyzer : public QMainWindow
{
	Q_OBJECT

private:
    Dialog                   *m_dlg;
    QChart                   * m_chart;
    Histogram                * m_origin_histo; //
    Histogram                * m_post_histo; //

    //  histogram
    int histSize[1];
    float hranges[2];
    const float* ranges[1];
    int channel[1];
    Mat                      m_lvhMat;
    Mat                      m_localMat;
    Mat                      originLVH;
    Mat                      NoisedLVH;
    UShort                   m_display_mode;
    Int                      m_PicComonentsID;
    Ui::NoiseAnalyzer        ui;
	QMenu                    *m_pMenuFile;
    QAction                  *m_pActionOpenYuv;
    QAction                  *m_pCompressNoise_AllIntra;
    QAction                  *m_pActionPrevComponents;
    QAction                  *m_pActionNextComponents;
    char                      m_FileName[512];
    QString                   m_hevc_outflie_name;


protected:
	Void closeEvent(QCloseEvent* event) override;

public:
    void copyDataPaintToPaint();
    NoiseAnalyzer(QWidget *parent = Q_NULLPTR);
    void resetWhenOpen();
    void resetPostWhenOpen();
    void resetWhenNoise();
    void putPSNR();
    Mat & calcLVH(MainPaintWidget * inp, int w_size, int stride=1);
    MatND getHistogram(const Mat & img);
    void setRange(float min, float max);

    QString calPSNR();
    void generateNoise(float sigma);
    ~NoiseAnalyzer() override;

private:
	Void AddMenuBar();
    Void readImageToBuffer(QString fileName);
	Void Init(const char* fileName);
    Void DisplayOnePicture();
    Void NoiseAnalyzer::DisplayOnePicturePost();

private slots:
    void NextComponentBtnClicked();
    void OpenImageSlot();
    void OpenQpWindow();
    void addNoiseBtnClicked();
    void calHistogramClicked();
    void addHevcCompressNoise(QString qpstr, QString inp, QString width, QString height);
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;

};
