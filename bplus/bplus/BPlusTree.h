//
//  BPlusTree.h
//  bplus
//
//  Created by 俞益聪 on 2019/10/23.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#ifndef BPlusTree_h
#define BPlusTree_h

#include <stdio.h>
#define M 4
#define LIMIT_M_2 (M % 2 ? (M + 1)/2 : M/2)
typedef struct BPlusNode *BPlusTree,*Position;

struct global{
    unsigned long long mem;
    unsigned long long cmpnum;
};

struct BPlusNode{
    int keyNum;
    char Key[M+1][100];
    BPlusTree Children[M+1];
    BPlusTree Next;
};


extern BPlusTree Initialize(void);
/* 插入 */
extern BPlusTree Insert(BPlusTree T,char* Key);
/* 删除 */
extern BPlusTree Remove(BPlusTree T,char* Key);
/* 销毁 */
extern BPlusTree Destroy(BPlusTree T);
/* 遍历节点 */
extern void Travel(BPlusTree T);
/* 遍历树叶节点的数据 */
extern void TravelData(BPlusTree T);

extern int search(BPlusTree T,char* Key,int flag_res);

#endif /* BPlusTree_h */
