#include "NoiseAnalyzer.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QCheckBox>
#include <QComboBox>
#include <QTableWidget>
#include <QLabel>
#include "MainPaintWidget.h"
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QTextStream>
#include <QDebug>
#include <QDialog>


Void NoiseAnalyzer::closeEvent(QCloseEvent * event){}

NoiseAnalyzer::NoiseAnalyzer(QWidget *parent)
    : m_display_mode(0)
    , QMainWindow(parent)
	, m_pMenuFile(NULL)
    , m_dlg(nullptr)
    , m_pActionOpenYuv(NULL)
{
	ui.setupUi(this);
    setWindowTitle("Noise Analyzer");
    connect(ui.componentButton, SIGNAL(clicked()), this, SLOT(NextComponentBtnClicked()));
    connect(ui.noisepushButton, SIGNAL(clicked()), this, SLOT(addNoiseBtnClicked()));
    connect(ui.calAddHistogram, SIGNAL(clicked()), this, SLOT(calHistogramClicked()));
    m_dlg = new Dialog();
    m_dlg->setWindowTitle("Qp Select");
    histSize[0] = 256;
    // BGR values range
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channel[0] = 0;
    AddMenuBar();
}

void NoiseAnalyzer::resetWhenOpen()
{
    if(ui.mainPaintWidget->getYPointer())
        ui.mainPaintWidget->MemFree_YUV(ui.mainPaintWidget->getHeight());
        if(ui.mainPaintWidget_post->getYPointer())
            ui.mainPaintWidget_post->MemFree_YUV(ui.mainPaintWidget->getHeight());
}

void NoiseAnalyzer::resetPostWhenOpen()
{
    if(ui.mainPaintWidget_post->getYPointer())
       ui.mainPaintWidget_post->MemFree_YUV(ui.mainPaintWidget->getHeight());
}

NoiseAnalyzer::~NoiseAnalyzer()
{
    if (m_pActionOpenYuv)
	{
        delete m_pActionOpenYuv;
	}
    if (m_pCompressNoise_AllIntra){
        delete m_pCompressNoise_AllIntra;
    }
    if(m_dlg){
        delete m_dlg;
    }
}

Void NoiseAnalyzer::AddMenuBar()
{
	QStatusBar *pStartusbar;
    m_pMenuFile = menuBar()->addMenu(tr("File"));
    m_pActionOpenYuv = new QAction(tr("Image Open"), this);
    m_pCompressNoise_AllIntra = new QAction(tr("Add Compression Noise Hevc All Intra"), this);
    connect(m_pActionOpenYuv,          SIGNAL(triggered()), this, SLOT(OpenImageSlot()));
    connect(m_pCompressNoise_AllIntra, SIGNAL(triggered()), this, SLOT(OpenQpWindow()));
    m_pMenuFile->addAction(m_pActionOpenYuv);
    m_pMenuFile->addAction(m_pCompressNoise_AllIntra);
	pStartusbar = statusBar();
}

Void NoiseAnalyzer::readImageToBuffer(QString fileName)
{
	QTextCodec * textCodec = QTextCodec::codecForName("eucKR");
    strcpy(m_FileName, textCodec->fromUnicode(fileName).constData());
    // 1. Parsing Data --> width, height
    QString str = QString(m_FileName);
    QRegExp rx("[(x)]");
    QStringList list = str.split(rx, QString::SkipEmptyParts);
    if(list.size()!=4){
        QMessageBox msgBox;
        msgBox.setText("Filename Format error >> image_(widthxheight).yuv ");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        return;
    }
    Int width = list.at(1).toInt();
    Int height= list.at(2).toInt();
    resetWhenOpen();
    ui.mainPaintWidget->MemAlloc_YUV(width, height);
    FILE * fp=fopen(m_FileName, "rb");
    if(!fp) {
        QMessageBox msgBox;
        msgBox.setText("File Open error");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        return;
    }
    ui.mainPaintWidget->setFilename(QString(m_FileName));
    ui.mainPaintWidget->ReadFrame_YUV(fp);
    DisplayOnePicture();
    fclose(fp);
}

Void NoiseAnalyzer::DisplayOnePicture()
{
    ui.mainPaintWidget->repaint();
}

Void NoiseAnalyzer::DisplayOnePicturePost()
{

    ui.mainPaintWidget_post->repaint();
}

void NoiseAnalyzer::NextComponentBtnClicked()
{
    ui.mainPaintWidget->NextPicID();
    ui.mainPaintWidget_post->NextPicID();
    ui.mainPaintWidget->repaint();
    ui.mainPaintWidget_post->repaint();
    ui.componentButton->setText(modeText[ui.mainPaintWidget->getDisplayMode()]);
}

void NoiseAnalyzer::addHevcCompressNoise(QString qpstr, QString inp, QString width, QString height)
{
   // add Hevc Noise
    m_hevc_outflie_name ="./out_("+width+"x"+height+").yuv";
    QString cmd="TAppEncoder.exe -c encoder_intra_main.cfg -i "+inp+" -q "+qpstr+" -f 1 -fr 30 -wdt " +width+ " -hgt "+height+" -o "+m_hevc_outflie_name;
    std::cout<<cmd.toStdString()<<std::endl;
    system(cmd.toStdString().c_str());
    resetPostWhenOpen();
    ui.mainPaintWidget_post->MemAlloc_YUV(ui.mainPaintWidget->getWidth(), ui.mainPaintWidget->getHeight());
    FILE * fp = fopen(m_hevc_outflie_name.toStdString().c_str(), "rb");
    if(!fp) {
        QMessageBox msgBox;
        msgBox.setText("reconstruction File Open error");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        return;
    }
    ui.mainPaintWidget_post->ReadFrame_YUV(fp);
    DisplayOnePicturePost();
    fclose(fp);
}

void NoiseAnalyzer::OpenQpWindow()
{
    if(m_dlg->isHidden()){
        if(ui.mainPaintWidget->getYPointer() == nullptr){
            QMessageBox msgBox;
            msgBox.setText(" No Input Image error ");
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();
            return ;
        }
        if(m_dlg->exec() == QDialog::Accepted){
            QString qpstr=m_dlg->findChild<QLineEdit*>("QpValue")->text();
            QString inp = ui.mainPaintWidget->getFilename();
            QString width= QString::number(ui.mainPaintWidget->getWidth());
            QString height= QString::number(ui.mainPaintWidget->getHeight());
            addHevcCompressNoise(qpstr, inp, width, height);
            putPSNR();
        }
    }
}

void NoiseAnalyzer::resetWhenNoise()
{
    if(ui.mainPaintWidget_post->getYPointer())
        ui.mainPaintWidget_post->MemFree_YUV(ui.mainPaintWidget->getHeight());
}


void NoiseAnalyzer::putPSNR()
{
    if( ui.mainPaintWidget->getYPointer() !=nullptr && ui.mainPaintWidget_post->getYPointer() != nullptr){
        QString psnr = calPSNR();
        ui.psnrText->setText(psnr);
    }
}

MatND NoiseAnalyzer::getHistogram(const Mat &img) {
    MatND hist;
    calcHist(&img,
            1,
            channel,
            Mat(), // No Mask
            hist, // final histogram
            1,
            histSize,
            ranges
            );
    return hist;
}

void NoiseAnalyzer::setRange(float min, float max)
{
    hranges[0] = min;
    hranges[1] = max;
    ranges[0]  = hranges;
}

QString NoiseAnalyzer::calPSNR()
{
    BYTE * Y = ui.mainPaintWidget->getYPointer();
    BYTE * Y_post = ui.mainPaintWidget_post->getYPointer();

    double sum = 0;

    int pixelCnt= (int)ui.mainPaintWidget->getWidth() * ui.mainPaintWidget->getHeight();
    for (int i=0; i < pixelCnt ; i++){
           double diff = (double)(Y[i] - Y_post[i]); // type cast
           sum += pow(diff, 2);
    }

    if (sum == 0)
        return QString("inf");

    double MSE = (double)(sum / pixelCnt);
    return QString::number(10*log10( pow(255, 2)/MSE ));

}

void NoiseAnalyzer::copyDataPaintToPaint()
{
    Int width  = ui.mainPaintWidget->getWidth();
    Int height = ui.mainPaintWidget->getHeight();
    ui.mainPaintWidget_post->MemAlloc_YUV(width, height);
    memcpy(ui.mainPaintWidget_post->getYPointer(), ui.mainPaintWidget->getYPointer(), width*height);   // Dst, Src
    memcpy(ui.mainPaintWidget_post->getUPointer(), ui.mainPaintWidget->getUPointer(), width*height/4); // Dst, Src
    memcpy(ui.mainPaintWidget_post->getVPointer(), ui.mainPaintWidget->getVPointer(), width*height/4); // Dst, Src
}

void NoiseAnalyzer::generateNoise(float sigma)
{
    BYTE * Y = ui.mainPaintWidget_post->getYPointer();
    const double mean = 0.0;
    std::default_random_engine generator;
    std::normal_distribution<double> dist(mean, sigma / 255.);
    Int width=ui.mainPaintWidget_post->getWidth();
    Int height=ui.mainPaintWidget_post->getHeight();
    // Add Gaussian noise
    for (int h=0; h<height; h++)
        for( int w=0; w<width; w++){
            double source = Y[h*width + w];
            double noise = dist(generator);
            double result = (source/255. + noise)*255.;
            Y[h*width + w] = clip8(result);
        }
}

void NoiseAnalyzer::addNoiseBtnClicked()
{
    //  write result memory buffer  //
    float sigma = stof(ui.siamaValue->text().toStdString());
    if(ui.mainPaintWidget->getYPointer() == nullptr || sigma == 0){
        QMessageBox msgBox;
        if(sigma == 0)
            msgBox.setText("sigma must more 0");
        else
            msgBox.setText("No Input Image error");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        return ;
    }
    resetWhenNoise();           // 기존에 노이즈 있으면 메모리 해제
    copyDataPaintToPaint();
    generateNoise(sigma);
    putPSNR();
    DisplayOnePicturePost();
}


Mat & NoiseAnalyzer::calcLVH(MainPaintWidget * inp, int w_size, int stride) // only stride = 1
{

    int imgWidth, imgHeight, lvhWidth, lvhHeight;

    imgWidth = inp->getWidth();
    imgHeight = inp->getHeight();
    lvhHeight = ( inp->getHeight() - w_size )/stride + 1;
    lvhWidth  = ( inp->getWidth()  - w_size )/stride + 1;

    m_lvhMat   = Mat::zeros(lvhHeight, lvhWidth, CV_32FC1);
    m_localMat = Mat::zeros(w_size, w_size, CV_8UC1);
    Scalar mean, dev;
    double max=0;
    double min=std::numeric_limits<double>::max();

    for (int h=0; h < lvhHeight ; h++){
        for(int w=0; w < lvhWidth ; w++){
            for(int k_h=0; k_h<w_size; k_h++){
                for(int k_w=0; k_w<w_size; k_w++){
                    m_localMat.at<unsigned char>(k_h, k_w) = inp->access(h + k_h, k_w + w);
                }
            }
            meanStdDev(m_localMat, mean, dev);
            if (pow(dev.val[0],2) > max)
                max = pow(dev.val[0],2);
            if (pow(dev.val[0],2) < min)
                min = pow(dev.val[0],2);
            m_lvhMat.at<float>(h, w) = pow(dev.val[0], 2); // save local variance
        }
    }
    setRange(static_cast<float>(min), static_cast<float>(max));
    return m_lvhMat;
}

// for origin image, post image
void NoiseAnalyzer::calHistogramClicked()
{
    if( ui.mainPaintWidget->getYPointer() == nullptr || ui.mainPaintWidget_post->getYPointer() == nullptr ){
        QMessageBox msgBox;
        msgBox.setText(" No Input Image and noised image error ");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        return ;
    }

    int num=stoi(ui.windowSizeText->text().toStdString());
    Mat temp, temp_noised;
    MatND his_Y, hit_Y_Noised;

    if (num == 1){ //pixel histogram
        BYTE * Y        = ui.mainPaintWidget->getYPointer();
        BYTE * Y_noised = ui.mainPaintWidget_post->getYPointer();
        setRange(0.0, 255.0);
        temp         = Mat(ui.mainPaintWidget->getHeight(),ui.mainPaintWidget->getWidth(), CV_8UC1, Y);
        his_Y        = getHistogram(temp);
        temp_noised  = Mat(ui.mainPaintWidget_post->getHeight(),ui.mainPaintWidget_post->getWidth(), CV_8UC1, Y_noised);
        hit_Y_Noised = getHistogram(temp_noised);
    }
    else{
        temp         = calcLVH(ui.mainPaintWidget,      num);
        his_Y        = getHistogram(temp);
        temp_noised  = calcLVH(ui.mainPaintWidget_post, num);
        hit_Y_Noised = getHistogram(temp_noised);
    }

    double maxVal_ori = 0;
    double minVal_ori = 0;
    double maxVal_noised = 0;
    double minVal_noised = 0;
    double maxVal=0;

    minMaxLoc(his_Y,        &minVal_ori,    &maxVal_ori,    0, 0);
    minMaxLoc(hit_Y_Noised, &minVal_noised, &maxVal_noised, 0, 0);

    if (maxVal_ori > maxVal_noised)
        maxVal = maxVal_ori;
    else
        maxVal = maxVal_noised;

    int img_h = ui.NoisedHist->size().height();
    int img_w = histSize[0];
    Mat histImg_Y(img_h, img_w, CV_8UC3, Scalar(50, 50, 50));
    int hpt = static_cast<int>(0.9 * img_h);

    for (int h=0; h<img_w; h++) {
        int intensity_Y = static_cast<int>(his_Y.at<float>(h)*hpt/maxVal);
        cv::line(histImg_Y, Point(h, img_h),Point(h, img_h-intensity_Y),Scalar(255,0,0));
    }

    ui.OriginHist->setPixmap(QPixmap::fromImage(QImage(
                                                (uchar*)histImg_Y.data,
                                                histImg_Y.cols,
                                                histImg_Y.rows,
                                                QImage::Format_RGB888)));

    Mat histImg_Y_post(img_h, img_w, CV_8UC3, Scalar(50, 50, 50));

    for (int h=0; h<img_w; h++) {
        int intensity_Y = static_cast<int>(hit_Y_Noised.at<float>(h) * hpt/maxVal);
        cv::line(histImg_Y_post, Point(h, img_h), Point(h, img_h-intensity_Y),Scalar(255,0,0));
    }

    ui.NoisedHist->setPixmap(QPixmap::fromImage(QImage(
                                                (uchar*)histImg_Y_post.data,
                                                histImg_Y_post.cols,
                                                histImg_Y_post.rows,
                                                QImage::Format_RGB888)));
}


Void NoiseAnalyzer::OpenImageSlot()
{
	QString selectedFileName;
    selectedFileName = QFileDialog::getOpenFileName(this, tr("Open Bitstream"), "", tr("Bitstream (*.yuv);;All (*.*)"));
	if (selectedFileName.length())
	{
		QLabel* pLabel = this->window()->findChild<QLabel*>("labelFilePath");
		if (pLabel)
		{
			pLabel->setText(selectedFileName);
		}

        readImageToBuffer(selectedFileName);
	}
}

void NoiseAnalyzer::dragEnterEvent(QDragEnterEvent* event)
 {
    event->acceptProposedAction();
 }

 void NoiseAnalyzer::dragMoveEvent(QDragMoveEvent* event)
 {
    event->acceptProposedAction();
 }

 void NoiseAnalyzer::dragLeaveEvent(QDragLeaveEvent* event)
 {
    event->accept();
 }








