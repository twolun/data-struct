#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    ADT Complex {
        ���ݶ���D = {c1, c2 | c1,c2����R}
        ���ݹ�ϵ��R = {<c1, c2> | c1Ϊʵ����c2Ϊ�鲿}

        ����������

        InitComplex(&C, j, i);
            ��ʼ������ʵ��C���
            �����������jΪʵ����iΪ�鲿��ʼ��C

        Complex_sum(&C, c1, c2);
            ��ʼ������C���ڣ�c1,c2�Ѿ���ʼ��
            ���������ͨ��C����c1����c2�Ľ��

        Complex_sub(&C, c1, c2);
            ��ʼ������C���ڣ�c1,c2�Ѿ���ʼ��
            ���������ͨ��C����c1��ȥc2�Ľ��

        Complex_multi(&C, c1, c2);
            ��ʼ������C���ڣ�c1,c2�Ѿ���ʼ��
            ���������ͨ��C����c1*c2�Ľ��

        Complex_getr(C, &e);
            ��ʼ������C���ڣ����ѳ�ʼ��
            ���������ͨ��e���ظ���C��ʵ��

        Complex_geti(C, &e);
            ��ʼ������C���ڣ����Ѿ���ʼ��
            ���������ͨ��e���ظ���C���鲿

    }
*/

// 1. Ԫ�����ͣ� ������ͣ� ָ�����Ͷ���
#define OK       1
#define ERROR    -1

typedef int Status;

typedef struct Complex {
    float r;        // ����ʵ��
    float i;        // �����鲿
} Complex, * ComplexP;


// 1. ��ʼ��
Status InitComplex(ComplexP C, float r, float i) {
    C->r = r;
    C->i = i;
    return OK;
}

// 2. �����������
Status Complex_sum(ComplexP C, Complex c1, Complex c2) {
//    printf("%f, %f, %f, %f\n", c1.j, c1.i, c2.j, c2.i);
    C->r = c1.r + c2.r;
    C->i = c1.i + c2.i;
    return OK;
}

// 3. �����������
Status Complex_multi(ComplexP C, Complex c1, Complex c2) {
    C->r = c1.r * c2.r;
    C->i = c1.i * c2.i;
    return OK;
}

// 4. ����C��ʵ��
Status Complex_getr(Complex C, float * e) {
    *e = C.r;
    return OK;
}

// ��ӡComplex
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

    // start: ����c1+c2�Ľ��
//    Complex_sum(&C, c1, c2);
//    printC(C);
    // end: c1+c2����ͨ��

    // start: ����c1*c2
//    Complex_multi(&C, c1, c2);
//    printC(C);
    // end: c1 * c2����ͨ��

    // start�����Ի�ȡʵ��
//    float e;
//    Complex_getr(c1, &e);
//    printf("c1 ��ʵ����%.2f\n", e);
    // end: ����ͨ��
}
