#ifndef PRACTICE3_1_H_INCLUDED
#define PRACTICE3_1_H_INCLUDED
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2

// 全局变量
#define MAXSIZE     10000   // 字符空间的最大容量
#define MAXLEN      20      // 单词的最大长度
#define MAXNUM      16      // 一行中单词最多多少个
typedef int Status;

typedef struct {
    char    stores[MAXSIZE];       // 所有单词所占的堆空间
    int     free;
} HeapSpace;


// 2. 单词类型
typedef struct {
    int stadr;      // 单词所含字符在堆空间的起始位置
    int len;        // 单词的长度
} WordType;
typedef struct {
    char ch[MAXLEN];    // 生成单词的字符序列
    int size;
} Sequence;
// 基本操作
Status NewWord(WordType * nw, Sequence cha);
// 由cha给定的字符序列生成一个新的单词，并返回TRUE
// 若堆空间不足于分配一个单词，则返回FALSE
void DestroyWord(WordType * wd);
// 销毁单词wd的结构，令wd.stadr=wd.len=0
void CopyWord(WordType * newd, WordType oldw);
// 生成一个和oldw相同的单词（newd.stadr = oldw.stadr）
// newd.len = oldw.len
int WordCmp(WordType wd1, WordType wd2);
// 若wd1<wd2，则返回-1，若wd1==wd2，则返回0；否则返回1
void PrintWord(WordType wd);
// 在计算机终端上显示单词wd

// 3. 有序表节点类型
typedef WordType ElemType;      // 元素类型
typedef struct NodeType {
    ElemType data;
    struct NodeType * next;
} NodeType, * LinkType;         // 结点类型，指针类型

// 基本操作
Status MakeNode(LinkType * p, ElemType e);
// 分配由p指向的数据元素e，后继为空的结点，并返回TRUE
// 若分配失败，则返回FALSE
void FreeNode(LinkType * p);
// 释放p所指结点空间，首先DestroyWord(p->data)
ElemType Elem(LinkType p);
// 若p!=NULL，则返回指向p所指节点的数据元素，单词，否则返回'#'
LinkType SuccNode(LinkType p);
// 若p!=NULL，则返回指向p的结点的后继元素的指针，否则返回NULL

// 定义有序链表，设头，尾两个指针和表长数据域，
// 并附设头结点，头结点的数据域没有实在意义
typedef struct {
    LinkType head, tail;    // 分别指向链表的头结点和尾结点
    int size;               // 链表当前的长度
} OrderedList;              // 有序链表类型
typedef struct {
    int eqelem[MAXNUM];
    int last;
} EqelemList;               // 记录匹配成功的单词在目标词汇中的位置
// 基本操作
Status InitList(OrderedList * L);
// 构造一个带头结点的空的有序链表L，并返回TRUE;
// 若分配空间失败，则令L.head=NULL,并返回FALSE
void DestroyList(OrderedList * L);
// 销毁有序链表L，并释放链表中每个节点所占空间
Status ListEmpty(OrderedList L);
// 若L不存在，或L为空表，则返回TRUE，否则返回FALSE
int ListLength(OrderedList L);
// 返回链表L的长度，L不存在，长度为0
LinkType GetElemPos(OrderedList L, int pos);
// 返回链表中第pos个元素的地址
Status LocateElem(OrderedList L, ElemType e, LinkType * p);
// 若有序表L存在且表中元素e，则p指向L中第一个值为e的结点位置
// 并返回TRUE，否则p指向第一个大于e的元素的前驱的位置，并返回FALSE
void InsertAfter(OrderedList * L, LinkType q, LinkType p);
// 在已存在有序链表L中，q所指示的节点之后插入指针p所结点
void ListCompare(OrderedList La, OrderedList Lb, EqelemList * s);
// 将La和Lb中共有的s.size个单词在La中的序号记录在线性表s中
void TraverseList(LinkType p, Status(*visit)());
void PrintNodeType(LinkType p);
void PrintList(OrderedList L);

typedef void (* VisitFunc)(LinkType p);


// 单词文本串文件类型
typedef struct Node {
    int elem;           // 被测试单词在文件中的行呈
    struct Node * next;
} Node, * Link;

typedef struct {
    WordType data;          // 被测试的单词
    int      count;         // 在文件中出现的次数
    Link     next;          // 记录所有行号链表的头指针
} HeadNode;

typedef HeadNode ResultType[MAXNUM];

Status GetAWord(char * ss, Sequence * st);
// 从文件指针所指字符起提取一个单词的字符序列st
Status ExtractWords(FILE * f, OrderedList * ta);
// 提取文件指针所指行中所有单词，并构成单词的有序表ta
// 同时返回TRUE，之后文件指针指向下一行的第一个字符
// 若空间不足生成链表，则返回FALSE
Status Match(FILE * f, OrderedList pat, ResultType rs);
// 文件打开，文件指针指向文件中的第一个字符
// pat为包含所有待查询单词的有序表，rs为查询结果

int feoln(FILE * f);
// 判定文件行结束
void InitRList(ResultType rs, OrderedList pat);
void Initialization(char * fr);
void OutResults(ResultType rs, int n);


#endif // PRACTICE3_1_H_INCLUDED
