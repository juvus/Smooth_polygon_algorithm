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
    setGeometry(100, 100, INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);

    // Create the smooth polygon object
    u32 x0 = width() / 2;  // Center point of the SmoothPolygon
    u32 y0 = height() / 2;  // Center point of the SmoothPolygon
    u32 max_vector_length = calc_largest(x0, y0);  // Max vector length

    this->smooth_polygon = new SmoothPolygon(x0, y0, max_vector_length, NUM_VERTICES,
        NUM_SMOOTH_POINTS, ROUND_QUALITY, LINE_COLOR, POINT_COLOR);

}


DrawingWindow::~DrawingWindow()
{
    // Destructor of the drawing window class
}


void
DrawingWindow::setWidth(u32 width)
{
    // Setter for the window width

    if (this->checkWidth(width)) {
        this->resize(width, height());
    }
}


void
DrawingWindow::setHeight(u32 height)
{
    // Setter for the window height

    if (this->checkHeight(height)) {
        this->resize(width(), height);
    }
}

bool
DrawingWindow::checkWidth(u32 width)
{
    // Method for check the correct window width

    // Get the screen width
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    u32 screen_width = screenGeometry.width();

    if (width > screen_width) {
        QString string = QString("ERROR: Window width is too large!");
        show_error_and_exit(string);
    }
    
    return true;
}


bool
DrawingWindow::checkHeight(u32 height)
{
    // Method for check the correct window height

    // Get the screen height
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    u32 screen_height = screenGeometry.height();

    if (height > screen_height) {
        QString string = QString("ERROR: Window height is too large!");
        show_error_and_exit(string);
    }
   
    return true;
}


bool
DrawingWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}


void
DrawingWindow::renderLater()
{
    requestUpdate();
}


void
DrawingWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
}


void
DrawingWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed())
        renderNow();
}


void
DrawingWindow::renderNow()
{
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), QColor(255, 255, 255));
    render(&painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}


void
DrawingWindow::render(QPainter *painter)
{
    // Method for render the window and all the objects

    // Render the smooth polygon
    this->smooth_polygon->render(painter);    
}
