#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "input_output.h"
#include "sll.h"

#define MAX_FILELINE 1000

int main(int argc, char *argv[])
{
    const char lexicon_delimiters[] = {" \n\t"};                            // Initialize local constants
    const char sentences_delimiters[] = {" ,&.*%\?!;/'@\"$#=><()][}{:\n\t"};

    validation_t input_args = Invalid;                                      // Initialize local variables

    clock_t start;
    clock_t end;

    char *error_char = NULL;

    FILE *lexicon_handle;
    FILE *sentences_handle;
//    FILE *output_handle;

    word_bias_t data;
    sll_t *lexicon_words;

    char *token = NULL;
    char fileline[MAX_FILELINE + 1];

    sll_comp_find = 0;                                                      // Reset comparison counters
    sll_comp_insert = 0;
    
    input_args = validate_input_arguments(argc);                            // Validate input arguments
    if(input_args == Invalid)                                               // If there was any error, return it
        return input_args;

    lexicon_handle = fopen(argv[Lexicon], "r");                             // Validate lexicon's file by trying to open it
    if(!lexicon_handle)
    {
        printf("\nERROR: Invalid Lexicon File.\n\n");
        return Invalid;
    }
    sentences_handle = fopen(argv[Sentences], "r");                         // Validate sentences' file by trying to open it
    if(!sentences_handle)
    {
        printf("\nERROR: Invalid Sentences File.\n\n");
        return Invalid;
    }

    sll_create(&lexicon_words);                                             // Initialize ADT to store the lexicon's words

    while(fgets(fileline, MAX_FILELINE + 1, lexicon_handle))                // Read each of the lexicon's lines until EOF
    {
        token = strtok(fileline, lexicon_delimiters);                       // Read line token by token
        strncpy(data.word, (const char *) _strlwr(token), MAX_WORD + 1);    // The first is the word itself (converted to lowercase)
        token = strtok(NULL, lexicon_delimiters);
        data.bias = strtof(token, &error_char);                             // The second token is the word's bias

        lexicon_words = sll_insert(lexicon_words, data);                    // Inserts each word bias to the ADT
    }

//    sll_print_all(lexicon_words);  // FOR TESTING

    lexicon_words = sll_destroy(lexicon_words);                             // Free ADT's memory

    fclose(lexicon_handle);                                                 // Close lexicon file
    fclose(sentences_handle);                                               // Close sentences file
//    fclose(output_handle);                                                  // Close output file

    return Valid;                                                           // Return no errors
}