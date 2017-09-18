#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

// 1. ��� SqList ��������
void printa(SqList L);
int equal(ElemType a, ElemType b);
// 2. �㷨2.3���������Ա�
Status ListInsert_Sq(SqList * L, int i, ElemType e);

// 3. �㷨2.4��ɾ�����Ա�
Status ListDelete_Sq(SqList * L, int i, ElemType * e);

// 4. �㷨2.5����λԪ��
int LocateElem_Sq(SqList L, ElemType e, Status (* compare)(ElemType, ElemType));

// 5. �㷨2.6��˳���ϲ�
void MergeList_Sq(SqList La, SqList Lb, SqList * Lc);

// �������
void printl(LinkList LL);

// �����̬����
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

    // difference_SL����
    int S;
    difference_SL(space, &S);
    printsl(space);
}

void difference_SL(SNode * space, int * S) {
    // �������뼯��A, B��Ԫ�أ���һά����space�н���
    // SΪͷָ�룬space[0].cur Ϊ��ͷָ��
//    SLinkList spacee;
    int r;                      // ָ��������ָ��
    int m, n, j, i, b, p, k, F;                   // A, BԪ�صĸ���
    InitSpace_SL(space);
//    S = Malloc_SL(space);       // ����ͷ��㣬����0
    *S = 0;
    F = space[0].cur;             // �����һ�����ָ��
//    printf("space[1] = %d\n", space[0].cur);

//    printf("S is: %d", S);

    r = i = space[*S].cur;                      // rָ�����Ľ��
    printf("\nA��Ԫ�صĸ�����");
    scanf("%d", &m);
    printf("\nB��Ԫ�صĸ�����");
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
    }      // 0 ָ���һ��ͷ���
    // ����ѭ������ǰ �ڴ汻�������һ�Σ�����Ҫ�ͷŵ�
//    Free_SL(space, i);
//    r = i - 1;
    printf("r is: %d\n", r);
    space[r].cur = 0;       // �������
//
    // ��������B��Ԫ�أ�������������룬������ɾ��
    for(j = 1; j<= n; j++) {
        scanf("%d", &b);
        p = *S;
        k = F;      // kָ���һ�����
        while(k != space[r].cur && space[k].data != b) {
            p = k;
            k = space[k].cur;
//            printf("k is: %d\n", k);
        }

        if(k == space[r].cur) { // ��ǰ�б����� ��Ԫ��
            i = Malloc_SL(space);
            printf("i now is: %d\n", i);
            space[i].data = b;
            space[i].cur = space[r].cur;        //��ǰ���ָ��ָ���ָ��
            space[r].cur = i;                   // �����ָ��ָ��ǰָ��
        } else {
            space[p].cur = space[k].cur;        // ���������½�ɾ���ڵ��ǰһ���ڵ��curָ��Ҫɾ���ڵ��cur
                                                // Ϊʲô����Free_SL()��ִ����
            Free_SL(space, k);
            if(r == k) r = p;
        }
    }
    // ���ڷ����ڴ��space[0].cur�Ѿ��ı䣬��Щ����ָ���һ��
//    space[0].cur = F;
    printf("space[1].data is: %d\n", space[3].cur);
    i = 0;
    while(i < 8) {
        printf("space[%d].cur is: %d---space[%d].data is: %d\n ", i, space[i].cur, i, space[i].data);
        ++i;
    }

//    printsl(space);
}

// �ھ�̬�����ж�λԪ��
int LocateElem_SL(SLinkList space, ElemType e) {
    int i = space[0].cur;
    while(i && space[i].data != e) i = space[i].cur;
    return i;
}

// ���տռ�
void Free_SL(SNode * space, int k) {
//    space[k - 1].cur = space[k].cur;wq    21`bnmkl;
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

// ����洢�ռ�
Status Malloc_SL(SNode * space) {
    int i = space[0].cur;
    if(space[0].cur) space[0].cur = space[i].cur;
    return i;
}

// ��ʼ������ռ�Ϊһ������
void InitSpace_SL(SNode * space) {
    // ��һά����space�и���������һ���������� space[0].curΪͷָ��
    // '0'��ʾ��ָ��
    int i;
    for(i = 0; i < MAXSIZE; i ++) {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0;
}

// �����̬����
void printsl(SNode * space) {
    // �ӵ�һ����㿪ʼ��������Ե�ͷ���
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
//    // ��ʼ������LL
//    InitList_Ln(linkL);
//    while(i < ALEN) {
//        lnode.data = arrA[i];
//        lnode.next = NULL;
//        ListAdd_Ln(lnode, linkL);
//        i++;
//    }
//    printl(linkL);

    // ��ȡ�����i��Ԫ�ز���
//    ElemType ei;
//    GetElem_Ln(linkL, 3, &ei);
//    printf("ei is: %d\n", ei);

    // ����Ԫ�ز���
//    int ok;
//    ok = ListInsert_Ln(linkL, 5, 12);
//    printf("---%d---\n", ok);
    // ɾ��Ԫ�ز���
//    ElemType e;
//    ListDelete_Ln(linkL, 5, &e);
//    printf("delete e is: %d\n", e);
//    printl(linkL);
    // ������λ����������
//    LinkList linkB;
//    InitList_Ln(linkB);
//    CreateList_Ln(&linkB, 5);
//    printl(linkB);
//    printf("%d\n", linkB->data);

    // �鲢�㷨����
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

    // ���������������ǵ����ϲ�
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
    // ����
//    Trevele_MergeList_LN(linkL, Lb);
//    printl(Lb);
//    Order_IntersectList_LN(linkL, Lb, Lc);
//    printl(Lc);
    CLinkList cLL = (CLinkList)malloc(sizeof(CLNode));
    CLNode cnode;
    // ��ʼ������LL
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

// ���ѭ���б�
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

// ��һ�������ֳ�����ѭ������
Status ListDivideInfo3(CLinkList L, CLinkList s1, CLinkList s2, CLinkList s3) {
    CLinkList p, q, pt1, pt2, pt3;
    p = L->next;
    pt1 = s1;       // �����ĸ
    pt2 = s2;       // �������
    pt3 = s3;       // ��������ַ�

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
    // ����ѭ������
    pt1->next = s1;
    pt2->next = s2;
    pt3->next = s3;
}

// �󽻼���������
Status Order_IntersectList_LN(LinkList La, LinkList Lb, LinkList Lc) {
    LinkList pa, pb, pc, qa, qb, qc, pt, ptmp;
    pa = La;
    pb = Lb;
    pc = Lc;
    qa = pa;        // ����La��ǰ��
    qb = pb;        // ����Lb��ǰ��
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
    pc->next = NULL;    // �������ǲ�����ģ�����Ҫfree�����ܴ��ڵ�fqg
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

// �ϲ���������
Status Trevele_MergeList_LN(LinkList La, LinkList Lb) {
    LinkList pa, pb, qa, qb;
    pa = La;
    pa = pa;    // ����pa��ǰ��
    pa = La->next;
    pb = Lb;
    qb = pb;    // ����pb����
    pb = Lb->next;
    La->next = NULL;        // ����Ԫ�ش����La��
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
    // ��ͷ���
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

// �鲢�㷨
Status MergeList_Ln(LinkList La, LinkList Lb, LinkList * Lc) {
    LNode * pa = La->next;
    LNode * pb = Lb->next;
    LNode * pc = *Lc;
//    printf("%d", pc->data);
    while(pa && pb) {
        if(pa->data <= pb->data) {
            pc->next = pa;
//            pc = pa;
            pc = pc->next;      // �����᲻��������һ��
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pc->next;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;        // ����ʣ������������Ҫ����ָ�븳ֵ������
    (*Lc)->data = La->data + Lb->data;
    free(Lb);                   // �ͷŵ�Lb��ͷ���
    return OK;
}

// ������������
Status CreateList_Ln(LinkList * LL, int n) {
     //��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ����Ա�
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

// ɾ��Ԫ�ز���
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
    free(q);        // �������ռ�õ��ڴ�
    return OK;
}
// ���������Ԫ��e
Status ListInsert_Lc(CLinkList LL, int i, char e) {
    // �ڴ�ͷ��������LL�е�i��λ�ò���Ԫ��e
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

// ���������Ԫ��e
Status ListInsert_Ln(LinkList LL, int i, ElemType e) {
    // �ڴ�ͷ��������LL�е�i��λ�ò���Ԫ��e
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

// ��ȡ�����е�i��Ԫ��
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

// ���������node
Status ListAdd_Lc(CLNode node, CLinkList LL) {
    CLNode * pnew;
    CLNode * scan = LL->next;
    pnew = (CLNode *)malloc(sizeof(CLNode));
    if(pnew == NULL) exit(OVERFLOW);
    *pnew = node;
    pnew->next = NULL;

    if(scan == NULL) {
        LL->next = pnew;
    }           //���ڵ�һ���ڵ�
    else {
        while(scan->next != NULL) {
            scan = scan->next;
        }
        scan->next = pnew;
    }
    LL->data++;
    return OK;
}
// ���������node
Status ListAdd_Ln(LNode node, LinkList LL) {
    LNode * pnew;
    LNode * scan = LL->next;
    pnew = (LNode *)malloc(sizeof(LNode));
    if(pnew == NULL) exit(OVERFLOW);
    *pnew = node;
    pnew->next = NULL;

    if(scan == NULL) {
        LL->next = pnew;
    }           //���ڵ�һ���ڵ�
    else {
        while(scan->next != NULL) {
            scan = scan->next;
        }
        scan->next = pnew;
    }
    LL->data++;
    return OK;
}

// ��ʼ������
int InitList_Lc(CLinkList LL) {
    // LLָ��ͷ��㣬ͷ���ָ����Ϊ�գ�ͷ�����������������
    LL->next = NULL;
    LL->data = '0';
    return OK;
}
// ��ʼ������
int InitList_Ln(LinkList LL) {
    // LLָ��ͷ��㣬ͷ���ָ����Ϊ�գ�ͷ�����������������
    LL->next = NULL;
    LL->data = 0;
    return OK;
}

// �������
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
// �������
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
//    ListInsert_Sq(&sqL, 2, 34);         // �㷨2.3 �������
//    ElemType e;
//    ListDelete_Sq(&sqL, 2, &e);
//    printf("%d\n", e);
    // Ԫ�ض�λ����
//    int ei;
//    ei = LocateElem_Sq(sqL, 77, equal);
//    printf("ei= %d\n", ei);
//    printa(sqL);
    // ���Ա�ϲ��㷨����
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
// ��ת����
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

// �㷨2.6
void MergeList_Sq(SqList La, SqList Lb, SqList * Lc) {
    // ��֪˳�����Ա�La��Lb��ֵ�ǵݼ�����
    // �鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݹ�����
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

// �㷨2.5
int LocateElem_Sq(SqList L, ElemType e, Status (* compare)(ElemType, ElemType)) {
    // ���ҵ�e���򷵻�����L�е�λ�򣬷��򷵻�0
    int i = 1;
    int * p = L.elem;
    while(i <= L.length && !(*compare)(*p++, e)) i++;
    if(i <= L.length) return i;
    else return 0;
}


// �㷨2.4
Status ListDelete_Sq(SqList * L, int i, ElemType * e) {
    // �����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
    // i�ĺϷ�ֵ 1<=i<=L.length
    ElemType * p, * q;
    if(i < 1 || i > L->length) return ERROR;
    p = &(L->elem[i - 1]);
    *e = *p;                  // pָ���ֵ����e
    q = L->elem + L->length - 1;
    for(++p; p <= q; p++) *(p - 1) = *p;
    --L->length;
    return OK;
}

// �㷨2.3
Status ListInsert_Sq(SqList * L, int i, ElemType e) {
    // ��˳�����Ա�L�еڸ�λ��֮ǰ�����µ�Ԫ��e
    // i: 1<=i<= L.length + 1
    int * newbase;
    ElemType * p,  * q;        //
    if(i < 1 || i > L->length + 1) return ERROR;
    if(L->length >= L->listsize) {
        newbase = (ElemType * ) realloc(L->elem, (L->listsize + LIST_INCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L->elem = newbase;              // L->elem ָ���µ�ַ
        L->listsize += LIST_INCREMENT;
    }
    q = &(L->elem[i - 1]);              // Ҫ����Ԫ�ص���λ��
    for(p = &(L->elem[L->length - 1]); p >= q; --p) *(p + 1) = *p;      // Ԫ������ƶ�
    *q = e;
    ++L->length;                        // ����1

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

// ��ʼ���б�
int InitList_Sq(SqList * L) {
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}
