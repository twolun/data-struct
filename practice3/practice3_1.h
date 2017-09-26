#ifndef PRACTICE3_1_H_INCLUDED
#define PRACTICE3_1_H_INCLUDED
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2

// ȫ�ֱ���
#define MAXSIZE     10000   // �ַ��ռ���������
#define MAXLEN      20      // ���ʵ���󳤶�
#define MAXNUM      16      // һ���е��������ٸ�
typedef int Status;

typedef struct {
    char    stores[MAXSIZE];       // ���е�����ռ�Ķѿռ�
    int     free;
} HeapSpace;


// 2. ��������
typedef struct {
    int stadr;      // ���������ַ��ڶѿռ����ʼλ��
    int len;        // ���ʵĳ���
} WordType;
typedef struct {
    char ch[MAXLEN];    // ���ɵ��ʵ��ַ�����
    int size;
} Sequence;
// ��������
Status NewWord(WordType * nw, Sequence cha);
// ��cha�������ַ���������һ���µĵ��ʣ�������TRUE
// ���ѿռ䲻���ڷ���һ�����ʣ��򷵻�FALSE
void DestroyWord(WordType * wd);
// ���ٵ���wd�Ľṹ����wd.stadr=wd.len=0
void CopyWord(WordType * newd, WordType oldw);
// ����һ����oldw��ͬ�ĵ��ʣ�newd.stadr = oldw.stadr��
// newd.len = oldw.len
int WordCmp(WordType wd1, WordType wd2);
// ��wd1<wd2���򷵻�-1����wd1==wd2���򷵻�0�����򷵻�1
void PrintWord(WordType wd);
// �ڼ�����ն�����ʾ����wd

// 3. �����ڵ�����
typedef WordType ElemType;      // Ԫ������
typedef struct NodeType {
    ElemType data;
    struct NodeType * next;
} NodeType, * LinkType;         // ������ͣ�ָ������

// ��������
Status MakeNode(LinkType * p, ElemType e);
// ������pָ�������Ԫ��e�����Ϊ�յĽ�㣬������TRUE
// ������ʧ�ܣ��򷵻�FALSE
void FreeNode(LinkType * p);
// �ͷ�p��ָ���ռ䣬����DestroyWord(p->data)
ElemType Elem(LinkType p);
// ��p!=NULL���򷵻�ָ��p��ָ�ڵ������Ԫ�أ����ʣ����򷵻�'#'
LinkType SuccNode(LinkType p);
// ��p!=NULL���򷵻�ָ��p�Ľ��ĺ��Ԫ�ص�ָ�룬���򷵻�NULL

// ��������������ͷ��β����ָ��ͱ�������
// ������ͷ��㣬ͷ����������û��ʵ������
typedef struct {
    LinkType head, tail;    // �ֱ�ָ�������ͷ����β���
    int size;               // ����ǰ�ĳ���
} OrderedList;              // ������������
typedef struct {
    int eqelem[MAXNUM];
    int last;
} EqelemList;               // ��¼ƥ��ɹ��ĵ�����Ŀ��ʻ��е�λ��
// ��������
Status InitList(OrderedList * L);
// ����һ����ͷ���Ŀյ���������L��������TRUE;
// ������ռ�ʧ�ܣ�����L.head=NULL,������FALSE
void DestroyList(OrderedList * L);
// ������������L�����ͷ�������ÿ���ڵ���ռ�ռ�
Status ListEmpty(OrderedList L);
// ��L�����ڣ���LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
int ListLength(OrderedList L);
// ��������L�ĳ��ȣ�L�����ڣ�����Ϊ0
LinkType GetElemPos(OrderedList L, int pos);
// ���������е�pos��Ԫ�صĵ�ַ
Status LocateElem(OrderedList L, ElemType e, LinkType * p);
// �������L�����ұ���Ԫ��e����pָ��L�е�һ��ֵΪe�Ľ��λ��
// ������TRUE������pָ���һ������e��Ԫ�ص�ǰ����λ�ã�������FALSE
void InsertAfter(OrderedList * L, LinkType q, LinkType p);
// ���Ѵ�����������L�У�q��ָʾ�Ľڵ�֮�����ָ��p�����
void ListCompare(OrderedList La, OrderedList Lb, EqelemList * s);
// ��La��Lb�й��е�s.size��������La�е���ż�¼�����Ա�s��
void TraverseList(LinkType p, Status(*visit)());
void PrintNodeType(LinkType p);
void PrintList(OrderedList L);

typedef void (* VisitFunc)(LinkType p);


// �����ı����ļ�����
typedef struct Node {
    int elem;           // �����Ե������ļ��е��г�
    struct Node * next;
} Node, * Link;

typedef struct {
    WordType data;          // �����Եĵ���
    int      count;         // ���ļ��г��ֵĴ���
    Link     next;          // ��¼�����к������ͷָ��
} HeadNode;

typedef HeadNode ResultType[MAXNUM];

Status GetAWord(char * ss, Sequence * st);
// ���ļ�ָ����ָ�ַ�����ȡһ�����ʵ��ַ�����st
Status ExtractWords(FILE * f, OrderedList * ta);
// ��ȡ�ļ�ָ����ָ�������е��ʣ������ɵ��ʵ������ta
// ͬʱ����TRUE��֮���ļ�ָ��ָ����һ�еĵ�һ���ַ�
// ���ռ䲻�����������򷵻�FALSE
Status Match(FILE * f, OrderedList pat, ResultType rs);
// �ļ��򿪣��ļ�ָ��ָ���ļ��еĵ�һ���ַ�
// patΪ�������д���ѯ���ʵ������rsΪ��ѯ���

int feoln(FILE * f);
// �ж��ļ��н���
void InitRList(ResultType rs, OrderedList pat);
void Initialization(char * fr);
void OutResults(ResultType rs, int n);


#endif // PRACTICE3_1_H_INCLUDED
