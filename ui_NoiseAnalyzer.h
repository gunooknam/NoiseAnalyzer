/********************************************************************************
** Form generated from reading UI file 'NoiseAnalyzer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOISEANALYZER_H
#define UI_NOISEANALYZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MainPaintWidget.h"

QT_BEGIN_NAMESPACE

class Ui_NoiseAnalyzer
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *componentButton;
    QLabel *label_2;
    QLineEdit *siamaValue;
    QPushButton *noisepushButton;
    QLabel *label;
    QLabel *labelFilePath;
    QLabel *pnsrLabel;
    QLabel *psnrText;
    QHBoxLayout *horizontalLayout;
    MainPaintWidget *mainPaintWidget;
    MainPaintWidget *mainPaintWidget_post;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *windowSizeText;
    QPushButton *calAddHistogram;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QLabel *NoisedHist;
    QLabel *OriginHist;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NoiseAnalyzer)
    {
        if (NoiseAnalyzer->objectName().isEmpty())
            NoiseAnalyzer->setObjectName(QString::fromUtf8("NoiseAnalyzer"));
        NoiseAnalyzer->resize(1008, 873);
        centralWidget = new QWidget(NoiseAnalyzer);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        componentButton = new QPushButton(centralWidget);
        componentButton->setObjectName(QString::fromUtf8("componentButton"));

        horizontalLayout_2->addWidget(componentButton);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        siamaValue = new QLineEdit(centralWidget);
        siamaValue->setObjectName(QString::fromUtf8("siamaValue"));
        siamaValue->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(siamaValue);

        noisepushButton = new QPushButton(centralWidget);
        noisepushButton->setObjectName(QString::fromUtf8("noisepushButton"));
        noisepushButton->setEnabled(true);
        noisepushButton->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(noisepushButton);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        labelFilePath = new QLabel(centralWidget);
        labelFilePath->setObjectName(QString::fromUtf8("labelFilePath"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        labelFilePath->setFont(font);
        labelFilePath->setTextFormat(Qt::AutoText);
        labelFilePath->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(labelFilePath);

        pnsrLabel = new QLabel(centralWidget);
        pnsrLabel->setObjectName(QString::fromUtf8("pnsrLabel"));

        horizontalLayout_2->addWidget(pnsrLabel);

        psnrText = new QLabel(centralWidget);
        psnrText->setObjectName(QString::fromUtf8("psnrText"));

        horizontalLayout_2->addWidget(psnrText);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 1);
        horizontalLayout_2->setStretch(3, 2);
        horizontalLayout_2->setStretch(4, 1);
        horizontalLayout_2->setStretch(5, 6);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainPaintWidget = new MainPaintWidget(centralWidget);
        mainPaintWidget->setObjectName(QString::fromUtf8("mainPaintWidget"));
        mainPaintWidget->setMinimumSize(QSize(300, 380));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\352\265\264\353\246\274"));
        mainPaintWidget->setFont(font1);
        mainPaintWidget->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(mainPaintWidget);

        mainPaintWidget_post = new MainPaintWidget(centralWidget);
        mainPaintWidget_post->setObjectName(QString::fromUtf8("mainPaintWidget_post"));

        horizontalLayout->addWidget(mainPaintWidget_post);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 1, 4, 1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_4);

        windowSizeText = new QLineEdit(centralWidget);
        windowSizeText->setObjectName(QString::fromUtf8("windowSizeText"));
        windowSizeText->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(windowSizeText);

        calAddHistogram = new QPushButton(centralWidget);
        calAddHistogram->setObjectName(QString::fromUtf8("calAddHistogram"));

        horizontalLayout_4->addWidget(calAddHistogram);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_5);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 1);
        horizontalLayout_4->setStretch(3, 8);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setLayoutDirection(Qt::RightToLeft);
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        NoisedHist = new QLabel(widget_2);
        NoisedHist->setObjectName(QString::fromUtf8("NoisedHist"));
        NoisedHist->setMaximumSize(QSize(255, 16777215));
        NoisedHist->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(NoisedHist, 0, 2, 1, 1);

        OriginHist = new QLabel(widget_2);
        OriginHist->setObjectName(QString::fromUtf8("OriginHist"));
        OriginHist->setMaximumSize(QSize(255, 16777215));
        OriginHist->setLayoutDirection(Qt::LeftToRight);
        OriginHist->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(OriginHist, 0, 3, 1, 1);


        verticalLayout_4->addWidget(widget_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_8);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_9);


        verticalLayout_4->addLayout(horizontalLayout_6);

        verticalLayout_4->setStretch(0, 8);
        verticalLayout_4->setStretch(1, 1);

        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout_3->addWidget(widget);


        verticalLayout_2->addLayout(horizontalLayout_3);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 8);
        verticalLayout_2->setStretch(2, 1);

        verticalLayout_3->addLayout(verticalLayout_2);

        NoiseAnalyzer->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NoiseAnalyzer);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1008, 21));
        NoiseAnalyzer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NoiseAnalyzer);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        NoiseAnalyzer->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NoiseAnalyzer);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        NoiseAnalyzer->setStatusBar(statusBar);

        retranslateUi(NoiseAnalyzer);

        QMetaObject::connectSlotsByName(NoiseAnalyzer);
    } // setupUi

    void retranslateUi(QMainWindow *NoiseAnalyzer)
    {
        NoiseAnalyzer->setWindowTitle(QCoreApplication::translate("NoiseAnalyzer", "HManalyzer", nullptr));
        componentButton->setText(QCoreApplication::translate("NoiseAnalyzer", "RGB", nullptr));
        label_2->setText(QCoreApplication::translate("NoiseAnalyzer", " Sigma(Noise Level) ", nullptr));
        siamaValue->setText(QCoreApplication::translate("NoiseAnalyzer", "20", nullptr));
        noisepushButton->setText(QCoreApplication::translate("NoiseAnalyzer", "Add Noise", nullptr));
        label->setText(QCoreApplication::translate("NoiseAnalyzer", "File Path : ", nullptr));
        labelFilePath->setText(QString());
        pnsrLabel->setText(QCoreApplication::translate("NoiseAnalyzer", "PSNR_Y : ", nullptr));
        psnrText->setText(QString());
        label_4->setText(QCoreApplication::translate("NoiseAnalyzer", "Window Size", nullptr));
        windowSizeText->setText(QCoreApplication::translate("NoiseAnalyzer", "4", nullptr));
        calAddHistogram->setText(QCoreApplication::translate("NoiseAnalyzer", "Calculate Histogram", nullptr));
        label_5->setText(QCoreApplication::translate("NoiseAnalyzer", "if window size = 1 ? pixel histogram : local varince histogram", nullptr));
        NoisedHist->setText(QString());
        OriginHist->setText(QString());
        label_8->setText(QCoreApplication::translate("NoiseAnalyzer", "               [ Origin Image ]", nullptr));
        label_9->setText(QCoreApplication::translate("NoiseAnalyzer", "[ Noised Image ]               ", nullptr));
        label_3->setText(QCoreApplication::translate("NoiseAnalyzer", "Local Variance Histogram (x-axis: variance, y-axis: frequency)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NoiseAnalyzer: public Ui_NoiseAnalyzer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOISEANALYZER_H
