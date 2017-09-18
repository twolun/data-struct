#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

// 1. 输出 SqList 辅助函数
void printa(SqList L);
int equal(ElemType a, ElemType b);
// 2. 算法2.3，插入线性表
Status ListInsert_Sq(SqList * L, int i, ElemType e);

// 3. 算法2.4，删除线性表
Status ListDelete_Sq(SqList * L, int i, ElemType * e);

// 4. 算法2.5，定位元素
int LocateElem_Sq(SqList L, ElemType e, Status (* compare)(ElemType, ElemType));

// 5. 算法2.6，顺序表合并
void MergeList_Sq(SqList La, SqList Lb, SqList * Lc);

// 输出链表
void printl(LinkList LL);

// 输出静态链表
void printsl(SNode * space);

void slistMain(void) {
    SLinkList space;
//    InitSpace_SL(space);
//    int i = 0, cur = space[0].cur;
//    while(i < 8) {
//        space[cur].data = arrA[i];
//        cur = space[++i].cur;
//    }
//
//    printsl(space);
//
//    i = LocateElem_SL(space, 28);
//    printf("e in sl is: %d\n", i);

    // difference_SL测试
    int S;
    difference_SL(space, &S);
    printsl(space);
}

void difference_SL(SNode * space, int * S) {
    // 依次输入集合A, B的元素，在一维数组space中建立
    // S为头指针，space[0].cur 为其头指针
//    SLinkList spacee;
    int r;                      // 指向最后结点的指针
    int m, n, j, i, b, p, k, F;                   // A, B元素的个数
    InitSpace_SL(space);
//    S = Malloc_SL(space);       // 生成头结点，即是0
    *S = 0;
    F = space[0].cur;             // 保存第一个结点指针
//    printf("space[1] = %d\n", space[0].cur);

//    printf("S is: %d", S);

    r = i = space[*S].cur;                      // r指向最后的结点
    printf("\nA表元素的个数：");
    scanf("%d", &m);
    printf("\nB表元素的个数：");
    scanf("%d", &n);
//    int ii = 0, cur = space[0].cur;
//    while(ii < 8) {
////        spacee[cur].data = arrA[ii];
//        scanf("%d", &(space[cur].data));
//        cur = space[++ii].cur;
//    }
    for(j = 1; j <= m; j++) {
        i = Malloc_SL(space);
        printf("spacee[%d] is: ", i);
        scanf("%d", &(space[i].data));
//        i = space[i].cur;
        space[r].cur = i;
        r = i;
    }      // 0 指向第一个头结点
    // 由于循环结束前 内存被多分配了一次，所以要释放掉
//    Free_SL(space, i);
//    r = i - 1;
    printf("r is: %d\n", r);
    space[r].cur = 0;       // 最后个结点
//
    // 依次输入B的元素，若不存在则插入，存在则删除
    for(j = 1; j<= n; j++) {
        scanf("%d", &b);
        p = *S;
        k = F;      // k指向第一个结点
        while(k != space[r].cur && space[k].data != b) {
            p = k;
            k = space[k].cur;
//            printf("k is: %d\n", k);
        }

        if(k == space[r].cur) { // 当前列表不存在 该元素
            i = Malloc_SL(space);
            printf("i now is: %d\n", i);
            space[i].data = b;
            space[i].cur = space[r].cur;        //当前结点指针指向空指针
            space[r].cur = i;                   // 最后结点指针指向当前指针
        } else {
            space[p].cur = space[k].cur;        // 在这里重新将删除节点的前一个节点的cur指向要删除节点的cur
                                                // 为什么不在Free_SL()里执行呢
            Free_SL(space, k);
            if(r == k) r = p;
        }
    }
    // 由于翻译内存后，space[0].cur已经改变，在些重置指向第一个
//    space[0].cur = F;
    printf("space[1].data is: %d\n", space[3].cur);
    i = 0;
    while(i < 8) {
        printf("space[%d].cur is: %d---space[%d].data is: %d\n ", i, space[i].cur, i, space[i].data);
        ++i;
    }

//    printsl(space);
}

// 在静态链表中定位元素
int LocateElem_SL(SLinkList space, ElemType e) {
    int i = space[0].cur;
    while(i && space[i].data != e) i = space[i].cur;
    return i;
}

// 回收空间
void Free_SL(SNode * space, int k) {
//    space[k - 1].cur = space[k].cur;wq    21`bnmkl;
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

// 分配存储空间
Status Malloc_SL(SNode * space) {
    int i = space[0].cur;
    if(space[0].cur) space[0].cur = space[i].cur;
    return i;
}

// 初始化数组空间为一个链表
void InitSpace_SL(SNode * space) {
    // 将一维数组space中各分量链成一个备用链表， space[0].cur为头指针
    // '0'表示空指针
    int i;
    for(i = 0; i < MAXSIZE; i ++) {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0;
}

// 输出静态链表
void printsl(SNode * space) {
    // 从第一个结点开始输出，忽略掉头结点
    int i = 1;
    printf("SL is: ");
    while(i) {
        printf("%d ", space[i].data);
        i = space[i].cur;
    }
    printf("%\n");
}


void listLnMain(void) {
    int i = 0;
//    LinkList linkL = (LinkList)malloc(sizeof(LNode));
//    LNode lnode;
//    // 初始化链表LL
//    InitList_Ln(linkL);
//    while(i < ALEN) {
//        lnode.data = arrA[i];
//        lnode.next = NULL;
//        ListAdd_Ln(lnode, linkL);
//        i++;
//    }
//    printl(linkL);

    // 获取链表第i个元素测试
//    ElemType ei;
//    GetElem_Ln(linkL, 3, &ei);
//    printf("ei is: %d\n", ei);

    // 插入元素测试
//    int ok;
//    ok = ListInsert_Ln(linkL, 5, 12);
//    printf("---%d---\n", ok);
    // 删除元素操作
//    ElemType e;
//    ListDelete_Ln(linkL, 5, &e);
//    printf("delete e is: %d\n", e);
//    printl(linkL);
    // 生成逆位序线性链表
//    LinkList linkB;
//    InitList_Ln(linkB);
//    CreateList_Ln(&linkB, 5);
//    printl(linkB);
//    printf("%d\n", linkB->data);

    // 归并算法测试
//    LinkList Lb = (LinkList)malloc(sizeof(LNode));
//    LinkList Lc = (LinkList)malloc(sizeof(LNode));
//    InitList_Ln(Lb);
//    InitList_Ln(Lc);
//    i = 0;
//    while(i < 5) {
//        lnode.data = arrB[i];
//        lnode.next = NULL;
//        ListAdd_Ln(lnode, Lb);
//        i++;
//    }
//    printl(Lb);
//    MergeList_Ln(linkL, Lb, &Lc);
//    TreveleList_LN(linkL);

    // 两个递增链表，按非递增合并
//    LinkList Lb = (LinkList)malloc(sizeof(LNode));
//    LinkList Lc = (LinkList)malloc(sizeof(LNode));
//    InitList_Ln(Lb);
//    InitList_Ln(Lc);
//    i = 0;
//    while(i < 5) {
//        lnode.data = arrC[i];
//        lnode.next = NULL;
//        ListAdd_Ln(lnode, Lb);
//        i++;
//    }
    // 测试
//    Trevele_MergeList_LN(linkL, Lb);
//    printl(Lb);
//    Order_IntersectList_LN(linkL, Lb, Lc);
//    printl(Lc);
    CLinkList cLL = (CLinkList)malloc(sizeof(CLNode));
    CLNode cnode;
    // 初始化链表LL
    InitList_Lc(cLL);
    while(i < 12) {
//        printf("%c--", arrD[i]);
        cnode.data = arrD[i];
        cnode.next = NULL;
        ListAdd_Lc(cnode, cLL);
        i++;
    }
    printlc(cLL);
    CLinkList S1 = (CLinkList)malloc(sizeof(CLNode));
    CLinkList S2 = (CLinkList)malloc(sizeof(CLNode));
    CLinkList S3 = (CLinkList)malloc(sizeof(CLNode));
    InitList_Lc(S1);
    InitList_Lc(S2);
    InitList_Lc(S3);
    ListDivideInfo3(cLL, S1, S2, S3);

    printll(S1);
    printll(S2);
    printll(S3);
}

// 输出循环列表
void printll(CLinkList L) {
    CLinkList p, h;
    h = L;
    p = L->next;
    printf("ll link is: ");
    while(h != p) {
        printf("%c  ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 将一个链表拆分成三个循环链表
Status ListDivideInfo3(CLinkList L, CLinkList s1, CLinkList s2, CLinkList s3) {
    CLinkList p, q, pt1, pt2, pt3;
    p = L->next;
    pt1 = s1;       // 存放字母
    pt2 = s2;       // 存放数字
    pt3 = s3;       // 存放特殊字符

    while(p) {
        if(p->data >= 'A' && p->data <= 'z') {
            q = p;
            p = p->next;
            q->next = pt1->next;
            pt1->next = q;
            pt1 = pt1->next;
        } else if(p->data >= '0' && p->data <= '9') {
            q = p;
            p = p->next;
            q->next = pt2->next;
            pt2->next =q;
            pt2 = pt2->next;
        } else {
            q = p;
            p = p->next;
            q->next = pt3->next;
            pt3->next = q;
            pt3 = pt3->next;
        }
    }
    // 链成循环链表
    pt1->next = s1;
    pt2->next = s2;
    pt3->next = s3;
}

// 求交集，再排序
Status Order_IntersectList_LN(LinkList La, LinkList Lb, LinkList Lc) {
    LinkList pa, pb, pc, qa, qb, qc, pt, ptmp;
    pa = La;
    pb = Lb;
    pc = Lc;
    qa = pa;        // 保存La的前驱
    qb = pb;        // 保存Lb的前驱
    qc = pc;
    pa = pa->next;
    pb = pb->next;
    pc = pc->next;
    int i = 0;
    while(pa && pb) {
        if(pa->data < pb->data) {
            pt = pa;
//            pa = pa->next;
//            qa->next = pa;
            qa->next = pa->next;
            pa = pa->next;
            free(pt);
        } else if(pa->data > pb->data) {
            pt = pb;
            pb = pb->next;
            qb->next = pb;
            free(pt);
        } else {
            qa = pa;
//            pc->next = NULL;
            pa = pa->next;
            if(pc && (pc->data != qa->data)) {
                qc = qc->next;
                qc->next = qa;
                pc = pc->next;
            } else {
                pt = qa;
                qc->next = qa;
                pc = qc->next;
                free(pt);
            }
            ++i;
        }
    }
    pc->next = NULL;    // 这样做是不合理的，我们要free掉可能存在的fqg
    while(pa) {
        pt = pa;
        pa = pa->next;
        qa->next = pa;
        free(pt);
    }
    while(pb) {
        pt = pb;
        pb = pb->next;
        qb->next = pb;
        free(pt);
    }
//    while(pa) {}
//    while(pa) {
//        while(pb) {
//            if(pa->data == pb->data) {
//                printf("pb->data is: %d\n", pb->data);
//                qb = pb;
//                pc->next = qb;
//                pc = pc->next;
//                ++i;
//                break;
//            }
//            pb = pb->next;
//        }
//        pb = Lb->next;
//        pa = pa->next;
//
//    }
    Lc->data = i;
    return OK;
}

// 合并，再排序
Status Trevele_MergeList_LN(LinkList La, LinkList Lb) {
    LinkList pa, pb, qa, qb;
    pa = La;
    pa = pa;    // 保存pa的前驱
    pa = La->next;
    pb = Lb;
    qb = pb;    // 保存pb的驱
    pb = Lb->next;
    La->next = NULL;        // 所有元素存放在La中
    while(pa && pb) {
        if(pa->data <= pb->data) {
            qa = pa;
            pa = pa->next;
            qa->next = La->next;
            La->next = qa;
        } else {
            qb = pb;
            pb = pb->next;
            qb->next = La->next;
            La->next = qb;
        }
    }
    while(pa) {
        qa = pa;
        pa = pa->next;
        qa->next = La->next;
        La->next = qa;
    }
    while(pb) {
        qb = pb;
        pb = pb->next;
        qb->next = La->next;
        La->next = qb;
    }
    return OK;
}

Status TreveleList_LN(LinkList L){
    // 带头结点
    LinkList p, q;
    p = L;
    p = p->next;
    L->next = NULL;
    while(p) {
        q = p;
        p = p->next;
        q->next = L->next;
        L->next = q;
    }
//    LinkList p,q;
//	p=L;
//	p=p->next;
//	L->next=NULL;
//	while(p){
//		q=p;
//		p=p->next;
//		q->next=L->next;
//		L->next=q;
//	}
    return OK;
}

// 归并算法
Status MergeList_Ln(LinkList La, LinkList Lb, LinkList * Lc) {
    LNode * pa = La->next;
    LNode * pb = Lb->next;
    LNode * pc = *Lc;
//    printf("%d", pc->data);
    while(pa && pb) {
        if(pa->data <= pb->data) {
            pc->next = pa;
//            pc = pa;
            pc = pc->next;      // 这样会不会更好理解一点
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pc->next;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;        // 插入剩余链表，仅仅需要进行指针赋值就行了
    (*Lc)->data = La->data + Lb->data;
    free(Lb);                   // 释放掉Lb的头结点
    return OK;
}

// 创建逆向链表
Status CreateList_Ln(LinkList * LL, int n) {
     //逆位序输入n个元素的值，建立带表头结点的单线性表
    int i;
    LNode * p;
    *LL = (LinkList)malloc(sizeof(LNode));
    (*LL)->next = NULL;
    (*LL)->data = 0;
    for(i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = (*LL)->next;
        (*LL)->next = p;
        (*LL)->data++;
    }
    return OK;
}

// 删除元素操作
Status ListDelete_Ln(LinkList LL, int i, ElemType * e) {
    LNode * p = LL, *q;
    int j = 0;
    while(p && j < i - 1) {
        p = p->next;
        ++j;
    }
    if(!p || j > i - 1) return ERROR;

    q = p->next;
    *e = q->data;
    p->next = p->next->next;
    LL->data--;
    free(q);        // 翻译掉被占用的内存
    return OK;
}
// 向链表插入元素e
Status ListInsert_Lc(CLinkList LL, int i, char e) {
    // 在带头结点的链表LL中第i个位置插入元素e
    LNode * p = LL, * s;
    int j = 0;
    while(p && j < i - 1) {
        p = p->next;
        ++j;
    }
    if(!p || j > i - 1) return ERROR;
    s = (LNode *)malloc(sizeof(LNode));
    if(!s) exit(OVERFLOW);
    s->data = e;
    s->next = p->next;
    p->next = s;
    LL->data++;
    return OK;
}

// 向链表插入元素e
Status ListInsert_Ln(LinkList LL, int i, ElemType e) {
    // 在带头结点的链表LL中第i个位置插入元素e
    LNode * p = LL, * s;
    int j = 0;
    while(p && j < i - 1) {
        p = p->next;
        ++j;
    }
    if(!p || j > i - 1) return ERROR;
    s = (LNode *)malloc(sizeof(LNode));
    if(!s) exit(OVERFLOW);
    s->data = e;
    s->next = p->next;
    p->next = s;
    LL->data++;
    return OK;
}

// 获取链表中第i个元素
Status GetElem_Ln(LinkList LL, int i, ElemType * e) {
    LNode * pnode = LL;
    int j = 0;
    while(pnode && j < i) {
        pnode = pnode->next;
        j++;
    }
    if(!pnode || j > i) return ERROR;
    *e = pnode->data;
    return OK;
}

// 向链表添加node
Status ListAdd_Lc(CLNode node, CLinkList LL) {
    CLNode * pnew;
    CLNode * scan = LL->next;
    pnew = (CLNode *)malloc(sizeof(CLNode));
    if(pnew == NULL) exit(OVERFLOW);
    *pnew = node;
    pnew->next = NULL;

    if(scan == NULL) {
        LL->next = pnew;
    }           //放在第一个节点
    else {
        while(scan->next != NULL) {
            scan = scan->next;
        }
        scan->next = pnew;
    }
    LL->data++;
    return OK;
}
// 向链表添加node
Status ListAdd_Ln(LNode node, LinkList LL) {
    LNode * pnew;
    LNode * scan = LL->next;
    pnew = (LNode *)malloc(sizeof(LNode));
    if(pnew == NULL) exit(OVERFLOW);
    *pnew = node;
    pnew->next = NULL;

    if(scan == NULL) {
        LL->next = pnew;
    }           //放在第一个节点
    else {
        while(scan->next != NULL) {
            scan = scan->next;
        }
        scan->next = pnew;
    }
    LL->data++;
    return OK;
}

// 初始化链表
int InitList_Lc(CLinkList LL) {
    // LL指向头结点，头结点指针域为空，头结点数据域存放链表长度
    LL->next = NULL;
    LL->data = '0';
    return OK;
}
// 初始化链表
int InitList_Ln(LinkList LL) {
    // LL指向头结点，头结点指针域为空，头结点数据域存放链表长度
    LL->next = NULL;
    LL->data = 0;
    return OK;
}

// 输出链表
void printlc(CLinkList LL) {
    CLNode * pnode = LL->next;
    printf("linkL is: ");
    while(pnode != NULL) {
        printf("%c ", pnode->data);
        pnode = pnode->next;
    }
    printf("\n");
    printf("linkL length is: %d \n", LL->data);
}
// 输出链表
void printl(LinkList LL) {
    LNode * pnode = LL->next;
    printf("linkL is: ");
    while(pnode != NULL) {
        printf("%d ", pnode->data);
        pnode = pnode->next;
    }
    printf("\n");
    printf("linkL length is: %d \n", LL->data);
}



void listMain(void) {
    SqList sqL;
    int ok;
    int i = 0;
    ok = InitList_Sq(&sqL);
    if(ok) printf("%s", "sqL init success~\n");

    // init sqL.elem
    while(i < ALEN) {
        *(sqL.elem + i) = arrA[i];
        sqL.length++;
        i++;
    }
    printa(sqL);
//    ListInsert_Sq(&sqL, 2, 34);         // 算法2.3 插入测试
//    ElemType e;
//    ListDelete_Sq(&sqL, 2, &e);
//    printf("%d\n", e);
    // 元素定位测试
//    int ei;
//    ei = LocateElem_Sq(sqL, 77, equal);
//    printf("ei= %d\n", ei);
//    printa(sqL);
    // 线性表合并算法测试
//    SqList sqLb, sqLc;
//    InitList_Sq(&sqLb);
//    i = 0;
//    while(i < 5) {
//        *(sqLb.elem + i) = arrB[i];
//        sqLb.length++;
//        i++;
//    }
//    MergeList_Sq(sqL, sqLb, &sqLc);
//    printa(sqL);
//    printa(sqLb);
//    printa(sqLc);
    TreveleSq_LN(&sqL);
    printa(sqL);
}
// 反转链表
Status TreveleSq_LN(SqList * LL) {
    ElemType * p, * q;
    p = LL->elem;
    q = LL->elem + LL->length - 1;
    ElemType x;
    while(p < q) {
        x = *p;
        *p = *q;
        *q = x;
        ++p;
        --q;
    }
    return OK;
}

// 算法2.6
void MergeList_Sq(SqList La, SqList Lb, SqList * Lc) {
    // 已知顺序线性表La和Lb按值非递减排序
    // 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递归排序
    ElemType * pa, * pb, * pc, * pa_last, * pb_last;
    pa = La.elem;
    pb = Lb.elem;
    Lc->listsize = Lc->length = La.length + Lb.length;
    pc = Lc->elem = (ElemType *)malloc(Lc->listsize * sizeof(ElemType));
    if(!Lc->elem) exit(OVERFLOW);
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;
    while(pa <= pa_last && pb <= pb_last) {
        if(*pa <= *pb) *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while(pa <= pa_last) *pc++ = *pa++;
    while(pb <= pb_last) *pc++ = *pb++;
}

// 算法2.5
int LocateElem_Sq(SqList L, ElemType e, Status (* compare)(ElemType, ElemType)) {
    // 若找到e，则返回其在L中的位序，否则返回0
    int i = 1;
    int * p = L.elem;
    while(i <= L.length && !(*compare)(*p++, e)) i++;
    if(i <= L.length) return i;
    else return 0;
}


// 算法2.4
Status ListDelete_Sq(SqList * L, int i, ElemType * e) {
    // 在线性表L中删除第i个元素，并用e返回其值
    // i的合法值 1<=i<=L.length
    ElemType * p, * q;
    if(i < 1 || i > L->length) return ERROR;
    p = &(L->elem[i - 1]);
    *e = *p;                  // p指向的值赋给e
    q = L->elem + L->length - 1;
    for(++p; p <= q; p++) *(p - 1) = *p;
    --L->length;
    return OK;
}

// 算法2.3
Status ListInsert_Sq(SqList * L, int i, ElemType e) {
    // 在顺序线性表L中第个位置之前插入新的元素e
    // i: 1<=i<= L.length + 1
    int * newbase;
    ElemType * p,  * q;        //
    if(i < 1 || i > L->length + 1) return ERROR;
    if(L->length >= L->listsize) {
        newbase = (ElemType * ) realloc(L->elem, (L->listsize + LIST_INCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L->elem = newbase;              // L->elem 指向新地址
        L->listsize += LIST_INCREMENT;
    }
    q = &(L->elem[i - 1]);              // 要插入元素的新位置
    for(p = &(L->elem[L->length - 1]); p >= q; --p) *(p + 1) = *p;      // 元素向后移动
    *q = e;
    ++L->length;                        // 表长增1

    return OK;
}

void printa(SqList L) {
    int i = 0;
    printf("L.elem is: ");
    while(i < L.length) {
        printf("%d  ", L.elem[i]);
        i++;
    }
    printf("\n");
    printf("L.length is: %d\n", L.length);
}

int equal(ElemType a, ElemType b) {
    if(a == b) return 1;
    else return 0;
}

// 初始化列表
int InitList_Sq(SqList * L) {
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}
