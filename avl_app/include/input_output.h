#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

typedef enum
{
    Valid,
    Invalid
} validation_t;

typedef enum
{
    Program,
    Lexicon,
    Sentences,
    Output
} arguments_t;

validation_t validate_input_arguments(int arg_count);

#endif // INPUT_OUTPUT_H