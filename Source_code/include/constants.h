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
    // Program window constants
    const u32 INIT_WNDOW_WIDTH = 500;  // Width of the program window
    const u32 INIT_WNDOW_HEIGHT = 500;  // Geight of the program window
    const QColor WINDOW_BKG_COLOR(255, 255, 255);  // Background color of the window

    // Polygon constants
    const u32 MAX_NUM_MAJOR_POINTS = 20;  // Maximum number of major points
    const u32 MIN_NUM_MAJOR_POINTS = 3;  // Minimum number of major points

    const u32 MAX_NUM_SMOOTH_POINTS = 10;  // Maximum number of smooth points
    const u32 MIN_NUM_SMOOTH_POINTS = 3;  // Minimum number of smooth points

    const f32 MAX_ROUND_QUALITY = 0.45f;  // Maximum posible round quality
    const f32 MIN_ROUND_QUALITY = 0.05f;  // Minimum posible round quality
    
    const QColor CENTER_COLOR(0, 200, 0);  // Color of the polygon center point
    const QColor MAJOR_LINE_COLOR(0, 0, 255);  // Color of the major polygon lines
    const QColor MINOR_LINE_COLOR(255, 0, 0);  // Color of the minor polygon lines
}

#endif // CONSTANTS_H_