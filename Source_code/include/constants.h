/* 
================================================================================
Filename: constants.h
Description: Different program constants
================================================================================
*/

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Standard includes:
#include <QtGui>

// Program includes:
#include <utils.h>

// Namespace with program constants
namespace Constants
{
    u32 INIT_WINDOW_WIDTH = 500;  // Width of the program window
    u32 INIT_WINDOW_HEIGHT = 500;  // Geight of the program window
    u32 MAX_NUM_MAJOR_POINTS = 10;  // Maximum number of polygon vertices
    u32 NUM_MAJOR_POINTS = 6;  // Current number of polygon vertices
    u32 MAX_NUM_SMOOTH_POINTS = 10;  // Maximum number of smoothing points
    u32 NUM_SMOOTH_POINTS = 5;  // Current number of smoothing points
    f32 MAX_ROUND_QUALITY = 0.5f;  // Maximum posible round quality
    f32 MIN_ROUND_QUALITY = 0.05f;  // Minimum posible round quality
    f32 ROUND_QUALITY = 0.5f;  // Current round quality (0.5 - 0.05)
    QColor MAJOR_LINE_COLOR(0, 0, 255);  // Color of the major polygon lines
    QColor MINOR_LINE_COLOR(255, 0, 0);  // Color of the minor polygon lines
    QColor MAJOR_POINT_COLOR(0, 0, 255);  // Color of the major polygon points
    QColor MINOR_POINT_COLOR(255, 0, 0);  // Color of the major polygon points
}

#endif // CONSTANTS_H_