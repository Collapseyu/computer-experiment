//
//  4BinaryRad.h
//  4-binaryRadix
//
//  Created by 俞益聪 on 2019/10/24.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#ifndef _BinaryRad_h
#define _BinaryRad_h

#include <stdio.h>
struct global{
    unsigned long long mem;
    unsigned long long cmpnum;
    unsigned long long treenodeNum;
};
typedef struct binaryRadix_Tree *RadixNode;
struct binaryRadix_Tree{
//    char x;
    char existFlag;
    struct binaryRadix_Tree* Lchild[4];
//    struct binaryRadix_Tree* Rchild;
};
void char2Binary(char *key,int *res);
RadixNode createNode(void);
void insert(int *key,RadixNode T,int ptr);
int search(int *key,RadixNode T,int ptr);

#endif /* _BinaryRad_h */
