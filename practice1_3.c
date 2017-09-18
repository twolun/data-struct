#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define status int
#define TRUE   1
#define FALSE  0

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

// 1. 定义元素类型，结点类型，指针类型
typedef char ElemType;
typedef struct NodeType {
    ElemType data;
    struct NodeType * next;
} NodeType, * LinkType;     // 结点类型，指针类型

LinkType MakeNode(ElemType e) {
    // 分配由p指向的，数据元素为e、后继为空的结点，并返回True
    // 若分配失败，则返回False
    LinkType q;
    q = (LinkType)malloc(sizeof(NodeType));
    if(!q) return NULL;
    q->data = e;
    q->next = NULL;
    return q;
}

void FreeNode(LinkType p) {
    free(p);
}

LinkType Copy(LinkType p) {
    // 复制生成和指针p所指节点有同值元素的新结点并返回
    // 若分配空间失败，则返回空指针，新结点的指针域为NULL
    LinkType s = (LinkType)malloc(sizeof(NodeType));
    if(!s) return NULL;
    s->data = p->data;
    s->next = NULL;
    return s;
}
ElemType Elem(LinkType p) {
    // 若指针p!=NULL，则返回p所指结点的数据元素，否则返回'#'
    if(p==NULL) return '#';
    else return p->data;
}
LinkType SuccNode(LinkType p) {
    // 若指针p!=NULL，则返回指向p所指结点的后继元素的指针
    // 否则返回NULL
    if(p!=NULL) return p->next;
    else return NULL;
}

// 2. 定义有序链表
typedef struct {
    LinkType head, tail;        // 分别指向链表的头结点和尾结点
    int size;                   // 指示链表当前的长度
} OrderedList;

status InitList(OrderedList * L) {
    // 初始头结点尾结点元素值为空
    LinkType h = MakeNode(' ');
    if(h) {
//        printf("%c--%c---------------", h.data, h.data);
        L->tail = L->head = h;
        L->size = 0;
        return TRUE;
    } else {
        L->head = NULL;
        return FALSE;
    }
}

void DestroyList(OrderedList * L) {
    // 头结点尾结点全部为NULL, size = 0;
    // 同时要销毁链接上的所有节点
    LinkType p = L->head->next;
    LinkType q;
    while(p) {
        q = p;
        p = SuccNode(p);
        free(q);
    }
    L->tail = L->head = NULL;
    L->size = 0;
}

int ListLength(OrderedList L) {
    // 返回链表L的长度
    return L.size;
}

status ListEmpty(OrderedList L) {
    // 判断链表是否为空，size=0即为空
    if(!L.size) return TRUE;
    else return FALSE;
}

LinkType GetElem(OrderedList L, int pos) {
    // 返回链表第pos位置的元素
    int k = 1;
    LinkType p;
    if(!L.head || pos<1 || pos>L.size) return NULL;
    else if(pos == L.size) return L.tail;
    else {
        p = L.head->next;           // 过滤掉头结点
        while(p && k < pos) {
            p = SuccNode(p);
            ++k;
        }
        return p;
    }
}

LinkType LocateElem(OrderedList * L, ElemType e) {
    // q指向L中第一个值为e的结点的位置，不存在指向第一个大于e结点的前驱

    LinkType pre, p;
    if(L->head) {
        pre = L->head;
        p = pre->next;
        while(p && p->data < e){
            pre = p;
            p = SuccNode(p);
        }
        if(p && p->data == e) return p;
        else {
            p = pre;
            return p;
        }
    } else return NULL;
}

status Append(OrderedList * L, LinkType s) {
    // L.head初始化指向一个空结点，而这个空结点，是不会被访问到的
    if(L->head && s) {
        if(L->head != L->tail) {
            L->tail->next = s;
        } else {
            L->head->next = s;
        }
        L->tail = s;
        L->size++;
        return TRUE;
    } else return FALSE;
}
status InsertAfter(OrderedList * L, LinkType q, LinkType s) {

    if(L->head && q && s) {
        s->next = q->next;
        q->next = s;
        if(L->tail == q) L->tail = s;
        L->size++;
        return TRUE;
    } else return FALSE;
}

void WriteElem(LinkType p) {
    ElemType e = Elem(p);
    if(e != '#') printf("%c", e);
}

void ListTraverse(LinkType p, status(* visit)(LinkType)) {
    while(p) {
        visit(p);
        p = p->next;
    }
}

// 2. 利用有序链表类型定义有序集合
typedef OrderedList OrderedSet;

// 辅助函数判定小写字母
//status islower(char a) {
//    if(a > 'a' && a < 'z') return TRUE;
//    else return FALSE;
//}

status WriteSetElem(LinkType p) {
    printf(",");
    WriteElem(p);
    return TRUE;
}

// 实现打印集合
void PrintSet(OrderedSet T) {
    LinkType p = GetElem(T, 1);
    printf("[");
    if(p){WriteElem(p); p = SuccNode(p);}
    ListTraverse(p, WriteSetElem);
    printf("]\n");

}
// 1. 创建集合
status CreateSet(OrderedSet * T, char * s) {
    int i;
    LinkType p, q;
    if(InitList(T)){        // 1. 构造空集T
        for(i=0; i<strlen(s); i++) {
//            printf("%c--", s[i]);
            p = LocateElem(T, s[i]);
            if(islower(s[i]) && (p->data != s[i])) {
                q = MakeNode(s[i]);
                if(q) InsertAfter(T, p, q);
            }
        }
        return TRUE;
    } else return FALSE;
}

// 2. 销毁集合
void DestroySet(OrderedSet * T) {
    DestroyList(T);
}

// 2. 集合并集
void Union(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    // S1.head S2.head != NULL
    LinkType p1, p2;
    ElemType c1, c2;
    if(InitList(T)) { // 初始化集合T
        if(S1.head && S2.head) {
            p1 = GetElem(S1, 1);
            p2 = GetElem(S2, 1);
            while(p1 && p2) {
                c1 = Elem(p1);
                c2 = Elem(p2);
                if(c1 <= c2) {
                    Append(T, Copy(p1));
                    p1 = SuccNode(p1);
                    if(c1 == c2) p2 = SuccNode(p2);
                } else {
                    Append(T, Copy(p2));
                    p2 = SuccNode(p2);
                }
            }
            // 如果没有遍历完，则单独遍历
            while(p1) {
                Append(T, Copy(p1));
                p1 = SuccNode(p1);
            }
            while(p2) {
                Append(T, Copy(p2));
                p2 = SuccNode(p2);
            }
        }
    }
}

// 3. 交集
void InterSection(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    LinkType p1, p2;
    ElemType c1, c2;
    if(InitList(T)) {
        p1 = GetElem(S1, 1);
        p2 = GetElem(S2, 1);
        while(p1 && p2) {
            c1 = Elem(p1);
            c2 = Elem(p2);
            while(p2 && (c1 != c2)) {
                p2 = SuccNode(p2);
                c2 = Elem(p2);
            }
            if(c2 != '#') {
                Append(T, Copy(p1));
            }
            p1 = SuccNode(p1);
            p2 = GetElem(S2, 1);

        }

    } else T->head = NULL;
}

// 4. 差集
void Difference(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    // S1与S2的差集，存在于S1中，不存在于S2中
    LinkType p1, p2;
    ElemType c1, c2;
    if(InitList(T)) {
        p1 = GetElem(S1, 1);
        p2 = GetElem(S2, 1);
        while(p1 && p2) {
            c1 = Elem(p1);
            c2 = Elem(p2);
            if(c1 < c2) {
                // c1 < c2 说明c1与c2不等，可以插入集合
                Append(T, Copy(p1));
                p1 = SuccNode(p1);
            } else if(c1 > c2) p2 = SuccNode(p2);       // c1 > c2 的时候，需要将p2向后移动，因为前端肯定不会再<=了
            else {  // 相等的时候，两个集合中都存在，不需要插入集合，全部往后移动
                p1 = SuccNode(p1);
                p2 = SuccNode(p2);
            }
        }
        // 最后，如果S1中，还余有元素，则要插入到T中，S2中余有元素，无需在意
        while(p1) {
            Append(T, Copy(p1));
            p1 = SuccNode(p1);
        }
    }
}

// 定义三个全局变量
OrderedSet Set1, Set2, Set3;

void Initialization() {
    char *menu[6] = {
        "MakeSet-1", "MakeSet-2", "Union-u", "Intersection-i", "Difference-d", "Quit-q"
    };
    int num = 101;
    int i;
//    char (*menu)[] = {"MakeSet-1", "MakeSet-2", "Union-u", "Intersection-i", "Difference-d", "Quit-q"};
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
void Interpret(char cmd) {
    char ss[10];
    switch(cmd) {
        case '1':
            scanf("%s", ss);
            CreateSet(&Set1, ss);
            PrintSet(Set1);
            break;
        case '2':
            scanf("%s", ss);
            CreateSet(&Set2, ss);
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
// 主程序
status LocateElemPos(OrderedList L, ElemType e, LinkType * p) {
    // q指向L中第一个值为e的结点的位置，不存在指向第一个大于e结点的前驱

    LinkType pre;
    if(L.head) {
        pre = L.head;
        *p = pre->next;
        while(*p && (*p)->data < e){
            pre = *p;
            *p = SuccNode(*p);
        }
        if(*p && (*p)->data == e) return TRUE;
        else {
            *p = pre;
        }
    } else return FALSE;
}
void practice1_3(void) {
    char cmd;
    Initialization();
    OrderedSet T;
    LinkType s;
    CreateSet(&T, "abcdefaafe");
    LocateElemPos(T, 'd', &s);
    printf("%c--", s->data);
//    do {
//       ReadCommand(&cmd);
//       Interpret(cmd);
//    }while(cmd != 'q' && cmd !='Q');
}


















