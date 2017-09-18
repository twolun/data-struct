#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define status int
#define TRUE   1
#define FALSE  0

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

// 1. ����Ԫ�����ͣ�������ͣ�ָ������
typedef char ElemType;
typedef struct NodeType {
    ElemType data;
    struct NodeType * next;
} NodeType, * LinkType;     // ������ͣ�ָ������

LinkType MakeNode(ElemType e) {
    // ������pָ��ģ�����Ԫ��Ϊe�����Ϊ�յĽ�㣬������True
    // ������ʧ�ܣ��򷵻�False
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
    // �������ɺ�ָ��p��ָ�ڵ���ֵͬԪ�ص��½�㲢����
    // ������ռ�ʧ�ܣ��򷵻ؿ�ָ�룬�½���ָ����ΪNULL
    LinkType s = (LinkType)malloc(sizeof(NodeType));
    if(!s) return NULL;
    s->data = p->data;
    s->next = NULL;
    return s;
}
ElemType Elem(LinkType p) {
    // ��ָ��p!=NULL���򷵻�p��ָ��������Ԫ�أ����򷵻�'#'
    if(p==NULL) return '#';
    else return p->data;
}
LinkType SuccNode(LinkType p) {
    // ��ָ��p!=NULL���򷵻�ָ��p��ָ���ĺ��Ԫ�ص�ָ��
    // ���򷵻�NULL
    if(p!=NULL) return p->next;
    else return NULL;
}

// 2. ������������
typedef struct {
    LinkType head, tail;        // �ֱ�ָ�������ͷ����β���
    int size;                   // ָʾ����ǰ�ĳ���
} OrderedList;

status InitList(OrderedList * L) {
    // ��ʼͷ���β���Ԫ��ֵΪ��
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
    // ͷ���β���ȫ��ΪNULL, size = 0;
    // ͬʱҪ���������ϵ����нڵ�
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
    // ��������L�ĳ���
    return L.size;
}

status ListEmpty(OrderedList L) {
    // �ж������Ƿ�Ϊ�գ�size=0��Ϊ��
    if(!L.size) return TRUE;
    else return FALSE;
}

LinkType GetElem(OrderedList L, int pos) {
    // ���������posλ�õ�Ԫ��
    int k = 1;
    LinkType p;
    if(!L.head || pos<1 || pos>L.size) return NULL;
    else if(pos == L.size) return L.tail;
    else {
        p = L.head->next;           // ���˵�ͷ���
        while(p && k < pos) {
            p = SuccNode(p);
            ++k;
        }
        return p;
    }
}

LinkType LocateElem(OrderedList * L, ElemType e) {
    // qָ��L�е�һ��ֵΪe�Ľ���λ�ã�������ָ���һ������e����ǰ��

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
    // L.head��ʼ��ָ��һ���ս�㣬������ս�㣬�ǲ��ᱻ���ʵ���
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

// 2. ���������������Ͷ������򼯺�
typedef OrderedList OrderedSet;

// ���������ж�Сд��ĸ
//status islower(char a) {
//    if(a > 'a' && a < 'z') return TRUE;
//    else return FALSE;
//}

status WriteSetElem(LinkType p) {
    printf(",");
    WriteElem(p);
    return TRUE;
}

// ʵ�ִ�ӡ����
void PrintSet(OrderedSet T) {
    LinkType p = GetElem(T, 1);
    printf("[");
    if(p){WriteElem(p); p = SuccNode(p);}
    ListTraverse(p, WriteSetElem);
    printf("]\n");

}
// 1. ��������
status CreateSet(OrderedSet * T, char * s) {
    int i;
    LinkType p, q;
    if(InitList(T)){        // 1. ����ռ�T
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

// 2. ���ټ���
void DestroySet(OrderedSet * T) {
    DestroyList(T);
}

// 2. ���ϲ���
void Union(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    // S1.head S2.head != NULL
    LinkType p1, p2;
    ElemType c1, c2;
    if(InitList(T)) { // ��ʼ������T
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
            // ���û�б����꣬�򵥶�����
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

// 3. ����
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

// 4. �
void Difference(OrderedSet * T, OrderedSet S1, OrderedSet S2) {
    // S1��S2�Ĳ��������S1�У���������S2��
    LinkType p1, p2;
    ElemType c1, c2;
    if(InitList(T)) {
        p1 = GetElem(S1, 1);
        p2 = GetElem(S2, 1);
        while(p1 && p2) {
            c1 = Elem(p1);
            c2 = Elem(p2);
            if(c1 < c2) {
                // c1 < c2 ˵��c1��c2���ȣ����Բ��뼯��
                Append(T, Copy(p1));
                p1 = SuccNode(p1);
            } else if(c1 > c2) p2 = SuccNode(p2);       // c1 > c2 ��ʱ����Ҫ��p2����ƶ�����Ϊǰ�˿϶�������<=��
            else {  // ��ȵ�ʱ�����������ж����ڣ�����Ҫ���뼯�ϣ�ȫ�������ƶ�
                p1 = SuccNode(p1);
                p2 = SuccNode(p2);
            }
        }
        // ������S1�У�������Ԫ�أ���Ҫ���뵽T�У�S2������Ԫ�أ���������
        while(p1) {
            Append(T, Copy(p1));
            p1 = SuccNode(p1);
        }
    }
}

// ��������ȫ�ֱ���
OrderedSet Set1, Set2, Set3;

void Initialization() {
    char *menu[6] = {
        "MakeSet-1", "MakeSet-2", "Union-u", "Intersection-i", "Difference-d", "Quit-q"
    };
    int num = 101;
    int i;
//    char (*menu)[] = {"MakeSet-1", "MakeSet-2", "Union-u", "Intersection-i", "Difference-d", "Quit-q"};
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
// ������
status LocateElemPos(OrderedList L, ElemType e, LinkType * p) {
    // qָ��L�е�һ��ֵΪe�Ľ���λ�ã�������ָ���һ������e����ǰ��

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


















