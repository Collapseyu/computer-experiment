//
//  4BinaryRad.c
//  4-binaryRadix
//
//  Created by 俞益聪 on 2019/10/24.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include "4BinaryRad.h"
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
    for(int i=0;i<4;i++)
    {
        fisrtNode->Lchild[i]=NULL;
    }
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
    else
    {
        if(key[ptr]==0&&key[ptr+1]==0)
        {   if(T->Lchild[0]==NULL)
            {
                RadixNode dur=createNode();
                T->Lchild[0]=dur;
            }
                insert(key, T->Lchild[0], ptr+2);
                
        }
        else if(key[ptr]==0&&key[ptr+1]==1)
        {
            if(T->Lchild[1]==NULL)
            {
                RadixNode dur=createNode();
                T->Lchild[1]=dur;
            }
            insert(key, T->Lchild[1], ptr+2);
        }
        else if(key[ptr]==1&&key[ptr+1]==0)
        {   if(T->Lchild[2]==NULL)
            {
                RadixNode dur=createNode();
                T->Lchild[2]=dur;
            }
            insert(key, T->Lchild[2], ptr+2);
        }
        else if(key[ptr]==1&&key[ptr+1]==1)
        {   if(T->Lchild[3]==NULL)
            {
                RadixNode dur=createNode();
                T->Lchild[3]=dur;
            }
            insert(key, T->Lchild[3], ptr+2);
        }
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
       if(key[ptr]==0&&key[ptr+1]==0)
       {
           if(T->Lchild[0]==NULL)
           return 0;
           else
           return search(key, T->Lchild[0], ptr+2);
       }
       else if(key[ptr]==0&&key[ptr+1]==1)
       {
          if(T->Lchild[1]==NULL)
              return 0;
           else
          return search(key, T->Lchild[1], ptr+2);
       }
       else if(key[ptr]==1&&key[ptr+1]==0)
       {
           if(T->Lchild[2]==NULL)
               return 0;
           else
           return search(key, T->Lchild[2], ptr+2);
       }
       else if(key[ptr]==1&&key[ptr+1]==1)
       {   if(T->Lchild[3]==NULL)
           return 0;
           else
           return search(key, T->Lchild[3], ptr+2);
       }
    }
    return 0;
}
