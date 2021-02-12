/* 
================================================================================
Filename: drawing_window.cpp
Description: Definition of the DrawingWindow class methods. This is the main
    window of the application
================================================================================
*/

// Standard includes:

// Program includes:
#include <drawing_window.h>
#include <utils.h>
#include <misc_functions.h>
#include <smooth_polygon.h>
#include <constants.h>

DrawingWindow::DrawingWindow(QWindow *parent) : QWindow(parent), 
    m_backingStore(new QBackingStore(this))
{
    // Constructor of the DrawingWindow class
    // Local use of namespace with constants
    using namespace Constants;

    // Set title and set the window geometry
    setTitle("Smooth polygon drawing");
    setGeometry(100, 100, INIT_WNDOW_WIDTH, INIT_WNDOW_HEIGHT);

    // Create the smooth polygon object
    u32 x0 = width() / 2;  // Center point of the SmoothPolygon
    u32 y0 = height() / 2;  // Center point of the SmoothPolygon
    u32 max_vector_length = calc_lowest(x0, y0);  // Max vector length

    this->smooth_polygon = new SmoothPolygon(QPoint(x0, y0), max_vector_length);
}

DrawingWindow::~DrawingWindow()
{
    // Destructor of the drawing window class
    delete this->smooth_polygon;
}

bool
DrawingWindow::event(QEvent *event)
{
    // Method for the handling of different events
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

void
DrawingWindow::mousePressEvent(QMouseEvent *event)
{
    // Method for handle the mouse press event on the window
    if (event->button() == Qt::LeftButton) 
    {
        // Create new polygon
        this->smooth_polygon->randomizeSmoothPolygon();
        this->smooth_polygon->calcPoints();

        // Request update of the window
        requestUpdate();
    }
}


void
DrawingWindow::renderLater()
{
    // Method (slot) for sending the event for window update request
    requestUpdate();
}

void
DrawingWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    // Method for the resize window event
    
    // Guard very small window size
    if ((width() <= 100) || (height() <= 100))
        return;
    
    m_backingStore->resize(resizeEvent->size());

    // Recalculate the polygon points
    u32 x0 = width() / 2;  // Center point of the SmoothPolygon
    u32 y0 = height() / 2;  // Center point of the SmoothPolygon
    u32 max_vector_length = calc_lowest(x0, y0);  // Max vector length
    
    this->smooth_polygon->setCenterPosition(QPoint(x0, y0));
    this->smooth_polygon->setMaxVectorLength(max_vector_length);
    this->smooth_polygon->calcPoints();

    // Request update of the window
    requestUpdate();
}

void
DrawingWindow::exposeEvent(QExposeEvent *)
{
    // Method for the expose window event
    if (isExposed())
        renderNow();
}

void
DrawingWindow::renderNow()
{
    // Method (slot) for render the window
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    // Fill the whole window with background color
    painter.fillRect(0, 0, width(), height(), QColor(255, 255, 255));

    // Render the SmoothPolygon object
    this->smooth_polygon->render(&painter);

    painter.end();
    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}