#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InoutMain(void) {
    int ch;
    char s1[20], s2[20];
    FILE * fp;          // 文件指针
    long count = 0;

    // 打开文件
    if((fp = fopen("arc.txt", "r")) == NULL) {
        printf("Can't open %s\n", "arc.txt");
        exit(1);
    }
//    while((ch = getc(fp)) != EOF) {
//        putc(ch, stdout);       // 相当于putchar(ch)
//        count++;
//    }
    // 1. 获取行号
    fgets(s1, 20, fp);
    strcpy(s2, s1+1);
    int m = atoi(s1);
    int n = atoi(s2);
    printf("m is: %d, n is: %d\n", m, n);
    while(fgets(s1, 20, fp) != NULL) {
        printf("%s\n", s1);
        count++;
    }
    printf("count is: %ld\n", count);
    fclose(fp);
}
