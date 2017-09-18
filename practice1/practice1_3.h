#ifndef PRACTICE1_3_H_INCLUDED
#define PRACTICE1_3_H_INCLUDED
#include <string.h>
#include <ctype.h>
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2

typedef int Status;
typedef char ElemType;

// ������ṹ
typedef struct NodeType {
    ElemType data;              // �������
    struct NodeType * next;     // ���ָ����ֱ�Ӻ��
}NodeType, * LinkType;

// ��������ṹ
typedef struct {
    LinkType head, tail;        // ָ���һ��Ԫ�ؽ������ һ��Ԫ�ؽ��
    int size;                   // ������
}OrderedList;

typedef OrderedList OrderedSet; // ���Ͻṹ


// �����ز���
Status MakeNode(LinkType * p, ElemType e);
// ���������������pָ�������Ԫ��Ϊe������Ϊ�յĽ�㣬������TRUE��ʧ�ܷ���FALSE

void FreeNode(LinkType * p);
// ����������ͷ���pָ��Ľ��Ĵ洢�ռ�

LinkType Copy(LinkType p);
// ������������Ʋ�������pָ�����Ԫ�����ɵ��µĽ��

ElemType Elem(LinkType p);
// ���������������pָ�����Ԫ��ֵ

LinkType NextNode(LinkType p);
// ���������������pָ����ĺ��ָ��


// �����������
Status InitList(OrderedList * L);
// �������������һ���յ������L�����򷵻�FALSE

void DestroyList(OrderedList * L);
// ��ʼ�����������L����
// ������������������L

int ListLength(OrderedList L);
// ��ʼ�����������L����
// ������������������L�ĳ���

Status ListEmpty(OrderedList L);
// ��ʼ�����������L����
// ��������������LΪ�գ�����TRUE�����򷵻�FALSE

LinkType GetElemPos(OrderedList L, int pos);
// ��ʼ�����������L����
// ������������������L�У���pos��Ԫ�صĵ�ַ

Status LocateElem(OrderedList L, ElemType e, LinkType * p);
// ��ʼ�����������L����
// �����������L�д�e����qָ���һ��ֵΪe�Ľ���λ�ã�������TRUE
//           ����qָ���һ��ֵ����e�Ľ���ǰ����λ�ã�������FALSE

Status Append(OrderedList * L, LinkType p);
// ��ʼ�����������L����
// ����������������Lĩβ����pָ��Ľ�㣬�ɹ�����TRUE�����򷵻�FALSE

Status InsertAfter(OrderedList * L, LinkType q, LinkType p);
// ��ʼ�����������L����
// ����������������L�У�qָ���Ԫ�غ����p

void WriteElem(LinkType p);
// �����������ӡ�ڵ��Ӧ��Ԫ��

void ListTraverse(LinkType p, void(* visit)(LinkType));
// ������������ζ�L��Pָʾ�Ľ��֮��Ľ�����ε���visit



// ���ϻ�������
Status CreateSet(OrderedSet * T, char * s);
// ��ʼ���������ַ���s��������T
// ������������ַ���s��������T

void DestroySet(OrderedSet * T);
// ��ʼ����������T����
// ������������ټ���T

void Union(OrderedSet * T, OrderedSet S1, OrderedSet S2);
// ��ʼ����������S1��S2����
// ���������������S1, S2������ɵļ���T

void InterSection(OrderedSet * T, OrderedSet S1, OrderedSet S2);
// ��ʼ����������S1, S2����
// ���������������S1, S2������ɵļ���T

void Difference(OrderedSet * T, OrderedSet S1, OrderedSet S2);
// ��ʼ����������S1, S2����
// ���������������S1, S2���ɵļ���T

void PrintSet(OrderedSet T);
// ��ʼ����������T����
// �����������ӡ����T

void WriteSetElem(LinkType p);
// �����������ӡ�����е�һ��Ԫ��

void Initialization();
// ��������������ʼ����չʾ�����ĵ�
void ReadCommand(char * cmd);
// �����������ȡ��������
void Interpret(char cmd);
// �����������������ִ����Ӧ�Ĳ�������չʾ�������

void PrintRes(char cmd);
// ��������������������

#endif // PRACTICE1_3_H_INCLUDED

/*
    1. �����ĳ����������Ͷ���
    ADT OrderedList {
        ���ݶ���D = {a(i) | a(i) ����CharSet, i=1,2,...,n, n>=0}
        ���ݹ�ϵ��R1 = {<a(i-1), a(i)> | a(i-1),a(1)����D��a(i-1)<a(i), i=2,3,...,n}
        ����������
            InitList(&L);
                �������������һ���յ������L
            DestroyList(&L);
                ��ʼ�����������L����
                ������������������L
            ListLength(L);
                ��ʼ�����������L����
                ������������������L�ĳ���
            ListEmpty(L);
                ��ʼ�����������L����
                ����������������LΪ�գ��򷵻�True�����򷵻�False
            GetElem(L, pos);
                ��ʼ�����������L����
                �����������1=<pos<=ListLength(L)�����ر�L�е�pos��Ԫ��
            LocateElem(L, e);
                ��ʼ�����������L����
                ����������������L�д���Ԫ��e���򷵻�L�е�һ��ֵe��Ԫ�ص�λ�ã�
                          ����qָʾ��һ������e��Ԫ�ص�ǰ����λ��
            Append(&L, e);
                ��ʼ�����������L����
                ����������������L��ĩβ����Ԫ��e
            InsertAfter(&L, q, e);
                ��ʼ�����������L���ڣ�qָʾL�е�һ��Ԫ�أ�
                ����������������L��qָʾ��Ԫ��֮�󣬲���Ԫ��e
            ListTraverse(q, visit());
                ��ʼ�����������L���ڣ�qָʾL�е�һ��Ԫ��
                ������������ζ�L��qָʾ��Ԫ�ؿ�ʼ��ÿ��Ԫ�ص��ú���visit()
    }

    2. ���ϵĳ����������Ͷ���
    ADT Set {
        ���ݶ���D={a(i) | a(i)ΪӢ��Сд��ĸ�һ�����ͬ, i=1,2,...,n, 0=<n<=26}
        ���ݹ�ϵ��R1 = {}
        ����������
            CreateSet(&T,Str);
                ��ʼ������StrΪ�ַ���
                �������������һ����Str��Сд��ĸ��ɵļ���T
            DestroySet(&T);
                ��ʼ����������T����
                ������������ټ���T�Ľṹ
            Union(&T,S1,S2);
                ��ʼ����������S1,S2����
                �������������һ���ɼ���S1��S2�������ɵļ���T
            InterSection(&T,S1,S2);
                ��ʼ����������S1,S2����
                �������������һ���ɼ���S1��S2�������ɵļ���T
            Difference(&T,S1,S2);
                ��ʼ����������S1,S2����
                �������������һ���ɼ���S1��S2����ɵļ���T
            PrintSet(T);
                ��ʼ����������T����
                �������������ĸ����˳����ʾ����T�е�ȫ��Ԫ��
    }
*/
