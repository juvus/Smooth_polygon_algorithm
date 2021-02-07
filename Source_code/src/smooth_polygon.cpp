/* 
================================================================================
Filename: smooth_polygon.cpp
Description: Definition of the SmoothPolygon class methods. 
================================================================================
*/

// Standard includes:
#include <QtGui>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QRandomGenerator>
#include <cmath>

// Program includes:
#include <smooth_polygon.h>
#include <utils.h>
#include <misc_functions.h>
#include <constants.h>

SmoothPolygon::SmoothPolygon(QPoint center, u32 max_vector_length, u32 min_vector_length, 
    u32 num_major_points, u32 num_smooth_points, f32 round_quality)
{
    // Constructor of the SmoothPolygon object
    
    this->center = center;
    this->max_vector_length = max_vector_length;
    this->min_vector_length = min_vector_length;
    
    if (this->checkNumMajorPoints(num_major_points))
        this->num_major_points = num_major_points;

    if (this->checkNumSmoothPoints(num_smooth_points))
        this->num_smooth_points = num_smooth_points;

    if (this->checkRoundQuality(round_quality))
        this->round_quality = round_quality;
    
    this->num_minor_points = num_major_points * num_smooth_points;

    // Calculate coordinates of the polygon major and minor points (de Casteljan algorithm)
    this->calcMajorPoints();
    this->calcMinorPoints();
}

void
SmoothPolygon::setCenterPosition(QPoint center)
{
    // Setter for the polygon center position
    
    this->center = center;

    // Calculate coordinates of the polygon major and minor points
    this->calcMajorPoints();
    this->calcMinorPoints();
}





void
SmoothPolygon::setMaxVectorLength(u32 length)
{
    // Setter for the maximum vector length

    // Assignment of the maximum vector length
    if (this->checkMaxVectorLength(length)) {
        this->max_vector_length = length;
    }

    // Recalculate the polygon major and extended vertices
    this->calculateVertices();
    this->calculateExtendedVertices();
}


void
SmoothPolygon::setNumVertices(u32 num_vertices)
{
    // Setter for the number of vertices

    // Assignment of the number of vertices
    if (this->checkNumVertices(num_vertices)) {
        this->num_vertices = num_vertices;
    }

    // Recalculate the polygon major and extended vertices
    this->calculateVertices();
    this->calculateExtendedVertices();
}


void
SmoothPolygon::setNumSmoothPoints(u32 num_smooth_points)
{
    // Setter for the number of corner smoothing points

    // Assignment of the number of corner smoothing points
    if (this->checkNumSmoothPoints(num_smooth_points)) {
        this->num_smooth_points = num_smooth_points;
    }

    // Recalculate the polygon major and extended vertices
    this->calculateVertices();
    this->calculateExtendedVertices();
}


void
SmoothPolygon::setRoundQuality(f32 round_quality)
{
    // Setter for the rounding quality

    // Assignment of the rounding quality
    if (this->checkRoundQuality(round_quality)) {
        this->round_quality = round_quality;
    }

    // Recalculate the polygon major and extended vertices
    this->calculateVertices();
    this->calculateExtendedVertices();
}


void
SmoothPolygon::setLineColor(QColor line_color)
{
    // Setter for the polygon lines color

    this->line_color = line_color;
}


void
SmoothPolygon::setPointColor(QColor point_color)
{
    // Setter for the polygon major points color

    this->point_color = point_color;
}


bool SmoothPolygon::checkCenterPosition(u32 x0, u32 y0)
{
    // Method for check the correct center position
    
    if ((x0 > window_width) || (y0 > window_height)) {
        QString string = QString("ERROR: x0 or y0 coordinates is out of the screen!"); 
        show_error_and_exit(string);
    }

    return true;
}


bool
SmoothPolygon::checkMaxVectorLength(u32 length)
{
    // Method for check the correct maximum vector length

    u32 max_horizontal_length = this->window_width - this->x0;
    u32 max_vertical_length = this->window_height - this->y0;

    if ((length > max_horizontal_length) || (length > max_vertical_length)) {
        QString string = QString("ERROR: Vector length is too long!"); 
        show_error_and_exit(string); 
    }

    return true;
}


bool
SmoothPolygon::checkNumVertices(u32 num_vertices)
{
    // Method for check the correct number of vectors

    if (num_vertices > MAX_NUM_VERTICES) {
        QString string = QString("ERROR: Number of vertices is to large (max is %1)")
            .arg(MAX_NUM_VERTICES);
        show_error_and_exit(string);
    }

    return true;
}


bool
SmoothPolygon::checkNumSmoothPoints(u32 num_smooth_points)
{
    // Method for check the correct number of corner smoothing points

    if (num_smooth_points > MAX_NUM_SMOOTH_POINTS) {
        QString string = QString("ERROR: Number of smooth points is to large (max is %1)")
            .arg(MAX_NUM_SMOOTH_POINTS);
        show_error_and_exit(string);
    }

    return true;
}


bool
SmoothPolygon::checkRoundQuality(f32 round_quality)
{
    // Method for check the correct rounding quality. The rounding
    // quality should be in the range [0.0, 0.5]

    if ((round_quality < 0.1) || (round_quality > 0.5)) {
        QString string = QString("ERROR: Round quality should be in range [0.0, 0.5]");
        show_error_and_exit(string);
    }

    return true;
}


void
SmoothPolygon::render(QPainter *painter)
{
    // Method for render of the polygon

    QPen pen;
    u32 diameter = 5;
    
    // Set the antialiasing
    painter->setRenderHint(QPainter::Antialiasing);

    // Draw the major lines of the polygon
    pen.setStyle(Qt::DashLine);
    pen.setColor(QColor(0, 0, 200));
    painter->setPen(pen);
    
    for (u32 i = 1; i < this->num_vertices; ++i) {
        painter->drawLine(this->vertices[i], this->vertices[i - 1]);
    }
    painter->drawLine(this->vertices[0], this->vertices[this->num_vertices - 1]);

    // Draw the major points of the polygon
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush(QColor(255, 255, 255));
    
    for (u32 i = 0; i < this->num_vertices; ++i) {
        painter->drawEllipse(this->vertices[i], diameter / 2, diameter / 2);
    }




    /*

    // Coordinates of the vertices
    int diameter = 6;
    QPoint p0(100, 100);
    QPoint p1(250, 400);
    QPoint p2(400, 100);
      
    // Set the antialiasing
    painter->setRenderHint(QPainter::Antialiasing);

    // Set the pen and brush for the drawing
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0, 0, 200)); // Blue

    // Draw the point on the window
    painter->drawEllipse(p0, diameter / 2, diameter / 2);
    painter->drawEllipse(p1, diameter / 2, diameter / 2);
    painter->drawEllipse(p2, diameter / 2, diameter / 2);

    // Draw the interpolation points using the quadratic Bezier curve (Casteljau algorithm)
    painter->setBrush(QColor(200, 0, 0)); // Red
    float t = 0.0;
    int numPoints = 20;
    int pt_x, pt_y;
   
    for (int i = 0; i < numPoints; ++i) {
        t = t + 1.0 / (numPoints + 1);
        pt_x = std::round(std::pow(1.0 - t, 2)*p0.x() + 2*t*(1 - t)*p1.x() + std::pow(t, 2)*p2.x());
        pt_y = std::round(std::pow(1.0 - t, 2)*p0.y() + 2*t*(1 - t)*p1.y() + std::pow(t, 2)*p2.y());
        painter->drawEllipse(QPoint(pt_x, pt_y), diameter / 2, diameter / 2);
    } 
    */   
}


void
SmoothPolygon::calculateVertices()
{
    // Method for calculation of the major polygon vertices

    f32 angle = 0.0f;  // Initial angle
    f32 angle_delta = 2 * M_PI / this->num_vertices;
    s32 x_tmp, y_tmp;  // Temporary points coordinates (around (0,0) point)
    u32 x_coord, y_coord;  // Point coordinates around x0, y0 point
    f32 radius;  // Random radius-vector 
    f32 rnd_num;  // Rnadom number [0.1, 1)
    
    // Setup the random number generator
    QRandomGenerator gen  = QRandomGenerator::securelySeeded(); // Securely seeded generator.
        
    for (u32 i = 0; i < this->num_vertices; ++i) {

        // Generate the random number
        rnd_num = 0.1f + 0.9f * static_cast<f32>(gen.generateDouble());       

        // Calculation of the new point coordinates
        radius = this->max_vector_length * rnd_num; 
        x_tmp = static_cast<s32>(std::round(radius * std::cos(angle)));
        y_tmp = static_cast<s32>(std::round(radius * std::sin(angle)));
        x_coord = this->x0 + x_tmp;
        y_coord = this->y0 - y_tmp;

        // Append the point to the vertices qvector
        this->vertices.append(QPoint(x_coord, y_coord));

        // New angle value
        angle += angle_delta;
    }
}


void
SmoothPolygon::calculateExtendedVertices()
{
    // Method for calculation of the extended polygon vertices (de Casteljan algorithm)

    qDebug() << "Calculate extended vertices";
}


