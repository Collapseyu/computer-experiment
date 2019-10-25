//
//  RadixTree.h
//  radix
//
//  Created by 俞益聪 on 2019/10/23.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#ifndef RadixTree_h
#define RadixTree_h
#define m 4
#include <stdio.h>
typedef struct radix_tree *postion,*RadixNode;
struct global{
    unsigned long long mem;
    unsigned long long cmpnum;
};
struct radix_tree{
    char name[2];
    char firstNode;
    struct radix_tree* lib;
    struct radix_tree* child;
};
RadixNode create_tree(void);
RadixNode new_Node(char Key);
void insert(char* key,RadixNode T,int ptr);
int search(char* key,RadixNode T,int ptr);

#endif /* RadixTree_h */
