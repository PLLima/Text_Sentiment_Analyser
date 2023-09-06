#ifndef SLL_H
#define SLL_H

#define MAX_NAME 50

typedef struct
{
    char name[MAX_NAME + 1];
    float price;
    unsigned int code;
} data_t;

typedef struct sll_s
{
    data_t info;
    struct sll_s *next;
} sll_t;

extern unsigned long long sll_comp_find;
extern unsigned long long sll_comp_insert;

sll_t *sll_create(void);
sll_t *sll_insert(sll_t *list, data_t data);
sll_t *sll_remove(sll_t *list, char *name);
sll_t *sll_find(sll_t *list, char *name);
void sll_print(sll_t *data);
void sll_print_all(sll_t *list);
sll_t *sll_destroy(sll_t *list);

#endif // SLL_H
