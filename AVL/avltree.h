//
//  avltree.h
//  AVL
//
//  Created by 俞益聪 on 2019/10/19.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#ifndef avltree_h
#define avltree_h

typedef int elementType;
typedef struct node
{
//    elementType key;
    char key[100];
    struct node *left;
    struct node *right;
    int height;//当前结点深度
} avlnode,*avltree;
struct global{
    unsigned long long mem;
    unsigned long long cmpnum;
};
void* bupt_malloc(size_t size);
int byte_cmp(char a,char b);
int str_cmp(char*a,char*b);
int getNode_height(avlnode *node);//获取当前结点的深度
int str_Sizecmp(char* a,char* b);
avlnode *create_node(char* key,avlnode *left,avlnode *right);//创建结点

avlnode *  maximun_node(avltree tree);//求树中最大结点

avlnode *minimun_node(avltree tree);//求树中最小结点

avltree  avltree_insertNode(avltree tree,char* key);//向树中插入结点

avltree  avltree_deleNode(avltree tree,char* key);//删除结点

void pre_order_avltree(avltree tree);//前序遍历

void in_order_avltree(avltree tree);//中序遍历

void post_order_avltree(avltree tree);//后序遍历

void print_avltree(avltree tree, char* key, int direction);//打印树的信息

avlnode *search_node(avltree tree,char* key);//根据key 的值搜索结点

#endif // AVLTREE_H_INCLUDED#endif /* avltree_h */
