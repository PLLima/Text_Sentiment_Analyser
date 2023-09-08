#include <stdio.h>
#include "input_output.h"

#define ARGUMENT_COUNT 4

validation_t validate_input_arguments(int arg_count)
{
    validation_t situation = Invalid;

    if(arg_count == ARGUMENT_COUNT)
        situation = Valid;
    else
        printf("\nERROR: Invalid Input - Expected 3 input parameters: program <lexicon_file> <sentences_file> <output_file>.\n\n");

    return situation;
}