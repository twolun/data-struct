#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    ADT Complex {
        数据对象：D = {c1, c2 | c1,c2属于R}
        数据关系：R = {<c1, c2> | c1为实部，c2为虚部}

        基本操作：

        InitComplex(&C, j, i);
            初始条件：实数C存放
            操作结果：以j为实部，i为虚部初始化C

        Complex_sum(&C, c1, c2);
            初始条件：C存在，c1,c2已经初始化
            操作结果：通过C返回c1加上c2的结果

        Complex_sub(&C, c1, c2);
            初始条件：C存在，c1,c2已经初始化
            操作结果：通过C返回c1减去c2的结果

        Complex_multi(&C, c1, c2);
            初始条件：C存在，c1,c2已经初始化
            操作结果：通过C返回c1*c2的结果

        Complex_getr(C, &e);
            初始条件：C存在，并已初始化
            操作结果：通过e返回复数C的实部

        Complex_geti(C, &e);
            初始条件：C存在，并已经初始化
            操作结果：通过e返回复数C的虚部

    }
*/

// 1. 元素类型， 结点类型， 指针类型定义
#define OK       1
#define ERROR    -1

typedef int Status;

typedef struct Complex {
    float r;        // 复数实部
    float i;        // 复数虚部
} Complex, * ComplexP;


// 1. 初始化
Status InitComplex(ComplexP C, float r, float i) {
    C->r = r;
    C->i = i;
    return OK;
}

// 2. 两个复数相加
Status Complex_sum(ComplexP C, Complex c1, Complex c2) {
//    printf("%f, %f, %f, %f\n", c1.j, c1.i, c2.j, c2.i);
    C->r = c1.r + c2.r;
    C->i = c1.i + c2.i;
    return OK;
}

// 3. 两个复数相乖
Status Complex_multi(ComplexP C, Complex c1, Complex c2) {
    C->r = c1.r * c2.r;
    C->i = c1.i * c2.i;
    return OK;
}

// 4. 返回C的实部
Status Complex_getr(Complex C, float * e) {
    *e = C.r;
    return OK;
}

// 打印Complex
void printC(Complex C) {
    if((int)C.r == 0 && (int)C.i == 0) {
        printf("%d\n", 0);
    } else if(C.i < 0) {
        if((int)C.r == 0) {
            printf("-i%.2f", fabs(C.i));
        } else {
           printf("%.2f-i%.2f\n", C.r, fabs(C.i));
        }

    } else {
        if((int)C.i == 0) {
            printf("%.2f", C.r);
        } else {
            printf("%.2f+i%.2f\n", C.r, C.i);
        }
    }
}





void practice01(void) {
    Complex C, c1, c2;
    float c1r, c1i, c2r, c2i;
    scanf("%f,%f;%f,%f;", &c1r, &c1i, &c2r, &c2i);
//    printf("scanfNum: %d", scanfNum);
//    printf("c1j: %f, c1i: %f, c2j: %f, c2i: %f", c1j, c1i, c2j, c2i);
    InitComplex(&c1, c1r, c1i);
    InitComplex(&c2, c2r, c2i);

    // start: 测试c1+c2的结果
//    Complex_sum(&C, c1, c2);
//    printC(C);
    // end: c1+c2测试通过

    // start: 测试c1*c2
//    Complex_multi(&C, c1, c2);
//    printC(C);
    // end: c1 * c2测试通过

    // start：测试获取实部
//    float e;
//    Complex_getr(c1, &e);
//    printf("c1 的实部：%.2f\n", e);
    // end: 测试通过
}
