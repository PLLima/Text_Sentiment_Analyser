#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "input_output.h"
#include "bst.h"

#define MAX_FILELINE 1000

int main(int argc, char *argv[])
{
    const char lexicon_delimiters[] = {"\n\t"};                                    // Initialize local constants
    const char sentences_delimiters[] = {" ,.&*%\?!;:/@'\"$#=><()][}{\n\t"};
    const char performance_filename[] = "bst_app_performance.txt";

    validation_t input_args = Invalid;                                              // Initialize local variables

    char *error_char = NULL;

    FILE *lexicon_handle;
    FILE *sentences_handle;
    FILE *output_handle;
    FILE *performance_handle;

    word_bias_t data;
    bst_t *lexicon_words;
    bst_t *node;

    float sentence_bias;

    char *token = NULL;
    char fileline[MAX_FILELINE + 1];
    char fileline_copy[MAX_FILELINE + 1];

    bst_comp_find = 0;                                                              // Reset performance evaluators
    bst_comp_insert = 0;

    clock_t start;
    clock_t end;
    double app_time = 0;
    double insert_time = 0;
    double find_time = 0;

    app_time = (double) clock();                                                    // Starts clock for measuring app's total time

    input_args = validate_input_arguments(argc);                                    // Validate input arguments
    if(input_args == Invalid)                                                       // If there was any error, return it
        return input_args;

    lexicon_handle = fopen(argv[Lexicon], "r");                                     // Validate lexicon's file by trying to open it
    if(!lexicon_handle)
    {
        printf("\nERROR: Invalid Lexicon File.\n\n");
        return Invalid;
    }
    sentences_handle = fopen(argv[Sentences], "r");                                 // Validate sentences' file by trying to open it
    if(!sentences_handle)
    {
        printf("\nERROR: Invalid Sentences File.\n\n");
        return Invalid;
    }

    bst_create(&lexicon_words);                                                     // Initialize ADT to store the lexicon's words

    while(fgets(fileline, MAX_FILELINE + 1, lexicon_handle))                        // Read each of the lexicon's lines until EOF
    {
        token = strtok(fileline, lexicon_delimiters);                               // Read line token by token
        strncpy(data.word, (const char *) _strlwr(token), MAX_WORD + 1);            // The first is the word itself (converted to lowercase)
        token = strtok(NULL, lexicon_delimiters);
        data.bias = strtof(token, &error_char);                                     // The second token is the word's bias

        start = clock();
        lexicon_words = bst_insert(lexicon_words, data);                            // Inserts each word bias to the ADT
        end = clock();
        insert_time += (double) (end - start) * 1000 / CLOCKS_PER_SEC;              // Updates total insert time
    }
    fclose(lexicon_handle);                                                         // Close lexicon file

//    bst_print(lexicon_words, Pre_Left);  // FOR TESTING

    output_handle = fopen(argv[Output], "w");                                       // Create output file
    if(output_handle)
    {
        while(fgets(fileline, MAX_FILELINE + 1, sentences_handle))                  // Read each of the sentences until EOF
        {
            sentence_bias = 0;                                                      // Reset sentence's bias

            strncpy(fileline_copy, fileline, MAX_FILELINE + 1);

            token = strtok(fileline, sentences_delimiters);                         // Read line token by token
            while(token)
            {
                start = clock();
                node = bst_find(lexicon_words, (char *) _strlwr(token));            // Looks for the token's bias
                end = clock();
                find_time += (double) (end - start) * 1000 / CLOCKS_PER_SEC;        // Updates total find time
                if(node)                                                            // If found, adds its bias to the sentence's
                    sentence_bias += node->info.bias;

                token = strtok(NULL, sentences_delimiters);
            }

            fprintf(output_handle, "%+4.2f %s", sentence_bias, fileline_copy);      // Prints results in the output file
        }
        fclose(output_handle);                                                      // Close output file
    }
    else                                                                            // Warns user if output file wasn't created
        printf("\nERROR: Impossible to create output file.\n\n");

    fclose(sentences_handle);                                                       // Close sentences file

    lexicon_words = bst_destroy(lexicon_words);                                     // Free ADT's memory

    app_time = (((double) clock()) - app_time) * 1000 / CLOCKS_PER_SEC;             // Calculates app's total time

    performance_handle = fopen(performance_filename, "w");                          // Creates performance file
    fprintf(performance_handle, "BST Application Performance:\n\n"                  // Prints results in the performance file
                                "Number of Comparisons during Insertion: %llu;\n"
                                "Number of Comparisons during Search: %llu;\n\n"
                                "Total Application Time: %.6lf ms;\n"
                                "Total Insertion Time: %.6lf ms;\n"
                                "Total Search Time: %.6lf ms.",
                                bst_comp_insert, bst_comp_find, app_time, insert_time, find_time);
    fclose(performance_handle);                                                     // Closes performance file

    return Valid;                                                                   // Return no errors
}