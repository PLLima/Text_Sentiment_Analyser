#ifndef AVL_H
#define AVL_H

typedef int data_t;

typedef struct avl_s
{
    data_t info;
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

avl_t *avl_find(avl_t *root, data_t key);

avl_t* avl_rot_right(avl_t* no);
avl_t* avl_rot_left(avl_t* no);
avl_t* avl_rot_dupla_right(avl_t* no);
avl_t* avl_rot_dupla_left(avl_t* no);

avl_t *avl_insert_int(avl_t *root, data_t key, int *success);

avl_t *avl_insert(avl_t *root, data_t key);

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
