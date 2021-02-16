/* 
================================================================================
Filename: main.cpp
Description: Main program file with entrance point. DrawingWindow class doesn't
    use widgets. ControlWindow class uses widgets and have all necessary 
    controls to generate different smoothing polygons.
================================================================================
*/

// Standard includes:
#include <QApplication>  // For QApplication
#include <QWidget>

// Program includes:
#include <drawing_window.h>
#include <control_window.h>
#include <utils.h>

int main(int argc, char **argv)
{
    // Create the application
    QApplication app(argc, argv);

    // Create the drawign window (without widgets)
    DrawingWindow drawing_window;
    
    // Create the control window (with widgets)
    ControlWindow control_window;

    // Share the pointers to each other
    control_window.drawing_window = &drawing_window;
    drawing_window.control_window = &control_window;

    // Show the created windows 
    drawing_window.show();
    control_window.show();

    //app.exec();
    //app2.exec();

    return (app.exec());
}
