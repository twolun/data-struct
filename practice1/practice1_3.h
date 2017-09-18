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

// 链表结点结构
typedef struct NodeType {
    ElemType data;              // 结点数据
    struct NodeType * next;     // 结点指针域，直接后继
}NodeType, * LinkType;

// 有序链表结构
typedef struct {
    LinkType head, tail;        // 指向第一个元素结点和最后 一个元素结点
    int size;                   // 链表长度
}OrderedList;

typedef OrderedList OrderedSet; // 集合结构


// 结点相关操作
Status MakeNode(LinkType * p, ElemType e);
// 操作结果：分配由p指向的数据元素为e，后续为空的结点，并返回TRUE，失败返回FALSE

void FreeNode(LinkType * p);
// 操作结果：释放由p指向的结点的存储空间

LinkType Copy(LinkType p);
// 操作结果：复制并返回由p指向结点的元素生成的新的结点

ElemType Elem(LinkType p);
// 操作结果：返回由p指向结点的元素值

LinkType NextNode(LinkType p);
// 操作结果：返回由p指向结点的后继指针


// 链表基本操作
Status InitList(OrderedList * L);
// 操作结果：构造一个空的有序表L，否则返回FALSE

void DestroyList(OrderedList * L);
// 初始条件：有序表L存在
// 操作结果：销毁有序表L

int ListLength(OrderedList L);
// 初始条件：有序表L存在
// 操作结果：返回有序表L的长度

Status ListEmpty(OrderedList L);
// 初始条件：有序表L存在
// 操作结果：有序表L为空，反加TRUE，否则返回FALSE

LinkType GetElemPos(OrderedList L, int pos);
// 初始条件：有序表L存在
// 操作结果：返回有序表L中，第pos个元素的地址

Status LocateElem(OrderedList L, ElemType e, LinkType * p);
// 初始条件：有序表L存在
// 操作结果：若L中存e，则q指向第一个值为e的结点的位置，并返回TRUE
//           否则q指向第一个值大于e的结点的前驱的位置，并返回FALSE

Status Append(OrderedList * L, LinkType p);
// 初始条件：有序表L存在
// 操作结果：在有序表L末尾插入p指向的结点，成功返回TRUE，否则返回FALSE

Status InsertAfter(OrderedList * L, LinkType q, LinkType p);
// 初始条件：有序表L存在
// 操作结果：在有序表L中，q指向的元素后插入p

void WriteElem(LinkType p);
// 操作结果：打印节点对应的元素

void ListTraverse(LinkType p, void(* visit)(LinkType));
// 操作结果：依次对L中P指示的结点之后的结点依次调用visit



// 集合基本操作
Status CreateSet(OrderedSet * T, char * s);
// 初始条件：用字符串s创建集合T
// 操作结果：用字符串s创建集合T

void DestroySet(OrderedSet * T);
// 初始条件：集合T存在
// 操作结果：销毁集合T

void Union(OrderedSet * T, OrderedSet S1, OrderedSet S2);
// 初始条件：集合S1、S2存在
// 操作结果：创建由S1, S2并集组成的集合T

void InterSection(OrderedSet * T, OrderedSet S1, OrderedSet S2);
// 初始条件：集合S1, S2存在
// 操作结果：创建由S1, S2交集组成的集合T

void Difference(OrderedSet * T, OrderedSet S1, OrderedSet S2);
// 初始条件：集合S1, S2存在
// 操作结果：创建由S1, S2差集组成的集合T

void PrintSet(OrderedSet T);
// 初始条件：集合T存在
// 操作结果：打印集合T

void WriteSetElem(LinkType p);
// 操作结果：打印集合中的一个元素

void Initialization();
// 操作结果：程序初始化，展示操作文档
void ReadCommand(char * cmd);
// 操作结果：获取操作命令
void Interpret(char cmd);
// 操作结果：根据命令执行相应的操作，并展示操作结果

void PrintRes(char cmd);
// 操作结果：辅助输出函数

#endif // PRACTICE1_3_H_INCLUDED

/*
    1. 有序表的抽象数据类型定义
    ADT OrderedList {
        数据对象：D = {a(i) | a(i) 属于CharSet, i=1,2,...,n, n>=0}
        数据关系：R1 = {<a(i-1), a(i)> | a(i-1),a(1)属于D，a(i-1)<a(i), i=2,3,...,n}
        基本操作：
            InitList(&L);
                操作结果：构造一个空的有序表L
            DestroyList(&L);
                初始条件：有序表L存在
                操作结果：销毁有序表L
            ListLength(L);
                初始条件：有序表L存在
                操作结果：返回有序表L的长度
            ListEmpty(L);
                初始条件：有序表L存在
                操作结果：若有序表L为空，则返回True，否则返回False
            GetElem(L, pos);
                初始条件：有序表L存在
                操作结果：若1=<pos<=ListLength(L)，返回表L中第pos个元素
            LocateElem(L, e);
                初始条件：有序表L存在
                操作结果：若有序表L中存在元素e，则返回L中第一个值e的元素的位置，
                          否则q指示第一个大于e的元素的前驱的位置
            Append(&L, e);
                初始条件：有序表L存在
                操作结果：在有序表L的末尾插入元素e
            InsertAfter(&L, q, e);
                初始条件：有序表L存在，q指示L中的一个元素，
                操作结果：在有序表L中q指示的元素之后，插入元素e
            ListTraverse(q, visit());
                初始条件：有序表L存在，q指示L中的一个元素
                操作结果：依次对L中q指示的元素开始的每个元素调用函数visit()
    }

    2. 集合的抽象数据类型定义
    ADT Set {
        数据对象：D={a(i) | a(i)为英文小写字母且互不相同, i=1,2,...,n, 0=<n<=26}
        数据关系：R1 = {}
        基本操作：
            CreateSet(&T,Str);
                初始条件：Str为字符串
                操作结果：生成一个由Str中小写字母组成的集合T
            DestroySet(&T);
                初始条件：集合T存在
                操作结果：销毁集合T的结构
            Union(&T,S1,S2);
                初始条件：集合S1,S2存在
                操作结果：生成一个由集合S1和S2并集构成的集合T
            InterSection(&T,S1,S2);
                初始条件：集合S1,S2存在
                操作结果：生成一个由集合S1和S2交集构成的集合T
            Difference(&T,S1,S2);
                初始条件：集合S1,S2存在
                操作结果：生成一个由集合S1和S2差集构成的集合T
            PrintSet(T);
                初始条件：集合T存在
                操作结果：按字母次序顺序显示集合T中的全部元素
    }
*/
