#ifndef PRACTICE2_9_H_INCLUDED
#define PRACTICE2_9_H_INCLUDED
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define RANGE       20

typedef int Status;


// 1. ����λ������
typedef struct {
    int r, c;       // �Թ���r��c�е�λ��
} PosType, * PPosType;
// PosType��������

PPosType MakePosType(int r, int c);
// �������������PosType�ṹ
Status ComparePosType(PosType pos1, PosType pos2);
// �ж����������Ƿ����

// 2. �Թ�����
typedef struct {
    int m, n;
    char arr[RANGE][RANGE];     // ��λȡֵ'', '#', '@', '*'
} MazeType;
// 3. ջ����
typedef struct {
    int step;           //��ǰλ����·���ϵ����
    PosType seat;       // ��ǰ������λ��
    int di;             // ��������λ�õķ���1,2,3,4��ʾ4������
} ElemType, * PElemType;             // ջ��Ԫ������
typedef struct NodeType {
    ElemType data;
    struct NodeType * next;
} NodeType, * LinkType;     // ������ͣ�����Ӧ��ָ������
typedef struct {
    LinkType base, top;
    int size;
} Stack;                // ջ����

void InitMaze(MazeType * maze, int a[][RANGE], int row, int col);
// �����û������row�к�col�еĶ�ά���飨Ԫ��ֵΪ0��1��
// ������·maze�ĳ�ֵ���������ϱ�Ե��һȦֵ
Status MazePath(MazeType * maze, PPosType start, PPosType end);
// ����Թ�maze�У������start������end��һ��·��
// �����ڣ��򷵻�TRUE�����򷵻�FALSE
void PrintMaze(MazeType maze);
// ���Թ����ַ��ͷ������ʽ�������׼����ļ���
Status Pass(MazeType maze, PosType curpos);
//
void FootPrint(MazeType * maze, PosType curpos);
void MarkPrint(MazeType * maze, PosType curpos);
//
Status Same(PosType curpos, PosType end);
//
PosType NextPos(PosType curpos, int di);
// ��һλ���ǵ�ǰλ�õĶ���

// ��������
void Initialization(void);
void ReadCommand(char * cmd);
void Interpret(char cmd);

void CreateMaze(char * mazefile);

// ջ�Ļ�������
void InitStack(Stack * S);
    // ��ʼ������SΪ��ջ����S.top=NULL
void DestroyStack(Stack * S);
    // ����S�����ͷ���ռ�ռ�
void ClearStack(Stack * s);
    // ��S���
int StackLength(Stack S);
    // ����ջS�ĳ���S.size
Status StackEmpty(Stack S);
    // ��SΪ��ջS.top==NULL���򷵻�TRUE�����򷵻�FALSE
Status GetTop(Stack S, PElemType * e);
    // ��ջS���գ�����e����ջԪ�ز�����TRUE�����򷵻�FALSE
Status Push(Stack * S, ElemType e);
    // ������ռ�ɹ�������S��ջ�������µ�ջ��Ԫ��e��������TRUE
    // ����ջ���䣬����FALSE
Status Pop(Stack * S, PElemType * e);
    // ��ջ���գ���ɾ��S��ջ��Ԫ�ز���e������ֵ������TRUE
    // ���򷵻�FALSE
void StackTraverse(Stack S, Status(* visit)(PElemType));
    // ��ջ����ջ�����ζ�S�е�ÿ�������ú���visit

// �����ز���
Status MakeNode(LinkType * p, PElemType e);

void FreeNode(LinkType * p);
// ����������ͷ���pָ��Ľ��Ĵ洢�ռ�

LinkType Copy(LinkType p);
// ������������Ʋ�������pָ�����Ԫ�����ɵ��µĽ��

ElemType Elem(LinkType p);
// ���������������pָ�����Ԫ��ֵ

LinkType NextNode(LinkType p);
// ���������������pָ����ĺ��ָ��

PElemType MakeElem(PosType curpos, int curstep, int di);
// �������������Ԫ��

// PosType����


#endif // PRACTICE2_9_H_INCLUDED

/*
1. ջ�ĳ����������Ͷ���
ADT Stack {
    ���ݶ���D = {a(i)|a(i)�����ַ�����, i=1,2,...,n, n>=0}
    ���ݹ�ϵ��R = {<a(i-1), a(i)>|a(i-1), a(i)����D, i=1,2,...,n}

    ����������
        InitStack(&S);
            �������������һ����ջS
        DestroyStack(&S);
            ��ʼ������ջS�Ѵ���
            �������������ջS
        ClearStack(&S);
            ��ʼ������ջS�Ѵ���
            �����������S��Ϊ��ջ
        StackLength(S);
            ��ʼ������ջS�Ѵ���
            �������������ջS�ĳ���
        StackEmpty(S);
            ��ʼ������ջS�Ѵ���
            �����������SΪ�գ��򷵻�True�����򷵻�FALSE
        GetTop(S, &e);
            ��ʼ������ջS�Ѵ���
            �����������ջS��Ϊ�գ�����e����ջ��Ԫ��
        Push(&S, e);
            ��ʼ������ջS�Ѵ���
            �����������ջS��ջ�������µ�ջ��Ԫ��
        Pop(&S, &e);
            ��ʼ������ջS�Ѵ���
            ���������ɾ��ջS��ջ��Ԫ�أ�����e������ֵ
        StackTraverse(S, visit());
            ��ʼ������ջS�Ѿ�����
            �����������ջ�׵�ջ�����ζ�S�е�ÿ��Ԫ�ص��ú���visit()
}

2. �Թ��ĳ�����������

ADT Maze {
    ���ݶ���D = {a(i,j)|a(i,j)����{'','#','@','*'}, 0<=i<=m+1,0<=j<=n+1, m,n<=10}
    ���ݹ�ϵ��R = {ROW, COL}
              ROW={<a(i-1,j),a(i,j)>|a(i-1,j),a(i,j)����D��i=1,...,m+1,j=0,...,n+1}
              COL={<a(i,j-1),a(i,j)>|a(i,j-1),a(i,j)����D��i=0,...,m+1,j=1,...,n+1}

    ����������
        InitMaze(&M, a, row, col)
            ��ʼ��������ά����a[row+2][col+2]�Ѵ��ڣ� �����Ե�1������row+1�У�
                      �������Ե�1���µ�col+1�е�Ԫ������ֵ��������ֵ0��ʾͨ·����ֵ1��ʾ��·
            ��������������Թ����ַ������飬�Կհ��ַ���ʾͨ·�����ַ�'#'��ʾ·���������Թ����ܼ���һȦ�ϰ�
        MazePath(&M);
            ��ʼ�������Թ�M�ѱ���ֵ
            ������������Թ�M�д���һ��ͨ·�������¹涨�ı��Թ�M��״̬��
                      ���ַ�'*'��ʾ·���ϵ�λ�ã��ַ�'@'��ʾ����ͬ�����Թ���״̬����
        PrintMaze(M);
            ��ʼ�������Թ�M�Ѵ���
            ������������ַ���ʽ����Թ�
}
*/
