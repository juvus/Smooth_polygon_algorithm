/* 
================================================================================
Filename: smooth_polygon.h
Description: Declaration of the SmoothPolygon class members. 
================================================================================
*/

#ifndef SMOOTH_POLYGON_H_
#define SMOOTH_POLYGON_H_

// Standard includes:
#include <QtGui>
#include <QVector>

// Program includes:
#include <utils.h>

class SmoothPolygon
{
    // Class for the smooth polygon. Major points of the polygon determine
    // the outer shape, when minor points determine the shape of a smooth
    // polygon. 
    // vectors -> major_points -> minor_points

    QPoint center;  // Center point of the polygon
    
    u32 max_vector_length;  // Maximum length of the vector
    u32 min_vector_length;  // Minimum length of the vector
    QVector<f32> vectors;  // List of polygon vector lengths

    u32 num_major_points;  // Number of major points that form an outer polygon
    QVector<QPoint> major_points;  // Vector of the major polygon points
    
    QVector<f32> round_qualities;  // // Rounding quality of the polygon corners 

    u32 num_smooth_points;  // Number of the single corner smooth points
    u32 num_minor_points;  // Number of minor points that form a smoothed polygon
    QVector<QPoint> minor_points;  // Vector of the minor polygon points

public:

    // Constructor of the SmoothPoligon class
    SmoothPolygon(QPoint center, u32 max_vector_length);
       
    // Setter for the polygon center point position
    void setCenterPosition(QPoint center);

    // Setter for the maximum vector length
    void setMaxVectorLength(u32 length);

    // Method for randomize the polygon parameters
    void randomizeSmoothPolygon(u32 min_num_major_points, u32 max_num_major_points,
        u32 min_num_smooth_points, u32 max_num_smooth_points, f32 min_round_quality, 
        f32 max_round_quality);

    // Method to calculate the position of polygon points
    void calcPoints();

    // Method for render of the polygon in the window
    void render(QPainter *painter);
    
private:

    // Method for calculation of the coordinates of major polygon points
    void calcMajorPoints();

    // Method for calculation of the coordinates of minoe polygon points
    void calcMinorPoints();
};

#endif // SMOOTH_POLYGON_H_
