/* 
================================================================================
Filename: main.cpp
Description: Main program file with entrance point
================================================================================
*/

// Standard includes:
#include <QtGui>

// Program includes:
#include <drawing_window.h>
#include <utils.h>

// Global constants
u32 WINDOW_WIDTH = 500;  // Width of the window
u32 WINDOW_HEIGHT = 500;  // Geight of the window
u32 MAX_NUM_VERTICES = 10;  // Maximum number of polygon vertices
u32 NUM_VERTICES = 6;  // Current number of polygon vertices
u32 MAX_NUM_SMOOTH_POINTS = 10;  // Maximum number of smoothing points
u32 NUM_SMOOTH_POINTS = 5;  // Current number of smoothing points
f32 ROUND_QUALITY = 0.5f;  // Current round quality
QColor LINE_COLOR(0, 0, 255);  // Color of the polygon line
QColor POINT_COLOR(255, 0, 0);  // Color of the polygon vertices points

int main(int argc, char **argv)
{
    // Create the application
    QGuiApplication app(argc, argv);

    // Create the window
    DrawingWindow drawingWindow;

    
    drawingWindow.show();

    return app.exec();
}
