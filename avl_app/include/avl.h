#ifndef AVL_H
#define AVL_H

#define MAX_WORD 45

typedef struct
{
    char word[MAX_WORD + 1];
    float bias;
} word_bias_t;

typedef struct avl_s
{
    word_bias_t info;
    int bf;
    struct avl_s *left;
    struct avl_s *right;
} avl_t;

typedef enum
{
    None,
    Pre_Left,
    Pre_Right,
    Cen_Left,
    Cen_Right,
    Pos_Left,
    Pos_Right
} walkings_t;

extern unsigned long long avl_comp_find;
extern unsigned long long avl_comp_insert;

void avl_create(avl_t **root);
avl_t *avl_find(avl_t *root, char *key);
avl_t* avl_rot_right(avl_t* node);
avl_t* avl_rot_left(avl_t* node);
avl_t* avl_rot_double_right(avl_t* node);
avl_t* avl_rot_double_left(avl_t* node);
avl_t *avl_insert_int(avl_t *root, word_bias_t key, int *success);
avl_t *avl_insert(avl_t *root, word_bias_t key);
void avl_print(avl_t *root, walkings_t walking);
void avl_print_pre_left(avl_t *root, int level);
void avl_print_pre_right(avl_t *root, int level);
void avl_print_cen_left(avl_t *root, int level);
void avl_print_cen_right(avl_t *root, int level);
void avl_print_pos_left(avl_t *root, int level);
void avl_print_pos_right(avl_t *root, int level);
int avl_count_nodes(avl_t *root);
avl_t *avl_destroy(avl_t *root);

#endif // AVL_H
