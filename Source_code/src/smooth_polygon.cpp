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

SmoothPolygon::SmoothPolygon(QPoint center, u32 max_vector_length)
{
    // Constructor of the SmoothPolygon object
    
    this->center = center;
    this->max_vector_length = max_vector_length;
    this->min_vector_length = std::round(0.1f * max_vector_length);
    
    // Randomize the polygon
    this->randomizeSmoothPolygon();

    // Calculate coordinates of the polygon major and minor points (de Casteljan algorithm)
    this->calcMajorPoints();
    this->calcMinorPoints();
}

void
SmoothPolygon::setCenterPosition(QPoint center)
{
    // Setter for the polygon center position
    
    this->center = center;
}

void
SmoothPolygon::setMaxVectorLength(u32 length)
{
    // Setter for the maximum vector length

    this->max_vector_length = length;
    this->min_vector_length = round(0.1f * max_vector_length);
}

void
SmoothPolygon::randomizeSmoothPolygon()
{
    // Method for randomize the polygon parameters

    u32 i;
    f32 rnd_num;  // Temporary rnd number [0.0 ... 1.0)
    f32 tmp;  // Temporary f32 value;
    using namespace Constants;

    // Setup the random number generator (Securely seeded generator)
    QRandomGenerator generator  = QRandomGenerator::securelySeeded();

    this->num_major_points = generator.bounded(MIN_NUM_MAJOR_POINTS, MAX_NUM_MAJOR_POINTS + 1);
    this->num_smooth_points = generator.bounded(MIN_NUM_SMOOTH_POINTS, MAX_NUM_SMOOTH_POINTS + 1);
    this->num_minor_points = this->num_major_points * this->num_smooth_points;

    // Randomize the vector of polygon radius-vectors
    this->vectors.clear();
    for (i = 0; i < this->num_major_points; ++i)
    {
        rnd_num = static_cast<f32>(generator.generateDouble());
        tmp = this->min_vector_length + rnd_num * \
            (this->max_vector_length - this->min_vector_length);
        this->vectors.append(tmp);
    }

    // Randomize the vector of round qualities
    this->round_qualities.clear();
    for (i = 0; i < this->num_major_points; ++i)
    {
        rnd_num = static_cast<f32>(generator.generateDouble());
        tmp = MIN_ROUND_QUALITY + rnd_num * (MAX_ROUND_QUALITY - MIN_ROUND_QUALITY);
        this->round_qualities.append(tmp);
    }
}

void 
SmoothPolygon::calcPoints()
{
    // Method to calculate the position of polygon points
    
    this->calcMajorPoints();
    this->calcMinorPoints();
}

void
SmoothPolygon::render(QPainter *painter)
{
    // Method for render of the polygon

    QPen pen;
    u32 diameter = 6;
    u32 i;
    using namespace Constants;
    
    // Set the antialiasing
    painter->setRenderHint(QPainter::Antialiasing);

    // Draw the major lines of the polygon
    pen.setStyle(Qt::DashLine);
    pen.setColor(MAJOR_LINE_COLOR);
    painter->setPen(pen);
    
    for (i = 1; i < this->num_major_points; ++i) {
        painter->drawLine(this->major_points[i], this->major_points[i - 1]);
    }
    painter->drawLine(this->major_points[0], this->major_points[this->num_major_points - 1]);

    // Draw the major points of the polygon
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush(QColor(255, 255, 255));
    
    for (i = 0; i < this->num_major_points; ++i) {
        painter->drawEllipse(this->major_points[i], diameter / 2, diameter / 2);
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
SmoothPolygon::calcMajorPoints()
{
    // Method for calculation of the major polygon point

    u32 i;
    f32 angle = 0.0f;  // Initial angle
    f32 angle_delta = 2.0f * M_PI / this->num_major_points;
    s32 x_tmp, y_tmp;  // Temporary points coordinates (around polygon center point)
    u32 x_coord, y_coord;  // Point coordinates around in the window
    f32 vector;  // Current polygon radius-vector

    this->major_points.clear();    
    for (i = 0; i < this->num_major_points; ++i)
    {
        vector = this->vectors[i];

        // Calculation of the new point coordinates
        x_tmp = static_cast<s32>(std::round(vector * std::cos(angle)));
        y_tmp = static_cast<s32>(std::round(vector * std::sin(angle)));
        x_coord = static_cast<u32>(this->center.x() + x_tmp);
        y_coord = static_cast<u32>(this->center.y() - y_tmp);

        // Append the point to the vertices qvector
        this->major_points.append(QPoint(x_coord, y_coord));

        // Calculate point coordinates for next angle value
        angle += angle_delta;
    }
}

void
SmoothPolygon::calcMinorPoints()
{
    // Method for calculation of the extended polygon vertices (de Casteljan algorithm)

    qDebug() << "Calculate extended vertices";
}


