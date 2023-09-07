#ifndef SLL_H
#define SLL_H

#define MAX_WORD 45

typedef struct
{
    char word[MAX_WORD + 1];
    float bias;
} word_bias_t;

typedef struct sll_s
{
    word_bias_t info;
    struct sll_s *next;
} sll_t;

extern unsigned long long sll_comp_find;
extern unsigned long long sll_comp_insert;

void sll_create(sll_t **list);
sll_t *sll_insert(sll_t *list, word_bias_t data);
sll_t *sll_remove(sll_t *list, char *key);
sll_t *sll_find(sll_t *list, char *key);
void sll_print(sll_t *data);
void sll_print_all(sll_t *list);
sll_t *sll_destroy(sll_t *list);

#endif // SLL_H
