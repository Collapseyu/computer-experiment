//
//  avltree.c
//  AVL
//
//  Created by 俞益聪 on 2019/10/19.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

#define HEIGHT(node) ((node==NULL) ? 0 :(((avlnode *)(node))->height))
#define MAX(a,b) ((a)>(b)?(a):(b))
extern struct global global_stats;
void* bupt_malloc(size_t size){
    if (size <= 0) {
        return NULL;
    }
    global_stats.mem += size;
    return malloc(size);
}
int byte_cmp(char a, char b)
{
    global_stats.cmpnum++;
    return a-b;
}
int str_cmp(char* a,char *b) //return 1 if same
{
    char *ptr1;
    char *ptr2;
    ptr1=a;
    ptr2=b;
    while(*ptr1!='\0'&&*ptr2!='\0')
    {
        if(byte_cmp(*ptr1, *ptr2)!=0)
            break;
        ptr1++;
        ptr2++;
    }
    if(*ptr1!='\0' || *ptr2!='\0')
        return 0;
    else
        return 1;
}
int str_Sizecmp(char* a,char* b)
//return 1 if a>b 0 if a==b -1 if a<b
{
    char *ptr1;
    char *ptr2;
    ptr1=a;
    ptr2=b;
    while(*ptr1!='\0'&&*ptr2!='\0')
     {
         if(byte_cmp(*ptr1, *ptr2)>0)
             return 1;
         if(byte_cmp(*ptr1, *ptr2)<0)
             return -1;
         ptr1++;
         ptr2++;
     }
    if(*ptr1!='\0')
        return 1;
    if(*ptr2!='\0')
        return -1;
    return 0;
}
int getNode_height(avlnode *node)
{
    return HEIGHT(node);
}

avlnode *create_node(char* key,avlnode *left,avlnode *right)
{
    avlnode *node=(avlnode *)bupt_malloc(sizeof(avlnode));
    if(node==NULL)
    {
        printf("创建结点失败");
        return NULL;
    }
//    node->key=key;
    int ptrIn=0;
    while(key[ptrIn]!='\0')
    {
        node->key[ptrIn]=key[ptrIn];
        ptrIn++;
    }
    key[ptrIn]='\0';
    node->left=left;
    node->right=right;
    node->height=0;

    return node;
}

avlnode *  maximun_node(avltree tree)
{
    if(tree==NULL)
        return NULL;
    while(tree->right)
        tree=tree->right;
    return tree;
}

avlnode *minimun_node(avltree tree)
{
    if(tree==NULL)
        return NULL;
    while(tree->left)
        tree=tree->left;

    return tree;
}

void pre_order_avltree(avltree tree)
{
    if(tree)
    {
        printf("%s    ",tree->key);
        pre_order_avltree(tree->left);
        pre_order_avltree(tree->right);
    }
}

void in_order_avltree(avltree tree)
{
    if(tree)
    {
        in_order_avltree(tree->left);
        printf("%s    ",tree->key);
        in_order_avltree(tree->right);

    }
}

void post_order_avltree(avltree tree)
{
    if(tree)
    {
        post_order_avltree(tree->left);
        post_order_avltree(tree->right);
        printf("%s    ",tree->key);

    }
}
static avltree left_left_rotation(avltree tree)
{
    avlnode *k2=tree->left;
    tree->left=k2->right;
    k2->right=tree;
    tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;
    k2->height=MAX(getNode_height(k2->left),getNode_height(k2->right))+1;
    return k2;
}

static avltree right_right_rotation(avltree tree)
{
    avlnode *k3=tree->right;
    tree->right=k3->left;
    k3->left=tree;
    tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;
    k3->height=MAX(getNode_height(k3->left),getNode_height(k3->right))+1;
    return k3;
}

static avltree left_right_rotation(avltree tree)
{
    tree->left=right_right_rotation(tree->left);
    tree=left_left_rotation(tree);
    return tree;
}
static avltree right_left_rotation(avltree tree)
{
    tree->right=left_left_rotation(tree->right);
    tree=right_right_rotation(tree);
    return tree;
}

avltree  avltree_insertNode(avltree tree,char* key)
{   int flag;
    if(tree==NULL)
    {
        avlnode *node=create_node(key,NULL,NULL);

        tree=node;

    }
    else
    {
    flag=str_Sizecmp(key,tree->key);
    if(flag==-1)
    {
        tree->left=avltree_insertNode(tree->left,key);
        if(HEIGHT(tree->left)-HEIGHT(tree->right)==2)
        {
            int flag1;
            flag1=str_Sizecmp(key, tree->left->key);
            if(flag1==-1)
            {
                
                tree= left_left_rotation(tree);

            }
            else
            {
                
                tree=left_right_rotation(tree);
            }
        }
    }
    else if(flag==1)
    {
        tree->right=avltree_insertNode(tree->right,key);
        if(getNode_height(tree->right)-getNode_height(tree->left)==2)
        {
            int flag1;
            flag1=str_Sizecmp(key, tree->right->key);
            if(flag1==1)
            {
                tree= right_right_rotation(tree);
            }
            else
            {
                
                tree=right_left_rotation(tree);
            }
        }
    }
    else
    {
//printf("不允许插入相同值结点");

    }
    }

    tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;

    return tree;
}

void print_avltree(avltree tree, char* key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)
            printf("%s is root\n", tree->key);
        else
            printf("%s is %s's %6s child\n", tree->key, key, direction==1?"right" : "left");

        print_avltree(tree->left, tree->key, -1);
        print_avltree(tree->right,tree->key,  1);
    }
}

avlnode *search_node(avltree tree,char* key)
{   int flag;
    if(tree==NULL)
    {
        return tree;
    }
    flag=str_Sizecmp(key,tree->key);
    if (flag==0)
    {
        return tree;
    }
    else if(flag==-1)
    {
        return search_node(tree->left,key);
    }
    else
    {
        return search_node(tree->right,key);
    }
}
avltree  avltree_deleNode(avltree tree,char* key)
{
    int flag;
    avlnode *node =search_node(tree,key);
    if(tree==NULL||node==NULL)
    {
        return tree;
    }
    flag=str_Sizecmp(key,tree->key);
    if(flag==-1)
    {
        tree->left= avltree_deleNode(tree->left,key);
        
        if(getNode_height(tree->right)-getNode_height(tree->left)==2)
        {   int flag1;
            flag1=str_Sizecmp(key, tree->right->key);
            if(flag1==-1)
            {
                tree=right_left_rotation(tree);
            }
            else
            {
                tree=right_right_rotation(tree);
            }
        }
    }
    else if(flag==1)
    {
        tree->right= avltree_deleNode(tree->right,key);
        if(getNode_height(tree->left)-getNode_height(tree->right)==2)
        {
            int flag1;
            flag1=str_Sizecmp(key, tree->left->key);
            if(flag1==-1)
            {
                tree=left_left_rotation(tree);
            }
            else
            {
                tree=left_right_rotation(tree);
            }

        }
    }
    else
    {
        
        if(tree->left&&tree->right)
        {
            avlnode *min_node=minimun_node(tree->right);
            int ptrIn=0;
            while(min_node->key[ptrIn]!='\0')
            {
                tree->key[ptrIn]=min_node->key[ptrIn];
                ptrIn+=1;
            }
            tree->key[ptrIn]='\0';
//            tree->key=min_node->key;
            tree->right= avltree_deleNode(tree->right,min_node->key);

        }
        else
        {
            tree=tree->left?tree->left:tree->right;
        }
    }
    if(tree)
        tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;
    return tree;
}



