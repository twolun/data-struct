#include "test.h"

void TestMain(void) {
    char arrb[10];
    gets(arrb);
    int ok;
//    ok = Test1(arrb);
    ok = Test2(arrb);
    printf("ok is: %d", ok);
}

int Test2(char * arr) {
    char arrb[10];      // 用于存放待期待匹配的字符
    char x;             // 待期待字符
    int i = 0;
    int j = 0;
    switch(arr[0]) {
        case '(':
            x = ')';
            break;
        case '[':
            x = ']';
            break;
        case '{':
            x = '}';
            break;
    }
    arrb[j] = x;
    printf("now x is: %c\n", arrb[0]);
    i = 1;
    while(arr[i]) {
        x = arrb[j];
        printf("%c ", x);
//        free(arrb[j]); //出栈
        if(arr[i] != x) {
            arrb[j] = x;    // 没有匹配，再次入栈
                 // 没有匹配，将当前期望入栈
            switch(arr[i]) {
                case '(':
                    x = ')';
                    break;
                case '[':
                    x = ']';
                    break;
                case '{':
                    x = '}';
                    break;
            }
            arrb[++j] = x;
        } else {
            free(arrb[j]);
            --j;
        }
        ++i;
    }

    if(j < 0) return 1;
    else return 0;

}



int Test1(char * arr) {
    int i = 0, j = 0;
    char arrc[10];

    while(arr[i] != '&' && arr[i]) {
        arrc[j] = arr[i];
        ++j;
        ++i;
//        printf("%c ", arr[i]);
    }
    int k = 0;
    while(k < j) {
        printf("%c ", arrc[k]);
        ++k;
    }
    printf("\n");
    --j;
    ++i;
    // 跳过'&'指向下一个字符
    while(arr[i] && j >= 0) {
        printf("arr[i] is: %c, arr[j] is %c", arr[i], arrc[j]);
        if(arr[i] != arrc[j]) {
            break;
        }
        i++;
        j--;
        printf("i is: %d---j is: %d\n", i, j);
    }
    if(j == -1) return 1;
    else return 0;
}
