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

    QPoint center;  // Center point of the polygon
    u32 max_vector_length;  // Maximum length of the vector
    u32 min_vector_length;  // Minimum length of the vector
    QVector<u32> vectors;  // List of polygon vector lengths
    
    



    u32 num_major_points;  // Number of major points that form an outer polygon
    
    u32 num_minor_points;  // Number of minor points that form a smoothed polygon
    u32 num_smooth_points;  // Number of the single corner smooth points
    f32 round_quality;  // Rounding quality of the polygon corners
    // QVector<f32> round_qualities;
    QVector<QPoint> major_points;  // Vector of the major polygon points
    QVector<QPoint> minor_points;  // Vector of the minor polygon points

public:
    // Constructor of the SmoothPoligon class
    SmoothPolygon(QPoint center, u32 max_vector_length, u32 min_vector_length, 
        u32 num_major_points, u32 num_smooth_points, f32 round_quality);
       
    // Setter for the polygon center point position
    void setCenterPosition(QPoint center);

    // Setter for the maximum vector length
    void setMaxVectorLength(u32 length);

    // Setter for the minimum vector length
    void setMinVectorLength(u32 length);

    // Setter for the number of major polygon points
    void setNumMajorPoints(u32 num_points);

    // Setter for the number of corner smoothing points
    void setNumSmoothPoints(u32 num_smooth_points);

    // Setter for the rounding quality
    void setRoundQuality(f32 round_quality);

    // Method for render of the polygon in the window
    void render(QPainter *painter);
    
private:
    // Method for check the correct number of major polygon points
    bool checkNumMajorPoints(u32 num_vertices);
    
    // Method for check the correct number of corner smoothing points
    bool checkNumSmoothPoints(u32 num_smooth_points);
    
    // Method for check the correct rounding quality
    bool checkRoundQuality(f32 round_quality);

    // Method for calculation of the coordinates of major polygon points
    void calcMajorPoints();

    // Method for calculation of the coordinates of minoe polygon points
    void calcMinorPoints();
};

#endif // SMOOTH_POLYGON_H_
