//
//  main.c
//  AVL
//
//  Created by 俞益聪 on 2019/10/19.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "avltree.h"
#define LENGTH(a) ((sizeof(a))/(sizeof(a[0])))
struct global global_stats={0,0,0};
const char *patterns_filename =
"../patterns-127w-utf8.txt";
const char *words_filename =
"../words-98w.txt";

int main(int argc, const char * argv[]) {
    // insert code here...
    avltree tree=NULL;
    clock_t start, finish;
    char durStr[100];
    FILE *f=fopen(patterns_filename,"r");
    start=clock();
    printf("start\n");
    int totalPatterns=0;
    while(~fscanf(f,"%s",durStr))
    {
        tree=avltree_insertNode(tree, durStr);
        totalPatterns+=1;
    }
    FILE *f1=fopen(words_filename, "r");
    FILE *wf;
    if((wf=fopen("./result.txt","wb"))==NULL)
    {
        printf("\nopen file Fail,close!");
        getchar();
        exit(1);
    }
    int count=0;
    int word=0;
    global_stats.cmpnum=0;
    while(~fscanf(f1,"%s",durStr))
    {
        if(search_node(tree, durStr)!=NULL)
        {
            count+=1;
            fprintf(wf, "%s yes\n",durStr);
            word+=1;
            continue;
        }
        word+=1;
        fprintf(wf, "%s no\n",durStr);
    }
    printf("treenode:%llu cmp:%llu mem:%llu word:%d goal:%d\n",global_stats.treenodeNum,global_stats.mem/1024,global_stats.cmpnum/1000,word,count);
    fprintf(wf,"treenode:%llu cmp:%llu mem:%llu word:%d goal:%d\n",global_stats.treenodeNum,global_stats.mem/1024,global_stats.cmpnum/1000,word,count);
    finish=clock();
    printf("%f",(double)(finish-start)/CLOCKS_PER_SEC);
    printf("done");
//    printf("中序遍历：");
//    in_order_avltree(tree);
     
    
}

