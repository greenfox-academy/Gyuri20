#include <stdio.h>
#include <stdlib.h>
#define TOTORO 19

// Define the TOTORO macro which holds the number of students in our class

int main()
{
    // If TOTORO is not defined throw a preprocessor error
    #error 
    
    printf("Class members: %d", TOTORO);
    return 0;
}