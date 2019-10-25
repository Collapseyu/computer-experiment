//
//  binaryRadix.c
//  binaryRadix
//
//  Created by 俞益聪 on 2019/10/24.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include "binaryRadix.h"
#include <stdlib.h>
extern struct global global_stats;
void* bupt_malloc(size_t size){
    if (size <= 0) {
        return NULL;
    }
    global_stats.mem += size;
    return malloc(size);
}
RadixNode createNode(void)
{
    RadixNode fisrtNode;
    fisrtNode=bupt_malloc(sizeof(struct binaryRadix_Tree));
    fisrtNode->Lchild=NULL;
    fisrtNode->Rchild=NULL;
    fisrtNode->existFlag=0;
    return fisrtNode;
}
void char2Binary(char *key,int *res)
{
    int ptrIn=0;
    while(key[ptrIn]!='\0')
    {
        for(int i=7;i>=0;i--)
        {
            int tmp;
            tmp=key[ptrIn]&(1<<i);
            res[7-i+8*ptrIn]=tmp>>i;
        }
        ptrIn++;
    }
    res[8*ptrIn]=-1;
}
void insert(int *key,RadixNode T,int ptr)
{
    if(key[ptr]==-1)
        {
            T->existFlag=1;
            return;
        }
    if(T->Lchild==NULL&&key[ptr]==0)
    {
        RadixNode Ldur=createNode();
//        Ldur->x=0;
        T->Lchild=Ldur;
        insert(key, T->Lchild, ptr+1);
    }
    else if(T->Rchild==NULL&&key[ptr]==1)
    {
            RadixNode Rdur=createNode();
//            Rdur->x=0;
            T->Rchild=Rdur;
            insert(key, T->Rchild, ptr+1);
    }
    else
    {
       if(key[ptr]==0)
           insert(key, T->Lchild, ptr+1);
       else
           insert(key, T->Rchild, ptr+1);
    }
}
int search(int *key,RadixNode T,int ptr)
{   global_stats.cmpnum+=1;
    if(key[ptr]==-1)
    {
        if(T->existFlag==1)
            return 1;
        else
            return 0;
    }
    else
    {
        if(key[ptr]==0)
        {
            if(T->Lchild==NULL)
                return 0;
            else
                return search(key, T->Lchild, ptr+1);
        }
        else
        {
            if(T->Rchild==NULL)
                return 0;
            else
                return search(key, T->Rchild, ptr+1);
        }
    }
}
