#include <QtWidgets/QApplication>
#include "NoiseAnalyzer.h"
#include <stdlib.h>

// [ support only yuv format ]
// input format define
//     ->imgname_(widthxheight).yuv !!
// image format define
//     -> yuv420

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NoiseAnalyzer w;
    w.show();
    return a.exec();
}
