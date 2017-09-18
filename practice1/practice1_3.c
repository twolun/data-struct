#include <stdio.h>
#include <stdlib.h>
#include "practice1_3.h"

// 定义三个全局变量
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
    // 系统初始化
    system("cls");      // 清屏？？？
    // 输出菜单
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
    printf("%16s", "操作结果：");
    PrintSet(Set3);
    DestroySet(&Set3);
}
// 集合操作定义
Status CreateSet(OrderedSet * T, char * s) {
    int i;
    LinkType p, q;
    // 1. 初始化链表
    if(InitList(T)) {
        // 2. 链表创建成功，进行节点创建，将插入到链表中
        for(i = 0; i < strlen(s); i++) {
            if(islower(s[i]) && !LocateElem(*T, s[i], &q)){    // 3. 判断s[i]不是已存在链表中，定义s[i]要插入的位置
//                printf("%c--", s[i]);
                if(MakeNode(&p, s[i])) InsertAfter(T, q, p);
            }
        }
    }
    return OK;
}

// 定义printSet  看看集合有没有创建成功
void PrintSet(OrderedSet T) {
    LinkType p;
    // 定位第一个元素的位置
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
// 并集操作
void Union(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    // 两个集合中的全部元素
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
        // 处理余下的数据
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

// 交集操作
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
    // 不用管两个集合余下的问题
}

// A与B的差集
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


// 链表操作定义
Status InitList(OrderedList * L) {
    L = (OrderedList *)malloc(sizeof(OrderedList));
    if(!L) exit(OVERFLOW);   // 分配空间失败，退出
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
    // 3种情况：1. L->head不存在时，即第一个结点插入链表时
    //          2. q == L->head时，即要插入到链表最前端时
    //          3. 其它情况
    if(!L->head) {
        L->head = L->tail = p;
    // 就下面一句话，让老子搞了一天，操了，不能操了，找到问题，还是很满足的oiuyt
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


// Node节点的基本操作
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
    // 你把我害的好若呀，
    LinkType q;
    MakeNode(&q, p->data);
    return q;
}
