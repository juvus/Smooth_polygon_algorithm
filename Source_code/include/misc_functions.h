/*================================================================================
  Header file for the misc functions
  ================================================================================*/

#ifndef MISC_FUNCTIONS_H_
#define MISC_FUNCTIONS_H_

#include <QString>
#include "utils.h"

// Function for printing the error message to std and exitting the program
void show_error_and_exit(QString string);

// Function to calculate the lagest value of 2 values
u32 calc_largest(u32 value_1, u32 value_2);

#endif // MISC_FUNCTIONS_H_
