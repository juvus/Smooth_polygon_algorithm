/* 
================================================================================
Filename: drawing_window.h
Description: Declaration of the DrawingWindow class methods. This is the main
    window of the application
================================================================================
*/

#ifndef DRAWING_WINDOW_H_
#define DRAWING_WINDOW_H_

// Standard includes:
#include <QtGui>

// Program includes:
#include <utils.h>
#include <smooth_polygon.h>

class DrawingWindow : public QWindow
{
    // Class for the DrawingWindow
    Q_OBJECT

public:
    // Constructor of the class
    DrawingWindow(QWindow *parent = 0); 

    // Destructor of the class
    ~DrawingWindow();

public slots:
    // Slot for sending the event for window update request
    void renderLater();

    // Slot for render the window
    void renderNow();
    
protected:
    // Method for the handling of different events
    bool event(QEvent *event) override;

    // Method for handle the mouse press event on the window
    void mousePressEvent(QMouseEvent *event) override;

    // Method for the resize window event
    void resizeEvent(QResizeEvent *event) override;

    // Method for the expose window event
    void exposeEvent(QExposeEvent *event) override;   

private:
    SmoothPolygon *smooth_polygon;  // Pointer to the SmoothPolygon class
    QBackingStore *m_backingStore;  // Provides a drawing area for window
};

#endif // DRAWING_WINDOW_H_
