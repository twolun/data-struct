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


// 1. 坐标位置类型
typedef struct {
    int r, c;       // 迷宫中r行c列的位置
} PosType, * PPosType;
// PosType基本操作

PPosType MakePosType(int r, int c);
// 操作结果：生成PosType结构
Status ComparePosType(PosType pos1, PosType pos2);
// 判断两个坐标是否相等

// 2. 迷宫类型
typedef struct {
    int m, n;
    char arr[RANGE][RANGE];     // 各位取值'', '#', '@', '*'
} MazeType;
// 3. 栈类型
typedef struct {
    int step;           //当前位置在路径上的序号
    PosType seat;       // 当前的坐标位置
    int di;             // 往下坐标位置的方向，1,2,3,4表示4个方向
} ElemType, * PElemType;             // 栈的元素类型
typedef struct NodeType {
    ElemType data;
    struct NodeType * next;
} NodeType, * LinkType;     // 结点类型，结点对应的指针类型
typedef struct {
    LinkType base, top;
    int size;
} Stack;                // 栈类型

void InitMaze(MazeType * maze, int a[][RANGE], int row, int col);
// 按照用户输入的row行和col列的二维数组（元素值为0或1）
// 设置迷路maze的初值，包括加上边缘的一圈值
Status MazePath(MazeType * maze, PPosType start, PPosType end);
// 求解迷宫maze中，从入口start到出口end的一条路径
// 若存在，则返回TRUE，否则返回FALSE
void PrintMaze(MazeType maze);
// 将迷宫以字符型方阵的形式输出到标准输出文件上
Status Pass(MazeType maze, PosType curpos);
//
void FootPrint(MazeType * maze, PosType curpos);
void MarkPrint(MazeType * maze, PosType curpos);
//
Status Same(PosType curpos, PosType end);
//
PosType NextPos(PosType curpos, int di);
// 下一位置是当前位置的东邻

// 基础定义
void Initialization(void);
void ReadCommand(char * cmd);
void Interpret(char cmd);

void CreateMaze(char * mazefile);

// 栈的基本操作
void InitStack(Stack * S);
    // 初始化，设S为空栈，即S.top=NULL
void DestroyStack(Stack * S);
    // 销毁S，并释放所占空间
void ClearStack(Stack * s);
    // 将S清空
int StackLength(Stack S);
    // 返回栈S的长度S.size
Status StackEmpty(Stack S);
    // 若S为空栈S.top==NULL，则返回TRUE，否则返回FALSE
Status GetTop(Stack S, PElemType * e);
    // 若栈S不空，则以e带回栈元素并返回TRUE，否则返回FALSE
Status Push(Stack * S, ElemType e);
    // 若分配空间成功，则在S的栈顶插入新的栈顶元素e，并返回TRUE
    // 否则栈不变，返回FALSE
Status Pop(Stack * S, PElemType e);
    // 若栈不空，则删除S的栈顶元素并以e带回其值，返回TRUE
    // 否则返回FALSE
void StackTraverse(Stack S, Status(* visit)(PElemType));
    // 从栈顶到栈底依次对S中的每个结点调用函数visit

void PrintStack(Stack S);
    // 从栈底开始输出

// 结点相关操作
Status MakeNode(LinkType * p, ElemType e);

void FreeNode(LinkType * p);
// 操作结果：释放由p指向的结点的存储空间

LinkType Copy(LinkType p);
// 操作结果：复制并返回由p指向结点的元素生成的新的结点

ElemType Elem(LinkType p);
// 操作结果：返回由p指向结点的元素值

LinkType NextNode(LinkType p);
// 操作结果：返回由p指向结点的后继指针

ElemType MakeElem(PosType curpos, int curstep, int di);
// 操作结果：生成元素

// PosType操作


#endif // PRACTICE2_9_H_INCLUDED

/*
1. 栈的抽象数据类型定义
ADT Stack {
    数据对象：D = {a(i)|a(i)属于字符集合, i=1,2,...,n, n>=0}
    数据关系：R = {<a(i-1), a(i)>|a(i-1), a(i)属于D, i=1,2,...,n}

    基本操作：
        InitStack(&S);
            操作结果：构造一个空栈S
        DestroyStack(&S);
            初始条件：栈S已存在
            操作结果：销毁栈S
        ClearStack(&S);
            初始条件：栈S已存在
            操作结果：将S清为空栈
        StackLength(S);
            初始条件：栈S已存在
            操作结果：返回栈S的长度
        StackEmpty(S);
            初始条件：栈S已存在
            操作结果：若S为空，则返回True，否则返回FALSE
        GetTop(S, &e);
            初始条件：栈S已存在
            操作结果：若栈S不为空，则以e返回栈顶元素
        Push(&S, e);
            初始条件：栈S已存在
            操作结果：在栈S的栈顶插入新的栈顶元素
        Pop(&S, &e);
            初始条件：栈S已存在
            操作结果：删除栈S的栈顶元素，并以e返回其值
        StackTraverse(S, visit());
            初始条件：栈S已经存在
            操作结果：从栈底到栈顶依次对S中的每个元素调用函数visit()
}

2. 迷宫的抽象数据类型

ADT Maze {
    数据对象：D = {a(i,j)|a(i,j)属于{'','#','@','*'}, 0<=i<=m+1,0<=j<=n+1, m,n<=10}
    数据关系：R = {ROW, COL}
              ROW={<a(i-1,j),a(i,j)>|a(i-1,j),a(i,j)属于D，i=1,...,m+1,j=0,...,n+1}
              COL={<a(i,j-1),a(i,j)>|a(i,j-1),a(i,j)属于D，i=0,...,m+1,j=1,...,n+1}

    基本操作：
        InitMaze(&M, a, row, col)
            初始条件：二维数组a[row+2][col+2]已存在， 其中自第1行至第row+1行，
                      第行中自第1列致第col+1列的元素已有值，并且以值0表示通路，以值1表示障路
            操作结果：构成迷宫的字符型数组，以空白字符表示通路，以字符'#'表示路碍，并在迷宫四周加上一圈障碍
        MazePath(&M);
            初始条件：迷宫M已被赋值
            操作结果：若迷宫M中存在一条通路，则按如下规定改变迷宫M的状态，
                      以字符'*'表示路径上的位置，字符'@'表示死胡同否则迷宫的状态不变
        PrintMaze(M);
            初始条件：迷宫M已存在
            操作结果：以字符形式输出迷宫
}
*/
