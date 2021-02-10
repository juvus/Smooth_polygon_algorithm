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

int main(int argc, char **argv)
{
    // Create the application
    QGuiApplication app(argc, argv);

    // Create the window
    DrawingWindow drawingWindow;
    drawingWindow.show();

    return app.exec();
}
