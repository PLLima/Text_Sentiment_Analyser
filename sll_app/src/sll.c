#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long sll_comp_find = 0;
unsigned long long sll_comp_insert = 0;

sll_t *sll_create(void)
{
    return NULL;
}

sll_t *sll_insert(sll_t *list, data_t data)
{
    sll_t *new;
    sll_t *aux = list;
    sll_t *previous = NULL;

    new = (sll_t *) malloc(sizeof(sll_t));
    new->info = data;

    while(aux && new->info.code > aux->info.code)
    {
        previous = aux;
        aux = aux->next;
    }

    new->next = aux;
    if(previous)
        previous->next = new;
    else
        list = new;

    return list;
}

sll_t *sll_remove(sll_t *list, char *name)
{
    sll_t *previous = NULL;
    sll_t *aux = list;

    while (aux && strcmp(aux->info.name, name))
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

sll_t *sll_find(sll_t *list, char *name)
{
    sll_t *aux = NULL;

    if(list)
        for(aux = list; aux && strcmp(aux->info.name, name); aux = aux->next);

    return aux;
}

void sll_print(sll_t *data)
{
    if(data)
        printf("\n[%d] %s - R$ %.2f\n",
               data->info.code,
               data->info.name,
               data->info.price);
    else
        printf("\nProduto nao encontrado.\n");
}

void sll_print_all(sll_t *list)
{
    sll_t *aux = list;
    if (aux)
    {
        printf("\nTabela de Produtos:\n"
           "\n[Codigo] Nome - Preco\n"
           "\n");
        for (aux = list; aux; aux = aux->next)
        {
            printf("[%d] %s - R$ %.2f\n",
                   aux->info.code,
                   aux->info.name,
                   aux->info.price);
        }
    }
    else
        printf("\nLista Vazia.\n");
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
