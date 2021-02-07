/*================================================================================
  Header file for the drawing window class. The main purpose of the window is
  render differnt objects
  ================================================================================*/

#ifndef DRAWING_WINDOW_H_
#define DRAWING_WINDOW_H_

#include <QtGui>
#include "utils.h"
#include "smooth_polygon.h"

class DrawingWindow : public QWindow
{
    Q_OBJECT
// Class for the drawing window
    
// Methods
// ================================================================================
public:
    // Constructor of the class
    DrawingWindow(QWindow *parent = 0);  
    // Destructor of the class
    ~DrawingWindow();
    // Setter for the window width
    void setWidth(u32 width);
    // Setter for the window height
    void setHeight(u32 height);
    // Method for render the window and all the objects
    void render(QPainter *p);

public slots:
    // Slot for later render
    void renderLater();
    // Slot for now render
    void renderNow();
    
protected:
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;

private:
    // Method for check the correct window width
    bool checkWidth(u32 width);
    // Method for check the correct window height
    bool checkHeight(u32 height);
    
// Attributes
// ================================================================================
public:

private:
    SmoothPolygon *smooth_polygon;  // Pointer to the SmoothPolygon class
    QBackingStore *m_backingStore;
    QColor bkg_color;  // Window background color   
};

#endif // DRAWING_WINDOW_H_
