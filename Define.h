#ifndef DEFINE_H
#define DEFINE_H
#pragma once
#include <QColor>
#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// ====================================================================================================================
// Basic type redefinition
// ====================================================================================================================
typedef       void                Void;
typedef       bool                Bool;
typedef       unsigned char       UChar;
typedef       short               Short;
typedef       unsigned short      UShort;
typedef       int                 Int;
typedef       unsigned int        UInt;
typedef       double              Double;
typedef       float               Float;


static QString modeText[]={"RGB",
                           "Y",
                           "U",
                           "V"};

enum process
{
    ORIGINAL        = 0,
    POST            = 1
};


enum ComponentID
{
  RGB_MODE            = 0,
  COMPONENT_Y         = 1,
  COMPONENT_Cb        = 2,
  COMPONENT_Cr        = 3
};

enum ChannelType
{
  CHANNEL_TYPE_LUMA    = 0,
  CHANNEL_TYPE_CHROMA  = 1,
  MAX_NUM_CHANNEL_TYPE = 2
};

static inline ChannelType toChannelType (const ComponentID id)                         { return (id==COMPONENT_Y)? CHANNEL_TYPE_LUMA : CHANNEL_TYPE_CHROMA; }
#define clip8(var) ((var > 255) ? 255 : (var < 0) ? 0 : var)
#define MIN( m, M ) ( m < M ? m: M )
#endif // DEFINE_H
