//
//  main.c
//  binaryRadix
//
//  Created by 俞益聪 on 2019/10/24.
//  Copyright © 2019 俞益聪. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "binaryRadix.h"
struct global global_stats={0,0,0};
const char *patterns_filename ="../patterns-127w-utf8.txt";
const char *words_filename ="../words-98w.txt";
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
//    char a[10]="hello";
//    char b[10]="hi";
    int dur[801];
//    char2Binary(a, dur);
    RadixNode T;
    T=createNode();
//    insert(dur, T, 0);
//    char2Binary(b, dur);
//    insert(dur, T, 0);
//    int x;
//    char2Binary("hhh", dur);
//    x=search(dur, T, 0);
//    printf("jh");
    
    clock_t start, finish;
    char durStr[100];
    FILE *f=fopen(patterns_filename,"r");
    start=clock();
    printf("start\n");
    int totalPatterns=0;
    while(~fscanf(f,"%s",durStr))
    {
//        printf("%s",durStr);
        char2Binary(durStr, dur);
        insert(dur,T, 0);
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
        char2Binary(durStr,dur);
        if(search(dur,T, 0)==1)
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
    printf("d");
    return 0;
}
