#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "practice2_9.h"
int m, n;           // �Թ���ά��
int arc[20][20];    // �Թ�����
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
            start = MakePosType(1, 1);
            end = MakePosType(9, 8);
            MazePath(&maze, start, end);
            PrintMaze(maze);
            break;


    }
}

void Initialization(void) {
    char *menu[4] = {"CreateMaze-c", "MazePath-m", "PrintMaze-p", "Quit-q"};
    int num = 69;
    int i;
    // ϵͳ��ʼ��
    system("cls");      // ����������
    // ����˵�
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
    // 1. ��ȡ��һ�У���ȡά�� m, n
    fgets(s1, 20, fp);
    strcpy(s2, s1 + 1);
    m = atoi(s1);
    n = atoi(s2);
    printf("m: %d, n: %d \n", m, n);

    // ����һ�У����һ���������1ΪΧ��
//    for(j = 0; j < n + 2; j++) {
//        arc[0][j] = 1;
//        arc[m + 1][j] = 1;
//    }
    // ���ɾ���
    count = 0;
    while(fgets(s1, 20, fp) != NULL) {
        // ��һ��ΪΧ��
//        arc[count][0] = 1;
        for(j = 0; j < n; j++) {
            k = (int)(s1[2*j]-'0');
            arc[count][j] = k;
        }
        // ���һ��ΪΧ��
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
    // 1. �����Թ�������û����Ҫ�жϵ�������
    int i, j;
    char k;
    // 1. ���ɵ�һ���ϰ���
    for(j = 0; j < col + 2; j++) {
        maze->arr[0][j] = '#';
    }

    for(i = 1; i < row + 1; i++) {
        // 2. ��һ�еĵ�һ��Ϊ�ϰ���
        maze->arr[i][0] = '#';
        for(j = 1; j < col + 1; j++) {
            if(a[i - 1][j - 1] == 1) k = '#';
            else k = ' ';
//            printf("%c ", k);
            maze->arr[i][j] = k;
        }
        // ÿһ�е����һ��Ϊ�ϰ���
        maze->arr[i][col + 1] = '#';
    }

    // �������һ���ϰ���
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
    // �����ǰcurpos��maze��Ӧλ�õ�ֵ��Ϊ-1���Ҳ�Ϊ'#', ���ʾ����ͨ��
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
    // �߹��Ľڵ���'-1'��ʶ
    maze->arr[curpos.r][curpos.c]= '^';
}

void MarkPrint(MazeType * maze, PosType curpos) {
    // ��ͨ�Ľڵ���'@'������ͬ
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
    // ���Թ�maze�д��ڴ����start����end��ͨ���������һ������ջ
    // ��ջ�׵�ջ��Ϊ����� �����ڵ�·����������TRUE���������FALSE
    Stack S;
    PosType curpos;
    int curstep = 1;
    Status found = FALSE;
    PElemType e;
    InitStack(&S);
    curpos = *start;              // �趨��ǰλ��Ϊ���λ��
    do {
        if(Pass(*maze, curpos)) {
            // ��ǰλ�ÿ���ͨ��������δ���ߵ�����ͨ���������㼣
            FootPrint(maze, curpos);
            e = MakeElem(curpos, curstep, 1);
            Push(&S, *e);
            if(Same(curpos, *end)) found = TRUE;
            else {
                curpos = NextPos(curpos, 1);        // ��һλ���ǵ�ǰλ�õĶ���
                curstep++;                          // ̽����һ��
            }
        } else {
            if(!StackEmpty(S)) {
                Pop(&S, &e);
                while(e->di == 4 && !StackEmpty(S)) {
                    MarkPrint(maze, e->seat);
                    Pop(&S, &e);
                    curstep--;
                }
                if(e->di < 4) {
                    e->di++;
                    Push(&S, *e);        // ����һ������̽��
                    curpos = NextPos(e->seat, e->di);
                }
            }
        }

        printf("curpos is r: %d, c: %d\n", curpos.r, curpos.c);
        printf("stack empty is: %d, found is: %d", StackEmpty(S), found);
    } while(!StackEmpty(S) && !found);
    return found;
}

// ջ��������

void InitStack(Stack * S) {
    LinkType ss = (LinkType)malloc(m * n * sizeof(NodeType));
    if(!ss) exit(OVERFLOW);
    S->top = S->base = ss;
    S->size = 0;
}

Status StackEmpty(Stack S) {
    if(S.base == S.top) return TRUE;
    else return FALSE;
}

Status Push(Stack * S, ElemType e) {
//    LinkType pn = (LinkType)malloc(sizeof(NodeType));
//    if(!pn) exit(OVERFLOW);
//    pn->data = e;
//    pn->next = NULL;
    S->top->data = e;
    S->top = S->top + 1;
    return TRUE;
}
Status Pop(Stack * S, PElemType * e){
    // ���ȡֵ�е�Ѿ���
    (*e) = &((S->top - 1)->data);
    S->top = S->top - 1;
    return TRUE;
}
PElemType MakeElem(PosType curpos, int curstep, int di) {
    PElemType pe;
    pe = (PElemType)malloc(sizeof(ElemType));
    if(!pe) exit(OVERFLOW);
    pe->seat = curpos;
    pe->step = curstep;
    pe->di = di;
    return pe;
}


// PosType ����
PPosType MakePosType(int r, int c) {
    PPosType pos = (PPosType)malloc(sizeof(PosType));
    if(!pos) exit(OVERFLOW);
    pos->r = r;
    pos->c = c;
    return pos;
}

