//
//  RadixTree.c
//  radix
//
//  Created by 俞益聪 on 2019/10/23.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include "RadixTree.h"
#include <stdlib.h>
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
void char2binary(char key,char *res)
{
    for(int i=7;i>=0;i--)
    {
        int tmp;
        tmp=key&(1<<i);
        res[7-i]=tmp>>i;
    }
}
RadixNode new_Node(char key)
{
    RadixNode Node;
    Node = bupt_malloc(sizeof(struct radix_tree));
    Node->lib=NULL;
    Node->child=NULL;
    Node->firstNode=0;
    Node->name[0]=key;
    Node->name[1]='0';
    return Node;
}
RadixNode create_tree()
{
    RadixNode firstNode;
    firstNode = bupt_malloc(sizeof(struct radix_tree));
    firstNode->lib=NULL;
    firstNode->child=NULL;
    firstNode->firstNode=1;
    return firstNode;
}

void insert(char* key,RadixNode T,int ptr)
{
    if(T->firstNode==1)
    {
        if(T->child==NULL)
        {
            RadixNode childNew;
            childNew=new_Node(key[ptr]);
            T->child=childNew;
            insert(key, T->child, ptr);
        }
        else
        {
            insert(key, T->child, ptr);
        }
    }
    else
    {
//        global_stats.cmpnum+=1;
        if(key[ptr]==T->name[0])
        {
            if(T->child==NULL)
            {
                if(key[ptr+1]!='\0')
                {
    //                int ptrIn=1;
    //                while(key[ptrIn]!='\0')
    //                {
    //                    T->name[ptrIn]=key[ptrIn];
    //                    ptrIn++;
    //                }
    //                T->name[ptrIn]='\0';
                    RadixNode durNew;
                    durNew=new_Node(key[ptr+1]);
                    T->child=durNew;
                    insert(key, T->child, ptr+1);
                }
                else
                {
                    T->name[1]='\0';
                }
            }
            else
            {
                if(key[ptr+1]=='\0')
                {
                    T->name[1]='\0';
    //                return T;
                }
                else
                {
                    insert(key, T->child, ptr+1);
                }
            }
        
        }
        else if(T->lib!=NULL)
        {
            insert(key, T->lib, ptr);
        }
        else
        {
            RadixNode libDur;
            libDur=new_Node(key[ptr]);
            T->lib=libDur;
            insert(key, T->lib, ptr);
        }
    }
}
int search(char* key,RadixNode T,int ptr)
{   global_stats.cmpnum+=1;
    if(T->name[0]==key[ptr])
    {
        if(key[ptr+1]=='\0')
        {
            if(T->name[1]=='\0')
                return 1;
            else
                return 0;
        }
        else
        {
            if(T->child!=NULL)
                return search(key, T->child, ptr+1);
            else
                return 0;
        }
    }
    else
    {
        if(T->lib==NULL)
            return 0;
        else
        {
            return search(key, T->lib, ptr);
        }
    }
}
