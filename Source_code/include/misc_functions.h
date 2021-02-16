/* 
================================================================================
Filename: misc_functions.h
Description: Declaration of the misc functions 
================================================================================
*/

#ifndef MISC_FUNCTIONS_H_
#define MISC_FUNCTIONS_H_

// Standard includes:
#include <QString>
#include <QPoint>

// Program includes:
#include <utils.h>

// Function for printing the error message to std and exitting the program
void show_error_and_exit(QString string);

// Function to calculate the lowest value of 2 values
u32 calc_lowest(u32 value_1, u32 value_2);

// Function to calculate the point position between other two points
QPoint find_between_point(QPoint begin_point, QPoint end_point, f32 alpha);

// Function to calculate the arbitrary Bezier point
QPoint calc_bezier_point(QPoint begin_point, QPoint middle_point,
    QPoint end_point, f32 t);

#endif // MISC_FUNCTIONS_H_
