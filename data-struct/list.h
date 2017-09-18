#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
#define OK              1
#define OVERFLOW        0
#define ERROR           0
#define ALEN            8
#define MAXSIZE         1000        //链表的最大长度

static int arrA[ALEN] = {12, 13, 21, 24, 28, 30, 42, 77};
static int arrB[5] = {15, 18, 31, 33, 90};
static int arrC[5] = {13, 16, 24, 28, 30};
static char arrD[12] = {'1', 'c', '2', 'A', 'b', '#', '5', '*', 'd', '(', '8', '$'};
//static (char *) arrC[8] = {"ZHAO", "QIAN", "SUN", "LI", "ZHOU", "WU", "ZHENG", "WANG"};


typedef int ElemType;
typedef int Status;

typedef struct {
    ElemType * elem;
    int      length;
    int      listsize;
} SqList;

typedef struct LNode {
    ElemType        data;
    struct LNode    * next;
}LNode, * LinkList;

typedef struct {
    ElemType data;
    int cur;
}SNode, SLinkList[MAXSIZE];

typedef struct CLNode {
    char data;
    struct CLNode * next;
}CLNode, * CLinkList;

//typedef struct LinkList {
//    LNode * head;
//    int size;
//} LinkList;

// 操作作：初始化一个列表
// 操作前：L指向一个列表
// 操作后：L指向一个空列表
int InitList_Sq(SqList * L);

// 操作：  初始化一个链表
// 操作前：L指向一个链表
// 操作后：L指向一个空链表
Status InitList_Ln(LinkList LL);
Status InitList_Lc(CLinkList CL);
Status ListAdd_Ln(LNode node, LinkList LL);
Status ListAdd_Lc(CLNode node, CLinkList LL);

// 操作： 获得链表LL中第i个元素，并通过e返回
// 操作前：链表LL已经存在
// 操作后：通过e返回链表LL中第i个元素，并返回OK
Status GetElem_Ln(LinkList LL, int i, ElemType * e);

Status ListInsert_Ln(LinkList LL, int i, ElemType e);
Status ListInsert_Lc(CLinkList LL, int i, char e);
// 初始条件：LL指向一个已经存在的链表
// 操作结果：元素e被插入到LL指向的链表第i位置

Status ListDelete_Ln(LinkList LL, int i, ElemType * e);
// 初始条件：LL链表已经存在，
// 操作结果

Status CreateList_Ln(LinkList * LL, int n);
// 操作结果：创建逆向链表

Status MergeList_Ln(LinkList La, LinkList Lb, LinkList * Lc);
// 操作前：La, Lb非空，并元素按非数值递减
// 操作后：归并La和Lb得到新的单链线性表Lc，Lc的元素也按非数值递减

Status TreveleSq_LN(SqList * LL);
Status TreveleList_LN(LinkList LL);

Status Trevele_MergeList_LN(LinkList La, LinkList Lb);
// 操作前：La, Lb，存在，并按递增排序
// 操作后：La 中存放La，Lb所有元素的非递增序列

Status Order_IntersectList_LN(LinkList La, LinkList Lb, LinkList Lc);
// 操作前：La, Lb, Lc已存在， La, Lb递增有序
// 操作后：La, Lb, 元素的交集存放在Lc中，并且Lc依值递增排序

// 静态链表
void InitSpace_SL(SNode * space);
Status Malloc_SL(SNode * space);
void Free_SL(SNode * space, int k);
// 操作前: space已经存在
// 操作后：将下标为k的空闲节点回收到备用链表

int LocateElem_SL(SNode * space, ElemType e);
// 操作前：space已经存在
// 操作后：如果e存在，则返回e所在链表中的位置，否则返回0

void difference_SL(SNode * space, int * S);
// 操作前：

Status ListDivideInfo3(CLinkList L, CLinkList l1, CLinkList l2, CLinkList l3);

void printll(CLinkList L);

void listMain(void);
void listLnMain(void);
void slistMain(void);

#endif // LIST_H_INCLUDED
