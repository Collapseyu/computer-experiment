//
//  BPlusTree.c
//  bplus
//
//  Created by 俞益聪 on 2019/10/23.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include "BPlusTree.h"
#include <stdlib.h>
extern struct global global_stats;
char Unavailable='\0';
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
static BPlusTree MallocNewNode(){
    BPlusTree NewNode;
    int i;
    NewNode = bupt_malloc(sizeof(struct BPlusNode));
    if (NewNode == NULL)
        exit(EXIT_FAILURE);
    
    
    i = 0;
    while (i < M + 1){
        NewNode->Key[i][0] = Unavailable;
        NewNode->Children[i] = NULL;
        i++;
    }
    NewNode->Next = NULL;
    NewNode->keyNum = 0;
    
    return NewNode;
}
extern BPlusTree Initialize(){
    
    BPlusTree T;
    if (M < (3)){
        printf("M最小等于3！");
        exit(EXIT_FAILURE);
        
    }
    /* 根结点 */
    T = MallocNewNode();
    
    return T;
}
static Position FindMostLeft(Position P){
    Position Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[0] != NULL) {
        Tmp = Tmp->Children[0];
    }
    return Tmp;
}
 
static Position FindMostRight(Position P){
    Position Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[Tmp->keyNum - 1] != NULL) {
        Tmp = Tmp->Children[Tmp->keyNum - 1];
    }
    return Tmp;
}

/* 寻找一个兄弟节点，其存储的关键字未满，否则返回NULL */
static Position FindSibling(Position Parent,int i){
    Position Sibling;
    int Limit;
    
    Limit = M;
    
    Sibling = NULL;
    if (i == 0){
        if (Parent->Children[1]->keyNum < Limit)
            Sibling = Parent->Children[1];
    }
    else if (Parent->Children[i - 1]->keyNum < Limit)
        Sibling = Parent->Children[i - 1];
    else if (i + 1 < Parent->keyNum && Parent->Children[i + 1]->keyNum < Limit){
        Sibling = Parent->Children[i + 1];
    }
    
    return Sibling;
}
 
/* 查找兄弟节点，其关键字数大于M/2 ;没有返回NULL*/
static Position FindSiblingKeyNum_M_2(Position Parent,int i,int *j){
    int Limit;
    Position Sibling;
    Sibling = NULL;
    
    Limit = LIMIT_M_2;
    
    if (i == 0){
        if (Parent->Children[1]->keyNum > Limit){
            Sibling = Parent->Children[1];
            *j = 1;
        }
    }
    else{
        if (Parent->Children[i - 1]->keyNum > Limit){
            Sibling = Parent->Children[i - 1];
            *j = i - 1;
        }
        else if (i + 1 < Parent->keyNum && Parent->Children[i + 1]->keyNum > Limit){
            Sibling = Parent->Children[i + 1];
            *j = i + 1;
        }
        
    }
    
    return Sibling;
}


/* 当要对X插入Key的时候，i是X在Parent的位置，j是Key要插入的位置
   当要对Parent插入X节点的时候，i是要插入的位置，Key和j的值没有用
 */
static Position InsertElement(int isKey, Position Parent,Position X,char* Key,int i,int j){
    
    int k;
    if (isKey){
        /* 插入key */
        k = X->keyNum - 1;
        while (k >= j){
            int ptrIn=0;
            while(X->Key[k][ptrIn]!='\0')
            {
                X->Key[k+1][ptrIn]=X->Key[k][ptrIn];
                ptrIn++;
            }
            X->Key[k+1][ptrIn]='\0';
            k--;
            
            //X->Key[k + 1] = X->Key[k];k--;
        }
        
//        X->Key[j] = Key;
        int ptrIn=0;
        while(Key[ptrIn]!='\0')
        {
            X->Key[j][ptrIn]=Key[ptrIn];
            ptrIn++;
        }
        X->Key[j][ptrIn]='\0';
        
        if (Parent != NULL)
        {
            int ptrIn=0;
            while(X->Key[0][ptrIn]!='\0')
            {
                Parent->Key[i][ptrIn]=X->Key[0][ptrIn];
                ptrIn++;
            }
            Parent->Key[i][ptrIn]='\0';
            
        }
//            Parent->Key[i] = X->Key[0];
        
        X->keyNum++;
        
    }else{
        /* 插入节点 */
        
        /* 对树叶节点进行连接 */
        if (X->Children[0] == NULL){
            if (i > 0)
                Parent->Children[i - 1]->Next = X;
            X->Next = Parent->Children[i];
        }
        
        k = Parent->keyNum - 1;
        while (k >= i){
            Parent->Children[k + 1] = Parent->Children[k];
            int ptrIn=0;
            while(Parent->Key[k][ptrIn]!='\0')
            {
        Parent->Key[k+1][ptrIn]=Parent->Key[k][ptrIn];
                ptrIn++;
            }
            Parent->Key[k+1][ptrIn]='\0';
//            Parent->Key[k + 1] = Parent->Key[k];
            k--;
        }
        int ptrIn=0;
            while(X->Key[0][ptrIn]!='\0')
            {
        Parent->Key[i][ptrIn]=X->Key[0][ptrIn];
                ptrIn++;
            }
            Parent->Key[i][ptrIn]='\0';
//        Parent->Key[i] = X->Key[0];
        Parent->Children[i] = X;
        
        Parent->keyNum++;
        
    }
    return X;
}
 
 
static Position RemoveElement(int isKey, Position Parent,Position X,int i,int j){
    
    int k,Limit;
    
    if (isKey){
        Limit = X->keyNum;
        /* 删除key */
        k = j + 1;
        while (k < Limit){
            int ptrIn=0;
                while(X->Key[k][ptrIn]!='\0')
                {
            X->Key[k-1][ptrIn]=X->Key[k][ptrIn];
                    ptrIn++;
                }
                X->Key[k-1][ptrIn]='\0';
//            X->Key[k - 1] = X->Key[k];
            
            k++;
        }
        
        X->Key[X->keyNum - 1][0] = Unavailable;
        
        int ptrIn=0;
            while(X->Key[0][ptrIn]!='\0')
            {
        Parent->Key[i][ptrIn]=X->Key[0][ptrIn];
                ptrIn++;
            }
            Parent->Key[i][ptrIn]='\0';
//        Parent->Key[i] = X->Key[0];
        
        X->keyNum--;
    }else{
        /* 删除节点 */
        
        /* 修改树叶节点的链接 */
        if (X->Children[0] == NULL && i > 0){
            Parent->Children[i - 1]->Next = Parent->Children[i + 1];
        }
        Limit = Parent->keyNum;
        k = i + 1;
        while (k < Limit){
            Parent->Children[k - 1] = Parent->Children[k];
            int ptrIn=0;
                while(Parent->Key[k][ptrIn]!='\0')
                {
            Parent->Key[k-1][ptrIn]=Parent->Key[k][ptrIn];
                    ptrIn++;
                }
                Parent->Key[k-1][ptrIn]='\0';
//            Parent->Key[k - 1] = Parent->Key[k];
            k++;
        }
        
        Parent->Children[Parent->keyNum - 1] = NULL;
        Parent->Key[Parent->keyNum - 1][0] = Unavailable;
        
        Parent->keyNum--;
        
    }
    return X;
}

/* Src和Dst是两个相邻的节点，i是Src在Parent中的位置；
 将Src的元素移动到Dst中 ,n是移动元素的个数*/
static Position MoveElement(Position Src,Position Dst,Position Parent,int i,int n){
    char TmpKey[100];
    Position Child;
    int j,SrcInFront;
    
    SrcInFront = 0;
    int sizeFlag=0;
    sizeFlag=str_Sizecmp(Src->Key[0], Dst->Key[0]);
//    if (Src->Key[0] < Dst->Key[0])
    if (sizeFlag==-1)
        SrcInFront = 1;
    
    j = 0;
    /* 节点Src在Dst前面 */
    if (SrcInFront){
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[Src->keyNum - 1];
                RemoveElement(0, Src, Child, Src->keyNum - 1, Unavailable);
                InsertElement(0, Dst, Child, &Unavailable, 0, Unavailable);
                j++;
            }
        }else{
            while (j < n) {
                int ptrIn=0;
                while(Src->Key[Src->keyNum-1][ptrIn]!='\0')
                {
                    TmpKey[ptrIn]=Src->Key[Src->keyNum-1][ptrIn];
                    ptrIn+=1;
                }
                TmpKey[ptrIn]='\0';
//                TmpKey = Src->Key[Src->keyNum -1];
                RemoveElement(1, Parent, Src, i, Src->keyNum - 1);
                InsertElement(1, Parent, Dst, TmpKey, i + 1, 0);
                j++;
            }
            
        }
        int ptrIn=0;
            while(Dst->Key[0][ptrIn]!='\0')
            {
        Parent->Key[i+1][ptrIn]=Dst->Key[0][ptrIn];
                ptrIn++;
            }
            Parent->Key[i+1][ptrIn]='\0';
//        Parent->Key[i + 1] = Dst->Key[0];
        /* 将树叶节点重新连接 */
        if (Src->keyNum > 0)
            FindMostRight(Src)->Next = FindMostLeft(Dst);
        
    }else{
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[0];
                RemoveElement(0, Src, Child, 0, Unavailable);
                InsertElement(0, Dst, Child, &Unavailable, Dst->keyNum, Unavailable);
                j++;
            }
            
        }else{
            while (j < n) {
                int ptrIn=0;
                while(Src->Key[0][ptrIn]!='\0')
                {
                    TmpKey[ptrIn]=Src->Key[0][ptrIn];
                    ptrIn+=1;
                }
                TmpKey[ptrIn]='\0';
//                TmpKey = Src->Key[0];
                RemoveElement(1, Parent, Src, i, 0);
                InsertElement(1, Parent, Dst, TmpKey, i - 1, Dst->keyNum);
                j++;
            }
            
        }
        int ptrIn=0;
            while(Src->Key[0][ptrIn]!='\0')
            {
        Parent->Key[i][ptrIn]=Src->Key[0][ptrIn];
                ptrIn++;
            }
            Parent->Key[i][ptrIn]='\0';
//        Parent->Key[i] = Src->Key[0];
        if (Src->keyNum > 0)
            FindMostRight(Dst)->Next = FindMostLeft(Src);
        
    }
    
    return Parent;
}
 
static BPlusTree SplitNode(Position Parent,Position X,int i){
    int j,k,Limit;
    Position NewNode;
    
    NewNode = MallocNewNode();
    
    k = 0;
    j = X->keyNum / 2;
    Limit = X->keyNum;
    while (j < Limit){
        if (X->Children[0] != NULL){
            NewNode->Children[k] = X->Children[j];
            X->Children[j] = NULL;
        }
        int ptrIn=0;
            while(X->Key[j][ptrIn]!='\0')
            {
        NewNode->Key[k][ptrIn]=X->Key[j][ptrIn];
                ptrIn++;
            }
            NewNode->Key[k][ptrIn]='\0';
//        NewNode->Key[k] = X->Key[j];
        X->Key[j][0] = Unavailable;
        NewNode->keyNum++;X->keyNum--;
        j++;k++;
    }
    
    if (Parent != NULL)
        InsertElement(0, Parent, NewNode, &Unavailable, i + 1, Unavailable);
    else{
        /* 如果是X是根，那么创建新的根并返回 */
        Parent = MallocNewNode();
        InsertElement(0, Parent, X, &Unavailable, 0, Unavailable);
        InsertElement(0, Parent, NewNode, &Unavailable, 1, Unavailable);
        
        return Parent;
    }
    
    return X;
}
 
/* 合并节点,X少于M/2关键字，S有大于或等于M/2个关键字*/
static Position MergeNode(Position Parent, Position X,Position S,int i){
    int Limit;
    
    /* S的关键字数目大于M/2 */
    if (S->keyNum > LIMIT_M_2){
        /* 从S中移动一个元素到X中 */
        MoveElement(S, X, Parent, i,1);
    }else{
        /* 将X全部元素移动到S中，并把X删除 */
        Limit = X->keyNum;
        MoveElement(X,S, Parent, i,Limit);
        RemoveElement(0, Parent, X, i, Unavailable);
        
        free(X);
        X = NULL;
    }
    
    return Parent;
}

int search(BPlusTree T,char* Key,int flag_res)
{
    int j;
    
    j=0;
    int flag=0;
    flag=str_Sizecmp(Key, T->Key[j]);
    if(flag==0) flag_res=1;
    while(j<T->keyNum && flag==1)
    {
        j++;
        flag=str_Sizecmp(Key, T->Key[j]);
         if(flag==0) flag_res=1;
    }
    if (j!=0 && T->Children[0]!=NULL) j--;
    //if(j==T->keyNum) j--;
    if (T->Children[0]==NULL)
        return flag_res;
    else
        return search(T->Children[j], Key,flag_res);
}

static BPlusTree RecursiveInsert(BPlusTree T,char* Key,int i,BPlusTree Parent){
    int j,Limit;
    Position Sibling;
    
    /* 查找分支 */
    j = 0;
    int flag=0;
    flag=str_Sizecmp(Key,T->Key[j]);
    while (j < T->keyNum && (flag==0||flag==1))//Key >= T->Key[j])
    {
        /* 重复值不插入 */
        if (flag==0)
            return T;
        j++;
        flag=str_Sizecmp(Key,T->Key[j]);
    }
    if (j != 0 && T->Children[0] != NULL) j--;
    
    /* 树叶 */
    if (T->Children[0] == NULL)
        T = InsertElement(1, Parent, T, Key, i, j);
    /* 内部节点 */
    else
        T->Children[j] = RecursiveInsert(T->Children[j], Key, j, T);
    
    /* 调整节点 */
    
    Limit = M;
    
    if (T->keyNum > Limit){
        /* 根 */
        if (Parent == NULL){
            /* 分裂节点 */
            T = SplitNode(Parent, T, i);
        }
        else{
            Sibling = FindSibling(Parent, i);
            if (Sibling != NULL){
                /* 将T的一个元素（Key或者Child）移动的Sibing中 */
                MoveElement(T, Sibling, Parent, i, 1);
            }else{
                /* 分裂节点 */
                T = SplitNode(Parent, T, i);
            }
        }
        
    }
    
    if (Parent != NULL)
    {
            int ptrIn=0;
            while(T->Key[0][ptrIn]!='\0')
            {
                Parent->Key[i][ptrIn]=T->Key[0][ptrIn];
                ptrIn++;
            }
            Parent->Key[i][ptrIn]='\0';
//        Parent->Key[i] = T->Key[0];
    }
    
    
    return T;
}
 
/* 插入 */
extern BPlusTree Insert(BPlusTree T,char* Key){
    return RecursiveInsert(T, Key, 0, NULL);
}
 
static BPlusTree RecursiveRemove(BPlusTree T,char* Key,int i,BPlusTree Parent){
    
    int j,NeedAdjust;
    Position Sibling,Tmp;
    
    Sibling = NULL;
    
    /* 查找分支 */
    j = 0;
    int sizeFlag=0;
    sizeFlag=str_Sizecmp(Key, T->Key[j]);
    while (j < T->keyNum && (sizeFlag==0||sizeFlag==1)){//Key >= T->Key[j]
        if (sizeFlag==0)
            break;
        j++;
        sizeFlag=str_Sizecmp(Key, T->Key[j]);
    }
    
    if (T->Children[0] == NULL){
        /* 没找到 */
        if (sizeFlag!=0 || j == T->keyNum)//Key != T->Key[j]
            return T;
    }else
        if (j == T->keyNum || sizeFlag==-1) j--;//Key < T->Key[j]
    
    
    
    /* 树叶 */
    if (T->Children[0] == NULL){
        T = RemoveElement(1, Parent, T, i, j);
    }else{
        T->Children[j] = RecursiveRemove(T->Children[j], Key, j, T);
    }
    
    NeedAdjust = 0;
    /* 树的根或者是一片树叶，或者其儿子数在2到M之间 */
    if (Parent == NULL && T->Children[0] != NULL && T->keyNum < 2)
        NeedAdjust = 1;
    /* 除根外，所有非树叶节点的儿子数在[M/2]到M之间。(符号[]表示向上取整) */
    else if (Parent != NULL && T->Children[0] != NULL && T->keyNum < LIMIT_M_2)
        NeedAdjust = 1;
    /* （非根）树叶中关键字的个数也在[M/2]和M之间 */
    else if (Parent != NULL && T->Children[0] == NULL && T->keyNum < LIMIT_M_2)
        NeedAdjust = 1;
    
    /* 调整节点 */
    if (NeedAdjust){
        /* 根 */
        if (Parent == NULL){
            if(T->Children[0] != NULL && T->keyNum < 2){
                Tmp = T;
                T = T->Children[0];
                free(Tmp);
                return T;
            }
            
        }else{
            /* 查找兄弟节点，其关键字数目大于M/2 */
            Sibling = FindSiblingKeyNum_M_2(Parent, i,&j);
            if (Sibling != NULL){
                MoveElement(Sibling, T, Parent, j, 1);
            }else{
                if (i == 0)
                    Sibling = Parent->Children[1];
                else
                    Sibling = Parent->Children[i - 1];
                
                Parent = MergeNode(Parent, T, Sibling, i);
                T = Parent->Children[i];
            }
        }
        
    }
 
    
    return T;
}
 
/* 删除 */
extern BPlusTree Remove(BPlusTree T,char* Key){
    return RecursiveRemove(T, Key, 0, NULL);
}
 
/* 销毁 */
extern BPlusTree Destroy(BPlusTree T){
    int i,j;
    if (T != NULL){
        i = 0;
        while (i < T->keyNum + 1){
            Destroy(T->Children[i]);i++;
        }
        
        printf("Destroy:(");
        j = 0;
        while (j < T->keyNum)/*  T->Key[i] != Unavailable*/
            printf("%s:",T->Key[j++]);
        printf(") ");
        free(T);
        T = NULL;
    }
    
    return T;
}
 
static void RecursiveTravel(BPlusTree T,int Level){
    int i;
    if (T != NULL){
        printf("  ");
        printf("[Level:%d]-->",Level);
        printf("(");
        i = 0;
        while (i < T->keyNum)/*  T->Key[i] != Unavailable*/
            printf("%s:",T->Key[i++]);
        printf(")");
        
        Level++;
        
        i = 0;
        while (i <= T->keyNum) {
            RecursiveTravel(T->Children[i], Level);
            i++;
        }
        
        
    }
}
 
/* 遍历 */
extern void Travel(BPlusTree T){
    RecursiveTravel(T, 0);
    printf("\n");
}
 
/* 遍历树叶节点的数据 */
extern void TravelData(BPlusTree T){
    Position Tmp;
    int i;
    if (T == NULL)
        return ;
    printf("All Data:");
    Tmp = T;
    while (Tmp->Children[0] != NULL)
        Tmp = Tmp->Children[0];
    /* 第一片树叶 */
    while (Tmp != NULL){
        i = 0;
        while (i < Tmp->keyNum)
            printf(" %s",Tmp->Key[i++]);
        Tmp = Tmp->Next;
    }
}

