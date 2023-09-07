#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"
#include "sll.h"

int main(int argc, char *argv[])
{
    validation_t input_args = Invalid;              // Initialize local variables

    sll_comp_find = 0;                              // Reset comparison counters
    sll_comp_insert = 0;
    
    input_args = validate_input_arguments(argc);    // Validate input arguments
    if(input_args == Invalid)
        return input_args;
    
    

    return 0;
}