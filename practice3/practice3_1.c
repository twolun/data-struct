#include <stdio.h>
#include <stdlib.h>
#include "practice3_1.h"

HeapSpace sp;       // 所有单词所占的堆空间，初始sp.free = 0
FILE * fe;
// 创建新单词
Status NewWord(WordType * nw, Sequence cha) {
//    printf("cha size is: %s\n", cha.ch);
    int i, k;
//    printf("sp.free: %d, char.size: %d--MAXSIZE: %d\n", sp.free, cha.size, MAXSIZE);
    if(sp.free + cha.size >= MAXSIZE) return FALSE; // 存储单词的堆栈已满
    else {
        i = sp.free;
        sp.free = sp.free + cha.size;
        for(k = 0; k < cha.size; k++) {
            sp.stores[i + k] = cha.ch[k];
        }
        nw->stadr = i;
        nw->len = cha.size;
        return TRUE;
    }
    return TRUE;
}
void DestroyWord(WordType * wd) {
    if(wd) wd->stadr = wd->len = 0;
}
// 单词比较
int WordCmp(WordType wd1, WordType wd2) {
    int si, sj, k = 0;
    si = wd1.stadr;
    sj = wd2.stadr;
    while(k < wd1.len && k < wd2.len) {
        if(sp.stores[si+k] == sp.stores[sj+k]) k++;
        else if(sp.stores[si+k] < sp.stores[sj+k]) return -1;
        else return 1;
    }
    if(wd1.len == wd2.len) return 0;
    else if(wd1.len < wd2.len) return -1;
    else return 1;
}
void CopyWord(WordType * newd, WordType oldw) {
    (*newd).stadr = oldw.stadr;
    (*newd).len = oldw.len;
}
ElemType Elem(LinkType p) {
    if(p) return p->data;
}
void PrintWord(WordType wd) {
    int i;
    for(i = 0; i < wd.len; i++) {
        printf("%c", sp.stores[wd.stadr+i]);
    }
}

// 链表节点基本操作
Status MakeNode(LinkType * p, ElemType e) {
    *p = (LinkType)malloc(sizeof(NodeType));
    if(!*p) return FALSE;
    (*p)->data = e;
    (*p)->next = NULL;
    return TRUE;
}
void FreeNode(LinkType * p) {
    if(*p) DestroyWord(&((*p)->data));
}
LinkType SuccNode(LinkType p) {
    if(!p) return NULL;
    else return p->next;
}


// 链表操作
Status InitList(OrderedList * L) {
    ElemType e;
    e.stadr = e.len = 0;
    if(MakeNode(&(L->head), e)) {  // 头结点设为空节点
        L->tail = L->head;
        L->size = 0;
        return TRUE;
    } else {
        L->head = NULL;
        return FALSE;
    }
}

void DestroyList(OrderedList * L) {
    LinkType p, q;
    p = L->head;
    while(p) {
        q = p;
        p = SuccNode(p);
        FreeNode(&q);
    }
    L->head = L->tail = NULL;
    L->size = 0;
}

Status LocateElem(OrderedList L, ElemType e, LinkType * p) {
    LinkType pre;
    if(!L.head) return FALSE;
    pre = L.head;
    *p = pre->next;
    // L中的WordType也是有序排列？？？
    while(*p && WordCmp((*p)->data, e) == -1) {
        pre = *p;
        *p = SuccNode(*p);
    }
    if(*p && WordCmp((*p)->data, e) == 0) return TRUE;
    *p = pre;
    return FALSE;
}

void InsertAfter(OrderedList * L, LinkType q, LinkType s) {
    if(L->head && q && s) {
        s->next = q->next;
        q->next = s;
        if(L->tail == q) L->tail = s;
        L->size++;
    }
}

void ListCompare(OrderedList La, OrderedList Lb, EqelemList * s) {
    // 将La和Lb中共有的s.last个单词在La中的序号记录在线性表s中
    LinkType pa, pb;
    int pos;
    if(La.head && Lb.head) {
//        PrintList(La);
//        PrintList(Lb);
        pa = SuccNode(La.head);
        pb = SuccNode(Lb.head);
        (*s).last = pos = 0;
        while(pa && pb) {
            if(WordCmp(pa->data, pb->data) == 0) {
                (*s).eqelem[(*s).last++] = pos++;
                pa = SuccNode(pa);
                pb = SuccNode(pb);
            } else if(WordCmp(pa->data, pb->data) == -1) {
                pa = SuccNode(pa);
                pos++;
            } else pb = SuccNode(pb);
        }
//        printf("ListCompare eqlist.last: %d\n", (*s).last);
    }
}

void PrintNodeType(LinkType p) {
    int i;
    if(p) {
        for(i = 0; i < p->data.len; i++) {
            printf("%c", sp.stores[p->data.stadr+i]);
        }
        printf("\n");
    }
}

void ListTraverse(LinkType p, VisitFunc visit) {
    while(p) {
        visit(p);
        p = SuccNode(p);
    }
}

void PrintList(OrderedList L) {
    if(L.head) {
        printf("\n");
        ListTraverse(L.head->next, PrintNodeType);
        printf("\n");
    }
}

int ListLength(OrderedList L) {
    return L.size;
}

Status ListEmpty(OrderedList L) {
    if(L.size == 0) return TRUE;
    else return FALSE;
}


// 文本串文件类型基本操作
int feoln(FILE * f) {
    char cha = fgetc(f);
    ungetc(cha, f);
    if(cha == '\n') return TRUE;
    else return FALSE;
}


Status GetAWord(char * ss, Sequence * st) {
    char ch[100];
    int i = 0, k = 0;
    char s;
    s = ss[k];

//    // 重新生成一个完整的字符串
    ch[i] = '\n';
    char ch2[i];
    for(k = 0; k < i; k++) {
        ch2[k] = ch[k];
        st->ch[k] = ch[k];
    }
    st->size = i;
    printf("%s-", st->ch);
    return TRUE;
}
Status CheckWordsSide(char s) {
    if(s!=' ' && s!='.' && s!='-' && s!='>' && s!='\n' && s!='*' && s!='(' && s!=')' && s!='[' && s!=']' && s!='{' && s!='}') {
        if(s != '#' && ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z'))){
            return 1;
        } else return 0;
    } else return -1;
}
Status ExtractWords(FILE * f, OrderedList * ta) {
    // 从文本文件指针当前所指字符起提取一行中所有单词
    Sequence st;
    WordType nwd;
    LinkType p, s;
    char ss[100];
    int i = 0, k = 0, ok;
    st.size = 0;
    if(!InitList(ta)) return FALSE;
    // 先读取一行
    fgets(ss, 100, f);
    for(k = 0; k < strlen(ss); k++) {
        if(CheckWordsSide(ss[k]) == 1) {
            st.ch[i++] = ss[k];
            st.size++;
        }else if(CheckWordsSide(ss[k]) == -1) {
//            printf("%s--", st.ch);
            if(st.size != 0) {
                ok = NewWord(&nwd, st);
//                printf("nwd.size: %d\n", nwd.len);
                if(ok) {
                    if(!LocateElem(*ta, nwd, &p)) {
                        if(MakeNode(&s, nwd)) {

                            InsertAfter(ta, p, s);
                        }
                    }
                }
            }
            i = 0;
            st.size = 0;
        }
    }
    return TRUE;
}

Status Match(FILE * f, OrderedList pat, ResultType rs) {
    int linenum = 1, i, k;       // 当前被查询的行号
    Status failed = FALSE;
    OrderedList sa;
    EqelemList eqlist;
    Link p;

    do {
        if(!ExtractWords(f, &sa)) {
//            PrintList(sa);
            failed = TRUE; // 查询结束
        }
        else {
            ListCompare(pat, sa, &eqlist);
//            PrintList(sa);
            // 将当前行中单词和给定的查询单词进行比较

        }
//        printf("eqlist is: %d\n", eqlist.last);
        for(i = 0; i < eqlist.last; i++) {
            k = eqlist.eqelem[i];   // 该行中含有目标词汇澡第k个单词
            p = (Link)malloc(sizeof(Node));
            if(!p) return FALSE;
            p->elem = linenum;
            p->next = rs[k].next;
            rs[k].next = p;
            rs[k].count++;
//            printf("%d--", k);
        }
//        printf("match3");
        DestroyList(&sa);
        linenum++;
//        char ss[100];
//        fgets(ss, 100, f);
//        printf("%d - %s", strlen(ss), ss);
    } while(!feof(f) && !failed);
    return !failed;
}

// 主程序

void MainPractice3_1(void) {
    // 初始化sp
    sp.free = 0;
    printf("%d \n", sp.free);
    char cmd;
    sp.free = 0;
    OrderedList pt;
    char fr[20];
    ResultType rs;
    do {
        printf("entry your file's name: ");
        scanf("%s", fr);
        getchar();
        Initialization(fr);   // 输入文件名并打开文件
        InputWords(&pt);     // 输入待匹配单词并建立有序链表pt
//        PrintList(pt);
        if(!ListEmpty(pt)) {
            InitRList(rs, pt);// 初始化统计结果线性表rs
//            OutResults(rs, ListLength(pt));
            if(Match(fe, pt, rs)) {
//                printf("rs's length is: %d\n", rs[0].count);
                OutResults(rs, ListLength(pt));
            }
            else printf("memory is not enough!");
            DestroyList(&pt);    // 释放待匹配单词链表空间
        }
        // 输出是否继续的信息
        printf("Want to continue?(y/n): ");
        scanf("%c", &cmd);
        getchar();  // 把输入到输入流的字符释放掉，不影响后面代码输入
    } while(cmd != 'n' && cmd !='N');
}
void Initialization(char * fr) {
    if((fe = fopen(fr, "r")) == NULL) {
        printf("Can't open file %s .", fr);
        exit(OVERFLOW);
    }
}
void InputWords(OrderedList * pt) {
    // 连续输入单词，建立有序链表，输入两个连续的单引号为结束标志
    char cc[MAXLEN];
    int i = 0;
    ElemType nwd;
    Sequence ws;
    LinkType p,q;
    if(InitList(pt)) {
        printf("输入要检索的单词\n");
        ws.size = 0;
        while(gets(cc)) {
            if(cc[0] == '\0') break;
//            printf("%s--%d\n", cc, strlen(cc));
            for(i = 0; i < strlen(cc); i++) {
                ws.ch[i] = cc[i];
            }
//            ws.ch = cc;
            ws.size = strlen(cc);
            if(NewWord(&nwd, ws))
                if(!LocateElem(*pt, nwd, &q))
                    if(MakeNode(&p, nwd)) InsertAfter(pt, q, p);
        }
    }

}
void InitRList(ResultType rs, OrderedList pat) {
    int k;
    LinkType p;
    p = SuccNode(pat.head);
    for(k = 0; k < ListLength(pat); k++) {
        CopyWord(&(rs[k].data), Elem(p));
        rs[k].next = NULL;
        rs[k].count = 0;
        p = SuccNode(p);
//        printf("rs[k].data length: %d\n", rs[k].data.len);
    }
//    ElemType elem;
//    for(k = 0; k < ListLength(pat); k++) {
//
//        elem = rs[k].data;
//        printf("%d-", elem.len);
//    }
}

void OutResults(ResultType rslist, int n) {
    int i;
    Link p;
    for(i = 0; i < n; i++) {
        printf("The word '");
        PrintWord(rslist[i].data);
        printf("' appeared in the file %d times", rslist[i].count);
        if(rslist[i].count != 0) {
            printf("rows: ");
            p = rslist[i].next;
            while(p) {
                printf("%d,", p->elem);
                p = p->next;
            }
        }
        printf("\n");
    }
}


