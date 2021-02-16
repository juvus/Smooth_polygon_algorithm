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
#include <QRandomGenerator>
#include <cmath>

// Program includes:
#include <smooth_polygon.h>
#include <utils.h>
#include <misc_functions.h>
#include <constants.h>

SmoothPolygon::SmoothPolygon(QPoint center, u32 max_vector_length)
    : center(center), max_vector_length(max_vector_length)
{
    // Constructor of the SmoothPolygon object
    this->min_vector_length = std::round(0.1f * max_vector_length);
    
    // Randomize the polygon
    this->randomizeSmoothPolygon(3, 10, 3, 10, 0.05, 0.45);

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
    /* Setter for the maximum vector length. The method also scale the current
       radius-vectors */

    u32 old_vector_length = this->max_vector_length;
    f32 ratio;
    u32 i;

    ratio = static_cast<f32>(length) / old_vector_length;

    // Update the vector with polygon vectors length
    for (i = 0; i < this->num_major_points; ++i)
    {
        this->vectors[i] *= ratio;
    }

    this->max_vector_length = length;
    this->min_vector_length = round(0.1f * max_vector_length);
}

void
SmoothPolygon::randomizeSmoothPolygon(u32 min_num_major_points, u32 max_num_major_points,
    u32 min_num_smooth_points, u32 max_num_smooth_points, f32 min_round_quality, 
    f32 max_round_quality)
{
    // Method for randomize the polygon parameters
    u32 i;
    f32 rnd_num;  // Temporary rnd number [0.0 ... 1.0)
    f32 tmp;  // Temporary f32 value;

    // Setup the random number generator (Securely seeded generator)
    QRandomGenerator generator  = QRandomGenerator::securelySeeded();

    this->num_major_points = generator.bounded(min_num_major_points, max_num_major_points + 1);
    this->num_smooth_points = generator.bounded(min_num_smooth_points, max_num_smooth_points + 1);
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
        tmp = min_round_quality + rnd_num * (max_round_quality - min_round_quality);
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

    // Draw the center polygon point
    pen.setStyle(Qt::SolidLine);
    pen.setColor(CENTER_COLOR);
    painter->setPen(pen);
    painter->setBrush(QColor(255, 255, 255));
    painter->drawEllipse(this->center, diameter / 2, diameter / 2);
    
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
    
    // Draw the minor lines of the polygon
    pen.setStyle(Qt::SolidLine);
    pen.setColor(MINOR_LINE_COLOR);
    //pen.setWidth(2);
    painter->setPen(pen);
    
    for (i = 1; i < this->num_minor_points; ++i) {
        painter->drawLine(this->minor_points[i], this->minor_points[i - 1]);
    }
    painter->drawLine(this->minor_points[0], this->minor_points[this->num_minor_points - 1]);
    
    // Draw the minor points of the polygon
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush(QColor(255, 255, 255));
    
    for (i = 0; i < this->num_minor_points; ++i) {
        painter->drawEllipse(this->minor_points[i], diameter / 2, diameter / 2);
    }   
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
    /* Method for calculation of the minor polygon points. Calculations are performed
       utilizing de Casteljan algorithm. */   
    
    QPoint prev_major_point;  // Previous major point of the polygon
    QPoint cur_major_point;  // Curent major point of the polygon
    QPoint next_major_point;  // Next major point of the polygon

    QPoint begin_edge_point;  // Begin edge point of the Bezier curve
    QPoint end_edge_point;  // End edge point of the Bezier curve
    QPoint result_minor_point;  // Point sliding the edge between prev and next major points
    
    u32 i, j;  // Temporary counters
    f32 round_quality;  // Current major point round quality value
    f32 delta_t;  // Delta t parameter for Bezier points calculation
    f32 t;  // t parameter for Bezier points calculation (0 - 1)
    f32 delta_between;  // Delta of distance on edge between prev_edge and next_edge points
    f32 dist_between;  // Distance on between edge from prev_edge to next_edge points

    // Clear the vector of minor polygon points
    this->minor_points.clear();

    for (i = 0; i < this->num_major_points; ++i)
    {
        // Current major point definition:
        cur_major_point = this->major_points[i];

        // Previous major point definition:
        if (i == 0)
            prev_major_point = this->major_points[this->num_major_points - 1];
        else
            prev_major_point = this->major_points[i - 1];

        // Next major point definition:
        if (i == (this->num_major_points - 1))
            next_major_point = this->major_points[0];
        else
            next_major_point = this->major_points[i + 1];

        // Calculate the begin and end point for Bezier points calculation:
        round_quality = this->round_qualities[i];
        delta_t = 1.0f / (this->num_smooth_points - 1);
        t = 0.0f;
        
        begin_edge_point = find_between_point(prev_major_point, cur_major_point,
            (1.0f - round_quality));
        end_edge_point = find_between_point(cur_major_point, next_major_point, round_quality);
        
        // Cycle to calculate the minor point positions
        for (j = 0; j < this->num_smooth_points; ++j)
        {    
            result_minor_point = calc_bezier_point(begin_edge_point, cur_major_point,
                end_edge_point, t);
            this->minor_points.append(result_minor_point);

            t += delta_t;
        }
    }
}


