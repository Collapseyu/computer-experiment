//
//  main.c
//  bplus
//
//  Created by 俞益聪 on 2019/10/23.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "BPlusTree.h"
struct global global_stats={0,0};
const char *patterns_filename ="./patterns-127w-utf8.txt";
const char *words_filename ="./words-98w.txt";

int main(int argc, const char * argv[]) {
//    BPlusTree T;
//    T=Initialize();
//    char a[10]="hello";
//    char b[10]="hi";
//    char c[10]="bye";
//    char d[10]="thank";
//    char e[10]="yeah";
//    T=Insert(T, a);
//    T=Insert(T, b);
//    T=Insert(T, c);
//    T=Insert(T, d);
//    T=Insert(T, e);
    // insert code here...
    
    printf("Hello, World!\n");
    BPlusTree T;
    T = Initialize();
    clock_t start, finish;
    char durStr[100];
    FILE *f=fopen(patterns_filename,"r");
    start=clock();
    printf("start\n");
    int totalPatterns=0;
    while(~fscanf(f,"%s",durStr))
    {
        //printf("done");
        T=Insert(T, durStr);
        totalPatterns+=1;
    }
    FILE *f1=fopen(words_filename, "r");
    FILE *wf;
    if((wf=fopen("./BPlus_output.txt","wb"))==NULL)
    {
        printf("\nopen file Fail,close!");
        getchar();
        exit(1);
    }
    int count=0;
    int word=0;
    global_stats.cmpnum=0;
    while(~fscanf(f1,"%s",durStr))
//    while(read(f1, durStr))
    {
        if(search(T, durStr, 0)==1)
        {
            count+=1;
            fprintf(wf, "%s yes\n",durStr);
            word+=1;
            continue;
        }
        word+=1;
        fprintf(wf, "%s no\n",durStr);
    }
    printf("totalPattern:%d word:%d goal:%d cmp:%llu mem:%llu\n",totalPatterns,word,count,global_stats.cmpnum,global_stats.mem/1024);
    finish=clock();
    printf("%f",(double)(finish-start)/CLOCKS_PER_SEC);
    printf("%d",search(T, "hi",0));
    return 0;
     
}
