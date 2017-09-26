#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "practice4_3.h"

// 定义全局使用广义表
GList Hlink;
void MainPractice4_3(void) {
    char cmd, cmds[20];
//    while((cmd = getchar())) {
//        putchar((cmd));
//    }
//    return FALSE;
    InitGList(&Hlink);
    Initialization();       // 初始化
//    do {
//        ReadCommand(&cmd);  // 读入一个操作命令符
//        Interpret(cmd);     // 解释执行操作命令符
//        getchar();
//        while(getchar()) getchar();          // 怎么这个地方要把缓冲区里的换行符给干掉
//    } while(cmd != 'q' && cmd != 'Q');
    do {
    printf("请输入广义表字符串：");
    CreateList(&Hlink);
    Traverse_GL(Hlink);
    printf("\n请输入广义表操作命令串：");
    scanf("%s", cmds);
    Decompose(Hlink, cmds);
    }while(cmd != 'q' && cmd != 'Q');
}

void Traverse_GL(GList Ls) {
    // 遍历广义表，以书写形式输出到终端
    if(!Ls) printf("( )");
    else {
        if(Ls->tag == ATOM) printf("%c", GL_Elem(Ls));    // 输出单土原子
        else {
            printf("(");
            while(Ls != NULL) {
                Traverse_GL(GetHead(Ls));           // 遍历广义表中其中的一个子表
                Ls = GetTail(Ls);
                if(Ls) printf(",");
            }
            printf(")");
        }
    }

}

char GL_Elem(GList Ls) {
    if(Ls && Ls->tag == ATOM) return Ls->data;
    else return ' ';
}
GList GetHead(GList Ls) {
    if(Ls) return Ls->ptr.hp;
    else return NULL;
}
GList GetTail(GList Ls) {
    if(Ls) return Ls->ptr.tp;
    else return NULL;
}
void InitGList(GList * Ls) {
    *Ls = NULL;
}
Status CreateList(GList * Ls) {
    // 本算法识别一个待输入的广义表字符串，其中单字母（不论大小写）都表示原子，
    // 建相应的存储结构，Ls为指向第一个结点的指针。若输入的字符串为“()”，
    // 则该广义表为空表，即Ls = NULL
    // 先把屏幕上的输出清掉
    char ch;
    getAChar(&ch);       // 拾取第一个合法字符
    if(ch != '(') return ERROR;         // 广义表的第一个字符只能是"("
    else return crtLtBU(Ls);
}
Status GListEmpty(GList Ls) {
    if(Ls != NULL) return FALSE;
    else return TRUE;
}
void DestroyGList(GList * Ls) {
    GList hp, tp;
    // 妈的，这也要递归销毁呀
    if(*Ls) {
        if((*Ls)->tag == ATOM) free(*Ls);
        else {
            while(*Ls != NULL) {
                hp = GetHead(*Ls);
                DestroyGList(&hp);
                tp = GetTail(*Ls);
                *Ls = tp;
            }
        }
    }
}
Status crtLtBU(GList * Ls) {
    // 本算法识别一个待输入的从字符'('或','之后的广义表字符串
    // 并建立相应的存储结构
    char ch;
    getAChar(&ch);              // 拾取第一个合法的字符
    if(ch == '\n') return TRUE;
    if(ch == ' ') {              // 空表的情况
        (*Ls) = NULL;
        getAChar(&ch);          // 拾取下一个合法的字符，应该是')'
        if(ch != ')') return ERROR;
    } else {
        // 当输入的广义表非空
        *Ls = (GList)malloc(sizeof(GLNode));
        (*Ls)->tag = LIST;       // 链表标记
        if(isalpha(ch)) {           // 表头为单原子，即是直接是字母，而非(, ...
            (*Ls)->ptr.hp = (GList)malloc(sizeof(GLNode));
            (*Ls)->ptr.hp->tag = ATOM;
            (*Ls)->ptr.hp->data = ch;
        } else if(ch == '('){   // 表头为广义表
            // 继续执行crtLtBU
            crtLtBU(&((*Ls)->ptr.hp));
        } else return ERROR;        // 其他字符均为错误情况
        getAChar(&ch);          // 拾取下一个合法字符
        if(ch == ')') (*Ls)->ptr.tp = NULL;
        else if(ch == ',') crtLtBU(&((*Ls)->ptr.tp));          // 表尾不为空
        else return ERROR;
    }
    return TRUE;
}
void getAChar(char * ch) {
    scanf("%c", ch);
//    printf("%c ", *ch);
}
void Decompose(GList Ls, char * cmds) {
    // 解释命令串str，对广义表Hlink执行“求表头”或“求表尾”操作
    // 并输出每一步操作后求得的文印有表头或表尾的字符串
    GList p = Ls;
    int i, n = strlen(cmds);
    for(i = 0; i < n; i++) {
        if(!p) printf("The LIST is a EmptyList!\n");
        else {
            if(cmds[i] == 'h') {
                p = GetHead(p);
                printf("The ListHead is ");
            } else if(cmds[i] == 't') {
                p = GetTail(p);
                printf("The ListTail is ");
            }
            Traverse_GL(p);
            printf("\n");
        }
    }
}
void Initialization(void) {
    char *menu[3] = {"CreatGList-c", "Decompost-d", "Quit-q"};
    int num = 69;
    int i;
    // 系统初始化
    system("cls");      // 清屏？？？
    // 输出菜单
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n*   ");
    for(i = 0; i < 3; i++) printf("%-16s", menu[i]);
    printf("*\n");
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n\n\n");
    printf("                    Operation: \n\n");
//    printf("                    Set1:[] \n\n");
//    printf("                    Set2:[] \n\n");
    printf("\n\n\n\n");

    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n*   ");
    printf(" Enter a operation code: c/C, d/D, q/Q");
    printf("*\n");
    for(i = 0; i < num; i++) {
        printf("*");
    }
    printf("\n");
}

void ReadCommand(char * cmd) {
//    printf("Please enter the cmd: ");
    do {
        *cmd = getchar();
    } while(*cmd != 'c' && *cmd != 'C' && *cmd != 'd' && *cmd != 'D' && *cmd != 'q' && *cmd != 'Q');
}
void Interpret(char cmd) {
    char cmds[10];
    switch(cmd) {
        case 'c':
        case 'C':
            if(GListEmpty(Hlink)) DestroyGList(&Hlink);
            // 释放掉已建立的广义表的存储空间，提示用户输入广义表的书写形式字符串
            printf("请输入广义表的字符串: ");
//            getchar();
            CreateList(&Hlink);
//            Traverse_GL(Hlink);
//            while(getchar()) getchar();
//            getchar();
            break;
        case 'd':
        case 'D':
            Traverse_GL(Hlink);
            printf("请输入命令字符串：");
            scanf("%s", cmds);
            if(GListEmpty(Hlink)){
                printf("为空，请输入广义表：");
                CreateList(&Hlink);
            } else Decompose(Hlink, cmds);
            break;
    }
}
