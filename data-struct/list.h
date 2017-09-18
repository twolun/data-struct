#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
#define OK              1
#define OVERFLOW        0
#define ERROR           0
#define ALEN            8
#define MAXSIZE         1000        //�������󳤶�

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

// ����������ʼ��һ���б�
// ����ǰ��Lָ��һ���б�
// ������Lָ��һ�����б�
int InitList_Sq(SqList * L);

// ������  ��ʼ��һ������
// ����ǰ��Lָ��һ������
// ������Lָ��һ��������
Status InitList_Ln(LinkList LL);
Status InitList_Lc(CLinkList CL);
Status ListAdd_Ln(LNode node, LinkList LL);
Status ListAdd_Lc(CLNode node, CLinkList LL);

// ������ �������LL�е�i��Ԫ�أ���ͨ��e����
// ����ǰ������LL�Ѿ�����
// ������ͨ��e��������LL�е�i��Ԫ�أ�������OK
Status GetElem_Ln(LinkList LL, int i, ElemType * e);

Status ListInsert_Ln(LinkList LL, int i, ElemType e);
Status ListInsert_Lc(CLinkList LL, int i, char e);
// ��ʼ������LLָ��һ���Ѿ����ڵ�����
// ���������Ԫ��e�����뵽LLָ��������iλ��

Status ListDelete_Ln(LinkList LL, int i, ElemType * e);
// ��ʼ������LL�����Ѿ����ڣ�
// �������

Status CreateList_Ln(LinkList * LL, int n);
// ���������������������

Status MergeList_Ln(LinkList La, LinkList Lb, LinkList * Lc);
// ����ǰ��La, Lb�ǿգ���Ԫ�ذ�����ֵ�ݼ�
// �����󣺹鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ������ֵ�ݼ�

Status TreveleSq_LN(SqList * LL);
Status TreveleList_LN(LinkList LL);

Status Trevele_MergeList_LN(LinkList La, LinkList Lb);
// ����ǰ��La, Lb�����ڣ�������������
// ������La �д��La��Lb����Ԫ�صķǵ�������

Status Order_IntersectList_LN(LinkList La, LinkList Lb, LinkList Lc);
// ����ǰ��La, Lb, Lc�Ѵ��ڣ� La, Lb��������
// ������La, Lb, Ԫ�صĽ��������Lc�У�����Lc��ֵ��������

// ��̬����
void InitSpace_SL(SNode * space);
Status Malloc_SL(SNode * space);
void Free_SL(SNode * space, int k);
// ����ǰ: space�Ѿ�����
// �����󣺽��±�Ϊk�Ŀ��нڵ���յ���������

int LocateElem_SL(SNode * space, ElemType e);
// ����ǰ��space�Ѿ�����
// ���������e���ڣ��򷵻�e���������е�λ�ã����򷵻�0

void difference_SL(SNode * space, int * S);
// ����ǰ��

Status ListDivideInfo3(CLinkList L, CLinkList l1, CLinkList l2, CLinkList l3);

void printll(CLinkList L);

void listMain(void);
void listLnMain(void);
void slistMain(void);

#endif // LIST_H_INCLUDED
