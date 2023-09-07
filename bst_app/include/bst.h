#ifndef BST_H
#define BST_H

#define MAX_WORD 45

typedef struct
{
    char word[MAX_WORD + 1];
    float bias;
} word_bias_t;

typedef struct bst_s
{
    word_bias_t info;
    struct bst_s *left;
    struct bst_s *right;
} bst_t;

typedef enum
{
    None,
    Pre_Left,
    Pre_Right,
    Cen_Left,
    Cen_Right,
    Pos_Left,
    Pos_Right
} walking_t;

extern unsigned long long bst_comp_find;
extern unsigned long long bst_comp_insert;

void bst_create(bst_t **root);
bst_t *bst_find(bst_t *root, char *key);
int bst_height(bst_t *root);
int bst_bf_node(bst_t *root);
int bst_bf_int(bst_t *root, int *max_bf);
int bst_bf(bst_t *root);
bst_t *bst_insert(bst_t *root, word_bias_t key);
void bst_print(bst_t *root, walking_t walking);
void bst_print_pre_left(bst_t *root, int level);
void bst_print_pre_right(bst_t *root, int level);
void bst_print_cen_left(bst_t *root, int level);
void bst_print_cen_right(bst_t *root, int level);
void bst_print_pos_left(bst_t *root, int level);
void bst_print_pos_right(bst_t *root, int level);
int bst_count_nodes(bst_t *root);
bst_t *bst_destroy(bst_t *root);

#endif // BST_H
