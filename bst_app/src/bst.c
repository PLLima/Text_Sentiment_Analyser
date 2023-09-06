#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long bst_comp_find = 0;
unsigned long long bst_comp_insert = 0;

void bst_create(bst_t **root)
{
    *root = NULL;
}

bst_t *bst_find(bst_t *root, data_t key)
{
    if(root)
    {
        if(root->info == key)
            return root;
        else if(root->info > key)
            return bst_find(root->left, key);
        else
            return bst_find(root->right, key);
    }
    else
        return NULL;
}

int bst_height(bst_t *root)
{
    int height = 0;
    int height_left, height_right;

    if (root)
    {
        height_left = bst_height(root->left);
        height_right = bst_height(root->right);
        if (height_left > height_right)
            height = 1 + height_left;
        else
            height = 1 + height_right;
    }

    return height;
}

int bst_bf_node(bst_t *root)
{
    return bst_height(root->left) - bst_height(root->right);
}
int bst_bf_int(bst_t *root, int *max_bf)
{
    int bf = 0;

    if(root)
    {
        bst_bf_int(root->left, max_bf);
        bst_bf_int(root->right, max_bf);

        bf = abs(bst_bf_node(root));
        if(*max_bf < bf)
            *max_bf = bf;
    }

    return *max_bf;
}

int bst_bf(bst_t *root)
{
    int max_bf = 0;
    max_bf = bst_bf_int(root, &max_bf);
    return max_bf;
}

bst_t *bst_insert(bst_t *root, data_t key)
{
    if(root)
    {
        if(key < root->info)
            root->left = bst_insert(root->left, key);
        else if(key > root->info)
            root->right = bst_insert(root->right, key);
    }
    else
    {
        root = (bst_t *) malloc(sizeof(bst_t));
        root->info = key;
        root->left = NULL;
        root->right = NULL;
    }

    return root;
}

int bst_count_nodes(bst_t *root)
{
    int node_count = 0;

    if(root)
    {
        node_count++;
        node_count += bst_count_nodes(root->left);
        node_count += bst_count_nodes(root->right);
    }

    return node_count;
}

void bst_print(bst_t *root, walking_t walking)
{
    int level = 1;
    int node_count = bst_count_nodes(root);
    int bf = bst_bf(root);
    if(node_count == 1)
        printf("\nA arvore tem 1 no;\n\n");
    else
        printf("\nA arvore tem %d nos;\n\n", node_count);
    printf("A arvore tem fator de balanceamento %d;\n\n", bf);
    switch(walking)
    {
        case Pre_Left:
            bst_print_pre_left(root, level);
            break;

        case Pre_Right:
            bst_print_pre_right(root, level);
            break;

        case Cen_Left:
            bst_print_cen_left(root, level);
            break;

        case Cen_Right:
            bst_print_cen_right(root, level);
            break;

        case Pos_Left:
            bst_print_pos_left(root, level);
            break;

        case Pos_Right:
            bst_print_pos_right(root, level);
            break;

        default:
            break;
    }
}

void bst_print_pre_left(bst_t *root, int level)
{
    if(root && level)
    {
        for(int i = 0; i < level; i++)
            printf("=");
        printf("%d\n", (int) root->info);
        bst_print_pre_left(root->left, level + 1);
        bst_print_pre_left(root->right, level + 1);
    }
}

void bst_print_pre_right(bst_t *root, int level)
{
    if(root && level)
    {
        for(int i = 0; i < level; i++)
            printf("=");
        printf("%d\n", (int) root->info);
        bst_print_pre_right(root->right, level + 1);
        bst_print_pre_right(root->left, level + 1);
    }
}
void bst_print_cen_left(bst_t *root, int level)
{
    if(root && level)
    {
        bst_print_cen_left(root->left, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf("%d\n", (int) root->info);
        bst_print_cen_left(root->right, level + 1);
    }
}
void bst_print_cen_right(bst_t *root, int level)
{
    if(root && level)
    {
        bst_print_cen_right(root->right, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf("%d\n", (int) root->info);
        bst_print_cen_right(root->left, level + 1);
    }
}
void bst_print_pos_left(bst_t *root, int level)
{
    if(root && level)
    {
        bst_print_pos_left(root->left, level + 1);
        bst_print_pos_left(root->right, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf("%d\n", (int) root->info);
    }
}
void bst_print_pos_right(bst_t *root, int level)
{
    if(root && level)
    {
        bst_print_pos_right(root->right, level + 1);
        bst_print_pos_right(root->left, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf("%d\n", (int) root->info);
    }
}

bst_t *bst_destroy(bst_t *root)
{
    if(root)
    {
        root->left = bst_destroy(root->left);
        root->right = bst_destroy(root->right);
        free(root);
    }
    else
        root = NULL;

    return root;
}
