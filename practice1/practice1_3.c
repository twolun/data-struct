#include <stdio.h>
#include <stdlib.h>
#include "practice1_3.h"

// ��������ȫ�ֱ���
OrderedSet Set1, Set2, Set3;
char inputs[20];

void MainPractice1_3(void) {
    char cmd;
    Initialization();
    do {
        ReadCommand(&cmd);
        Interpret(cmd);
    } while(cmd != 'q' && cmd != 'Q');
}
void Interpret(char cmd) {
    switch(cmd) {
        case '1':
            scanf("%s", inputs);
            CreateSet(&Set1, inputs);
            PrintSet(Set1);
            break;
        case '2':
            scanf("%s", inputs);
            CreateSet(&Set2, inputs);
            PrintSet(Set2);
            break;
        case 'u':
        case 'U':
            Union(&Set3, Set1, Set2);
            PrintRes(cmd);
            break;
        case 'i':
        case 'I':
            InterSection(&Set3, Set1, Set2);
            PrintRes(cmd);
            break;
        case 'd':
        case 'D':
            Difference(&Set3, Set1, Set2);
            PrintRes(cmd);
            break;

    }
}
void Initialization() {
    char *menu[6] = {"MakeSet-1", "MakeSet-2", "Union-u", "Intersection-i", "Difference-d", "Quit-q"};
    int num = 101;
    int i;
    // ϵͳ��ʼ��
    system("cls");      // ����������
    // ����˵�
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n*   ");
    for(i = 0; i < 6; i++) printf("%-16s", menu[i]);
    printf("*\n");
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n\n\n");
    printf("                    Operation: \n\n");
    printf("                    Set1:[] \n\n");
    printf("                    Set2:[] \n\n");
    printf("\n\n\n\n");

    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n*   ");
    printf(" Enter a operation code: 1, 2, u, i, d OR q");
    printf("*\n");
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n");
}

void ReadCommand(char * cmd) {
    do {
        *cmd = getchar();
    } while(*cmd != '1' && *cmd != '2' && *cmd != 'u' && *cmd != 'U' && *cmd != 'i' && *cmd != 'I' && *cmd != 'd' && *cmd != 'D' && *cmd != 'q' && *cmd != 'Q');
}

void PrintRes(char cmd) {
    printf("%16s%c\n", "Operation: ", cmd);
    printf("%16s", "Set1: ");
    PrintSet(Set1);
    printf("%16s", "Set2: ");
    PrintSet(Set2);
    printf("%16s", "���������");
    PrintSet(Set3);
    DestroySet(&Set3);
}
// ���ϲ�������
Status CreateSet(OrderedSet * T, char * s) {
    int i;
    LinkType p, q;
    // 1. ��ʼ������
    if(InitList(T)) {
        // 2. �������ɹ������нڵ㴴���������뵽������
        for(i = 0; i < strlen(s); i++) {
            if(islower(s[i]) && !LocateElem(*T, s[i], &q)){    // 3. �ж�s[i]�����Ѵ��������У�����s[i]Ҫ�����λ��
//                printf("%c--", s[i]);
                if(MakeNode(&p, s[i])) InsertAfter(T, q, p);
            }
        }
    }
    return OK;
}

// ����printSet  ����������û�д����ɹ�
void PrintSet(OrderedSet T) {
    LinkType p;
    // ��λ��һ��Ԫ�ص�λ��
    p = GetElemPos(T, 1);
    printf("[");
    if(p) {WriteElem(p); p = NextNode(p);}
    ListTraverse(p, WriteSetElem);
    printf("]\n");

}

void WriteSetElem(LinkType p) {
    printf(",");
    WriteElem(p);
}

void DestroySet(OrderedSet * T) {
    DestroyList(T);
}
// ��������
void Union(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    // ���������е�ȫ��Ԫ��
    LinkType p1, p2;
    if(InitList(T)) {
        p1 = S1.head;
        p2 = S2.head;
        while(p1 && p2) {
            if(p1->data <= p2->data) {
                Append(T, Copy(p1));
                if(p1->data == p2->data) {
                    p2 = NextNode(p2);
                }
                p1 = NextNode(p1);
            } else if(p1->data > p2->data) {
                Append(T, Copy(p2));
                p2 = NextNode(p2);
            }
        }
        // �������µ�����
        while(p1) {
            Append(T, Copy(p1));
            p1 = NextNode(p1);
        }
        while(p2) {
            Append(T, Copy(p2));
            p2 = NextNode(p2);
        }
    }
}

// ��������
void InterSection(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    LinkType p1, p2;
    if(InitList(T)) {
        p1 = S1.head;
        p2 = S2.head;
        while(p1 && p2) {
            if(p1->data < p2->data) {
                p1 = NextNode(p1);
            } else if(p1->data > p2->data) {
                p2 = NextNode(p2);
            } else {
                Append(T, Copy(p1));
                p1 = NextNode(p1);
                p2 = NextNode(p2);
            }
        }
    }
    // ���ù������������µ�����
}

// A��B�Ĳ
void Difference(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    LinkType p1, p2;
    if(InitList(T)) {
        p1 = S1.head;
        p2 = S2.head;
        while(p1 && p2) {
            if(p1->data < p2->data) {
                Append(T, Copy(p1));
                p1 = NextNode(p1);
            } else if(p1->data > p2->data){
                p2 = NextNode(p2);
            } else {
                p1 = NextNode(p1);
                p2 = NextNode(p2);
            }
        }
        while(p1) {
            Append(T, Copy(p1));
            p1 = NextNode(p1);
        }
    }
}


// �����������
Status InitList(OrderedList * L) {
    L = (OrderedList *)malloc(sizeof(OrderedList));
    if(!L) exit(OVERFLOW);   // ����ռ�ʧ�ܣ��˳�
    L->head = L->tail = NULL;
    L->size = 0;
    return OK;
}
Status LocateElem(OrderedList L, ElemType e, LinkType * p) {
    LinkType pre, nowp;
    if(!L.head) {
        *p = NULL;
        return FALSE;
    }
    pre = L.head;
//    nowp = pre->next;
    nowp = L.head;
    while(nowp && nowp->data < e) {
        pre = nowp;
        nowp = NextNode(nowp);
    }
    if(nowp && e == nowp->data) {
        *p = nowp;
        return OK;
    } else {
        *p = pre;
        return FALSE;
    }
}
Status InsertAfter(OrderedList * L, LinkType q, LinkType p) {
    // 3�������1. L->head������ʱ������һ������������ʱ
    //          2. q == L->headʱ����Ҫ���뵽������ǰ��ʱ
    //          3. �������
    if(!L->head) {
        L->head = L->tail = p;
    // ������һ�仰�������Ӹ���һ�죬���ˣ����ܲ��ˣ��ҵ����⣬���Ǻ������oiuyt
    } else if(q==L->head && p->data < L->head->data){
        p->next = q;
        L->head = p;
    } else {
        p->next = q->next;
        q->next = p;
    }
    L->size++;
    if(q == L->tail) L->tail = p;
    return OK;
}
Status Append(OrderedList * L, LinkType s) {
    if(!L->head) {
        L->head = s;
    } else {
        L->tail->next = s;
    }
    L->tail = s;
    L->size++;
    return OK;
}
void WriteElem(LinkType p) {
    printf("%c", p->data);
}

void ListTraverse(LinkType p, void(* visit)(LinkType)) {
    while(p) {
        visit(p);
        p = NextNode(p);
    }
}


LinkType GetElemPos(OrderedList L, int pos) {
    int i;
    LinkType p;
    if(!L.head || pos<1 || pos>L.size) return NULL;
    i = 1;
    p = L.head;
    while(p && i < pos) {
        p = NextNode(p);
        ++i;
    }
    return p;
}

void DestroyList(OrderedList * L) {
    LinkType p, q;
    p = q = L->head;
    while(p) {
        q = p;
        p = NextNode(p);
        free(q);
    }
    L->head = L->tail = NULL;
}


// Node�ڵ�Ļ�������
Status MakeNode(LinkType * p, ElemType e) {
    *p = (LinkType)malloc(sizeof(NodeType));
    if(!*p) exit(OVERFLOW);
    (*p)->data = e;
    (*p)->next = NULL;
    return OK;
}

LinkType NextNode(LinkType p) {
    if(!p) return p;
    return p->next;
}

LinkType Copy(LinkType p) {
    // ����Һ��ĺ���ѽ��
    LinkType q;
    MakeNode(&q, p->data);
    return q;
}
