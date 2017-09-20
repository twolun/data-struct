#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "practice2_9.h"
int m, n;           // 迷宫的维度
int arc[20][20];    // 迷宫数组
MazeType maze;

void MainPractice2_9(void) {
    char cmd;
    Initialization();
    do {
        ReadCommand(&cmd);
        Interpret(cmd);
    }while(cmd != 'q' && cmd != 'Q');
}

void Interpret(char cmd) {
    char filename[20];
    PPosType start, end;
    int r, c, ok;
    switch(cmd) {
        case 'c':
        case 'C':
            printf("Entry the maze file: ");
            scanf("%s", filename);
            CreateMaze(filename);
            InitMaze(&maze, arc, m, n);
            PrintMaze(maze);
            break;
        case 'm':
        case 'M':
            printf("Please enter the entry: ");
            scanf("%d,%d", &r,&c);
            start = MakePosType(r, c);
            printf("Please enter the out: ");
            scanf("%d,%d", &r,&c);
            end = MakePosType(r, c);
            ok = MazePath(&maze, start, end);
            if(ok) printf("The pass is been found, enter the 'p' to print it: ");
            else printf("The pass is not tong..., please change the entry and end.\n");
//            PrintMaze(maze);
            break;
        case 'p':
        case 'P':
            PrintMaze(maze);
            break;


    }
}

void Initialization(void) {
    char *menu[4] = {"CreateMaze-c", "MazePath-m", "PrintMaze-p", "Quit-q"};
    int num = 69;
    int i;
    // 系统初始化
    system("cls");      // 清屏？？？
    // 输出菜单
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n*   ");
    for(i = 0; i < 4; i++) printf("%-16s", menu[i]);
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
    printf(" Enter a operation code: c, p, p OR q");
    printf("*\n");
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n");
}

void ReadCommand(char * cmd) {
    do {
        *cmd = getchar();
    }while(*cmd != 'c' && *cmd != 'C' && *cmd != 'm' && *cmd != 'M' && *cmd != 'p' && *cmd != 'P' && *cmd != 'q' && *cmd != 'Q');
}

void CreateMaze(char * mazefile) {
    char s1[20], s2[20];
    int i = 0, j = 0, k, count = 1;
    FILE * fp;
    if((fp = fopen(mazefile, "r")) == NULL) {
        printf("Can't open %s\n", mazefile);
        exit(1);
    }
    // 1. 读取第一行，获取维度 m, n
    fgets(s1, 20, fp);
    strcpy(s2, s1 + 1);
    m = atoi(s1);
    n = atoi(s2);
    printf("m: %d, n: %d \n", m, n);

    // 填充第一行，最后一行数据填充1为围栏
//    for(j = 0; j < n + 2; j++) {
//        arc[0][j] = 1;
//        arc[m + 1][j] = 1;
//    }
    // 生成矩阵
    count = 0;
    while(fgets(s1, 20, fp) != NULL) {
        // 第一列为围栏
//        arc[count][0] = 1;
        for(j = 0; j < n; j++) {
            k = (int)(s1[2*j]-'0');
            arc[count][j] = k;
        }
        // 最后一列为围栏
//        arc[count][j+1] = 1;
        count++;
    }
    for(i = 0; i < m; i++) {
        for(j = 0; j< n; j++) {
            printf("%d ", arc[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void InitMaze(MazeType * maze, int a[][RANGE], int row, int col) {
    // 1. 生成迷宫矩阵，有没有需要判断的条件？
    int i, j;
    char k;
    // 1. 生成第一行障碍物
    for(j = 0; j < col + 2; j++) {
        maze->arr[0][j] = '#';
    }

    for(i = 1; i < row + 1; i++) {
        // 2. 第一行的第一列为障碍物
        maze->arr[i][0] = '#';
        for(j = 1; j < col + 1; j++) {
            if(a[i - 1][j - 1] == 1) k = '#';
            else k = ' ';
//            printf("%c ", k);
            maze->arr[i][j] = k;
        }
        // 每一行的最后一列为障碍物
        maze->arr[i][col + 1] = '#';
    }

    // 生成最后一行障碍物
    for(j = 0; j < col + 2; j++) {
        maze->arr[row + 1][j] = '#';
    }
    maze->m = row;
    maze->n = col;
}

// PriintMaze
void PrintMaze(MazeType maze) {
    int i, j;
    printf("\n The maze is:\n");
    for(i = 0; i < maze.m + 2; i++) {
        for(j = 0; j < maze.n + 2; j++) {
            printf("%c ", maze.arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
Status Pass(MazeType maze, PosType curpos){
    // 如果当前curpos在maze对应位置的值不为-1，且不为'#', 则表示可以通过
    if(maze.arr[curpos.r][curpos.c] == ' ') {
        return TRUE;
    }
    return FALSE;
}
Status Same(PosType curpos, PosType end) {
    if(curpos.r == end.r && curpos.c == end.c) return TRUE;
    return FALSE;
}

void FootPrint(MazeType * maze, PosType curpos) {
    // 走过的节点用'-1'标识
    maze->arr[curpos.r][curpos.c]= '*';
}

void MarkPrint(MazeType * maze, PosType curpos) {
    // 不通的节点用'@'，死胡同
    maze->arr[curpos.r][curpos.c] = '@';
}

PosType NextPos(PosType curpos, int di) {
    PosType nextpos;
    switch(di) {
        case 1:                         //
            nextpos.r = curpos.r;
            nextpos.c = curpos.c + 1;
            break;
        case 2:
            nextpos.r = curpos.r + 1;
            nextpos.c = curpos.c;
            break;
        case 3:
            nextpos.r = curpos.r;
            nextpos.c = curpos.c - 1;
            break;
        case 4:
            nextpos.r = curpos.r - 1;
            nextpos.c = curpos.c;
            break;
    }
    return nextpos;
}

Status MazePath(MazeType * maze, PPosType start, PPosType end) {
    // 若迷宫maze中存在从入口start到出end的通道，则求得一条放在栈
    // 从栈底到栈顶为从入口 到出口的路径，并返回TRUE，否则瓜田FALSE
    Stack S;
    PosType curpos;
    int curstep = 1;
    Status found = FALSE;
    ElemType e;
    InitStack(&S);
    curpos = *start;              // 设定当前位置为入口位置
    do {
        if(Pass(*maze, curpos)) {
            // 当前位置可以通过，即是未曾走到过的通道块留下足迹
            FootPrint(maze, curpos);
            e = MakeElem(curpos, curstep, 1);
            Push(&S, e);
            if(Same(curpos, *end)) found = TRUE;
            else {
                curpos = NextPos(curpos, 1);        // 下一位置是当前位置的东邻
                curstep++;                          // 探索下一步
            }
        } else {
            if(!StackEmpty(S)) {
                Pop(&S, &e);
                while(e.di == 4 && !StackEmpty(S)) {
                    MarkPrint(maze, e.seat);
                    Pop(&S, &e);
                    curstep--;
                }
                if(e.di < 4) {
                    e.di++;
                    Push(&S, e);        // 换下一个方向探索
                    curpos = NextPos(e.seat, e.di);
                }
            }
        }

//        printf("curpos is r: %d, c: %d\n", curpos.r, curpos.c);
//        printf("stack empty is: %d, found is: %d", StackEmpty(S), found);
    } while(!StackEmpty(S) && !found);
    if(found) {
        printf("\nThe pass is: ");
        PrintStack(S);
    }
    return found;
}

// 栈基本操作

void InitStack(Stack * S) {
//    LinkType ss = (LinkType)malloc(m * n * sizeof(NodeType));
    LinkType ss = (LinkType)malloc(sizeof(NodeType));
    if(!ss) exit(OVERFLOW);
    S->top = S->base = ss;
    S->size = 0;
}

Status StackEmpty(Stack S) {
    if(S.base == S.top) return TRUE;
    else return FALSE;
}

Status Push(Stack * S, ElemType e) {
    LinkType ss;
    if(MakeNode(&ss, e)) {
        ss->next = S->top;
        S->top = ss;
        S->size++;
    }
//    S->top->data = e;
//    S->top = S->top + 1;
    return TRUE;
}
Status Pop(Stack * S, PElemType e){
    // 这个取值有点费劲了
//    (*e) = &((S->top - 1)->data);
//    S->top = S->top - 1;
    *e = S->top->data;
    S->top = S->top->next;
    S->size--;
    return TRUE;
}
void PrintStack(Stack S) {
    // 怎么从栈底开始输出，要倒一次吧
    Stack st;
    ElemType e;
    InitStack(&st);

    while(S.size) {
        Pop(&S, &e);
        Push(&st, e);
    }
    while(st.size) {
        Pop(&st, &e);
        printf("(%d,%d,%d)", e.seat.r, e.seat.c, e.di);
    }
    printf("\n");

}


Status MakeNode(LinkType * p, ElemType e) {
    *p = (LinkType)malloc(sizeof(NodeType));
    if(!*p) exit(OVERFLOW);
    (*p)->data = e;
    (*p)->next = NULL;
    return TRUE;
}

ElemType MakeElem(PosType curpos, int curstep, int di) {
    PElemType pe;
    pe = (PElemType)malloc(sizeof(ElemType));
    if(!pe) exit(OVERFLOW);
    pe->seat = curpos;
    pe->step = curstep;
    pe->di = di;
    return *pe;
}


// PosType 操作
PPosType MakePosType(int r, int c) {
    PPosType pos = (PPosType)malloc(sizeof(PosType));
    if(!pos) exit(OVERFLOW);
    pos->r = r;
    pos->c = c;
    return pos;
}

