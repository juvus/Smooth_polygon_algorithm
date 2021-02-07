/*================================================================================
  Realisation of the misc functions.
  ================================================================================*/

#include <QString>
#include <iostream>
#include <cstdlib>
#include "../include/utils.h"

void
show_error_and_exit(QString string)
{
    // Function for printing the error message to std and exitting the program

    std::cout << string.toStdString();
    exit(1);    
}


u32
calc_largest(u32 value_1, u32 value_2)
{
    // Function to calculate the lagest value of 2 values

    if (value_1 >= value_2) {
        return value_1;
    }
    else {
        return value_2;
    }
}
