#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long avl_comp_find = 0;
unsigned long long avl_comp_insert = 0;

void avl_create(avl_t **root)
{
    *root = NULL;
}

avl_t *avl_find(avl_t *root, char *key)
{
    avl_comp_find++;
    if(root)
    {
        avl_comp_find++;
        if(!strncmp(root->info.word, key, MAX_WORD + 1))
            return root;
        else if(strncmp(root->info.word, key, MAX_WORD + 1) > 0)
        {
            avl_comp_find++;
            return avl_find(root->left, key);
        }
        else
        {
            avl_comp_find++;
            return avl_find(root->right, key);
        }
    }
    else
        return NULL;
}

avl_t* avl_rot_right(avl_t* node)
{
    avl_t *son_left;
    son_left = node->left;
    node->left = son_left->right;
    son_left->right = node;
    node->bf = 0;
    node = son_left;
    return node;
}
avl_t* avl_rot_left(avl_t* node)
{
    avl_t *son_left;
    son_left = node->right;
    node->right = son_left->left;
    son_left->left = node;
    node->bf = 0;
    node = son_left;
    return node;
}
avl_t* avl_rot_double_right(avl_t* node)
{
    avl_t *son_left, *grandson_right;
    son_left = node->left;
    grandson_right = son_left->right;
    son_left->right = grandson_right->left;
    grandson_right->left = son_left;
    node->left = grandson_right->right;
    grandson_right->right = node;

    avl_comp_insert++;
    if(grandson_right->bf == 1)
        node->bf = -1;
    else
        node->bf = 0;
    
    avl_comp_insert++;
    if(grandson_right->bf == -1)
        son_left->bf = 1;
    else
        son_left->bf = 0;
    node = grandson_right;
    return node;
}
avl_t* avl_rot_double_left(avl_t* node)
{
    avl_t *son_left, *grandson_left;
    son_left = node->right;
    grandson_left = son_left->left;
    son_left->left = grandson_left->right;
    grandson_left->right = son_left;
    node->right = grandson_left->left;
    grandson_left->left = node;

    avl_comp_insert++;
    if (grandson_left->bf == -1)
        node->bf = 1;
    else
        node->bf = 0;

    avl_comp_insert++;
    if (grandson_left->bf == 1)
        son_left->bf = -1;
    else
        son_left->bf = 0;
    node = grandson_left;
    return node;
}

avl_t* unbalanced_left(avl_t *root, int *success)
{
    avl_t *son_left;
    son_left = root->left;

    avl_comp_insert++;
    if (son_left->bf == 1)
        root = avl_rot_right(root);
    else
        root = avl_rot_double_right(root);
    root->bf = 0;
    *success = 0;
    return root;
}
avl_t* unbalanced_right(avl_t *root, int *success)
{
    avl_t *son_left;
    son_left = root->right;

    avl_comp_insert++;
    if (son_left->bf == -1)
        root = avl_rot_left(root);
    else
        root = avl_rot_double_left(root);
    root->bf = 0;
    *success = 0;
    return root;
}
avl_t *avl_insert_int(avl_t *root, word_bias_t key, int *success)
{
    avl_comp_insert++;
    if(!root)
    {
        root = (avl_t*) malloc(sizeof(avl_t));
        root->info = key;
        root->left = NULL;
        root->right = NULL;
        root->bf = 0;
        *success = 1;
    }
    else if(strncmp(root->info.word, key.word, MAX_WORD + 1) > 0)
    {
        avl_comp_insert += 2;
        root->left = avl_insert_int(root->left, key, success);
        if(*success)
        {
            avl_comp_insert++;
            switch(root->bf)
            {
                case -1:
                    root->bf = 0;
                    *success = 0;
                    break;
                case 0:
                    root->bf = 1;
                    break;
                case 1:
                    root = unbalanced_left(root, success);
                    break;
            }
        }
    }
    else
    {
        avl_comp_insert += 2;
        root->right = avl_insert_int(root->right, key, success);
        if(*success)
        {
            avl_comp_insert++;
            switch(root->bf)
            {
                case 1:
                    root->bf = 0;
                    *success = 0;
                    break;
                case 0:
                    root->bf = -1;
                    break;
                case -1:
                    root = unbalanced_right(root, success);
                    break;
            }
        }
    }
    return root;
}

avl_t *avl_insert(avl_t *root, word_bias_t key)
{
    int success = 1;
    root = avl_insert_int(root, key, &success);
    return root;
}

int avl_count_nodes(avl_t *root)
{
    int node_count = 0;

    if(root)
    {
        node_count++;
        node_count += avl_count_nodes(root->left);
        node_count += avl_count_nodes(root->right);
    }

    return node_count;
}

void avl_print(avl_t *root, walkings_t walking)
{
    int level = 1;
    int node_count = avl_count_nodes(root);
    if(node_count == 1)
        printf("\nThe tree has only one node:\n\n");
    else
        printf("\nThe tree has %d nodes:\n\n", node_count);
    switch(walking)
    {
        case Pre_Left:
            avl_print_pre_left(root, level);
            break;

        case Pre_Right:
            avl_print_pre_right(root, level);
            break;

        case Cen_Left:
            avl_print_cen_left(root, level);
            break;

        case Cen_Right:
            avl_print_cen_right(root, level);
            break;

        case Pos_Left:
            avl_print_pos_left(root, level);
            break;

        case Pos_Right:
            avl_print_pos_right(root, level);
            break;

        default:
            break;
    }
}

void avl_print_pre_left(avl_t *root, int level)
{
    if(root && level)
    {
        for(int i = 0; i < level; i++)
            printf("=");
        printf(" (%f) %s\n", root->info.bias, root->info.word);
        avl_print_pre_left(root->left, level + 1);
        avl_print_pre_left(root->right, level + 1);
    }
}

void avl_print_pre_right(avl_t *root, int level)
{
    if(root && level)
    {
        for(int i = 0; i < level; i++)
            printf("=");
        printf(" (%f) %s\n", root->info.bias, root->info.word);
        avl_print_pre_right(root->right, level + 1);
        avl_print_pre_right(root->left, level + 1);
    }
}
void avl_print_cen_left(avl_t *root, int level)
{
    if(root && level)
    {
        avl_print_cen_left(root->left, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf(" (%f) %s\n", root->info.bias, root->info.word);
        avl_print_cen_left(root->right, level + 1);
    }
}
void avl_print_cen_right(avl_t *root, int level)
{
    if(root && level)
    {
        avl_print_cen_right(root->right, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf(" (%f) %s\n", root->info.bias, root->info.word);
        avl_print_cen_right(root->left, level + 1);
    }
}
void avl_print_pos_left(avl_t *root, int level)
{
    if(root && level)
    {
        avl_print_pos_left(root->left, level + 1);
        avl_print_pos_left(root->right, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf(" (%f) %s\n", root->info.bias, root->info.word);
    }
}
void avl_print_pos_right(avl_t *root, int level)
{
    if(root && level)
    {
        avl_print_pos_right(root->right, level + 1);
        avl_print_pos_right(root->left, level + 1);
        for(int i = 0; i < level; i++)
            printf("=");
        printf(" (%f) %s\n", root->info.bias, root->info.word);
    }
}

avl_t *avl_destroy(avl_t *root)
{
    if(root)
    {
        root->left = avl_destroy(root->left);
        root->right = avl_destroy(root->right);
        free(root);
    }
    else
        root = NULL;

    return root;
}
