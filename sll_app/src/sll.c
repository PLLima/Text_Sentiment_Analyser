#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long sll_comp_find = 0;
unsigned long long sll_comp_insert = 0;

void sll_create(sll_t **list)
{
    *list = NULL;
}

sll_t *sll_insert(sll_t *list, word_bias_t data)
{
    sll_t *new;
    sll_t *aux = list;
    sll_t *previous = NULL;

    new = (sll_t *) malloc(sizeof(sll_t));
    new->info = data;

    while(aux)
    {
        sll_comp_insert++;
        previous = aux;
        aux = aux->next;
    }

    sll_comp_insert++;
    new->next = aux;
    if(previous)
        previous->next = new;
    else
        list = new;

    return list;
}

sll_t *sll_remove(sll_t *list, char *key)
{
    sll_t *previous = NULL;
    sll_t *aux = list;

    while (aux && strncmp(aux->info.word, key, MAX_WORD + 1))
    {
        previous = aux;
        aux = aux->next;
    }

    if (aux)
    {
        if(!previous)
            list = aux->next;
        else
            previous->next = aux->next;

        free(aux);
    }

    return list;
}

sll_t *sll_find(sll_t *list, char *key)
{
    sll_t *aux = NULL;

    sll_comp_find++;
    if(list)
        for(aux = list; aux && strncmp(aux->info.word, key, MAX_WORD + 1); aux = aux->next)
            sll_comp_find++;

    return aux;
}

void sll_print(sll_t *data)
{
    if(data)
        printf("\n(%.2f) %s\n",
               data->info.bias,
               data->info.word);
    else
        printf("\nWord not found.\n");
}

void sll_print_all(sll_t *list)
{
    sll_t *aux = list;
    if (aux)
    {
        printf("\nLexicon:\n"
           "\n((Bias) Word)\n"
           "\n");
        for (aux = list; aux; aux = aux->next)
        {
            printf("\n(%.2f) %s\n",
                  aux->info.bias,
                  aux->info.word);
        }
    }
    else
        printf("\nEmpty list.\n");
}

sll_t *sll_destroy(sll_t *list)
{
    sll_t *aux;

    while(list)
    {
        aux = list;
        list = list->next;
        free(aux);
    }

    free(list);
    return NULL;
}
