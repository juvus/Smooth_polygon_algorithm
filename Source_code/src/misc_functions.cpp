/* 
================================================================================
Filename: misc_functions.cpp
Description: Definition of the misc functions
================================================================================
*/

// Standard includes:
#include <QString>
#include <QPoint>
#include <iostream>
#include <cmath>

// Program includes:
#include <utils.h>

void
show_error_and_exit(QString string)
{
    // Function for printing the error message to std and exitting the program

    std::cout << string.toStdString();
    exit(1);    
}

u32
calc_lowest(u32 value_1, u32 value_2)
{
    // Function to calculate the lowest value of 2 values

    if (value_1 <= value_2) {
        return value_1;
    }
    else {
        return value_2;
    }
}

QPoint 
find_between_point(QPoint begin_point, QPoint end_point, f32 alpha)
{
    // Function to calculate the point position between other two points
    f32 x_begin = static_cast<f32>(begin_point.x());
    f32 y_begin = static_cast<f32>(begin_point.y());
    f32 x_end = static_cast<f32>(end_point.x());
    f32 y_end = static_cast<f32>(end_point.y());
    f32 x_result, y_result;
    QPoint result;

    x_result = x_begin + alpha * (x_end - x_begin);
    y_result = y_begin + alpha * (y_end - y_begin);

    result.setX(static_cast<int>(std::round(x_result)));
    result.setY(static_cast<int>(std::round(y_result)));

    return result;
}

QPoint 
calc_bezier_point(QPoint begin_point, QPoint middle_point, QPoint end_point, f32 t)
{
    // Function to calculate the arbitrary Bezier point
    f32 x_begin = static_cast<f32>(begin_point.x());
    f32 y_begin = static_cast<f32>(begin_point.y());
    f32 x_middle = static_cast<f32>(middle_point.x());
    f32 y_middle = static_cast<f32>(middle_point.y());
    f32 x_end = static_cast<f32>(end_point.x());
    f32 y_end = static_cast<f32>(end_point.y());
    f32 x_result, y_result;
    QPoint result;

    // Calculate x point coordinate
    x_result = std::pow((1 - t), 2) * x_begin + 2 * (1 - t) * t * x_middle + \
        std::pow(t, 2) * x_end;

    // Calcualte y point coordinate
    y_result = std::pow((1 - t), 2) * y_begin + 2 * (1 - t) * t * y_middle + \
        std::pow(t, 2) * y_end;

    result.setX(static_cast<int>(std::round(x_result)));
    result.setY(static_cast<int>(std::round(y_result)));

    return result;
}