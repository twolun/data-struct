#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "practice4_3.h"

// ����ȫ��ʹ�ù����
GList Hlink;
void MainPractice4_3(void) {
    char cmd, cmds[20];
//    while((cmd = getchar())) {
//        putchar((cmd));
//    }
//    return FALSE;
    InitGList(&Hlink);
    Initialization();       // ��ʼ��
//    do {
//        ReadCommand(&cmd);  // ����һ�����������
//        Interpret(cmd);     // ����ִ�в��������
//        getchar();
//        while(getchar()) getchar();          // ��ô����ط�Ҫ�ѻ�������Ļ��з����ɵ�
//    } while(cmd != 'q' && cmd != 'Q');
    do {
    printf("�����������ַ�����");
    CreateList(&Hlink);
    Traverse_GL(Hlink);
    printf("\n������������������");
    scanf("%s", cmds);
    Decompose(Hlink, cmds);
    }while(cmd != 'q' && cmd != 'Q');
}

void Traverse_GL(GList Ls) {
    // �������������д��ʽ������ն�
    if(!Ls) printf("( )");
    else {
        if(Ls->tag == ATOM) printf("%c", GL_Elem(Ls));    // �������ԭ��
        else {
            printf("(");
            while(Ls != NULL) {
                Traverse_GL(GetHead(Ls));           // ��������������е�һ���ӱ�
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
    // ���㷨ʶ��һ��������Ĺ�����ַ��������е���ĸ�����۴�Сд������ʾԭ�ӣ�
    // ����Ӧ�Ĵ洢�ṹ��LsΪָ���һ������ָ�롣��������ַ���Ϊ��()����
    // ��ù����Ϊ�ձ���Ls = NULL
    // �Ȱ���Ļ�ϵ�������
    char ch;
    getAChar(&ch);       // ʰȡ��һ���Ϸ��ַ�
    if(ch != '(') return ERROR;         // �����ĵ�һ���ַ�ֻ����"("
    else return crtLtBU(Ls);
}
Status GListEmpty(GList Ls) {
    if(Ls != NULL) return FALSE;
    else return TRUE;
}
void DestroyGList(GList * Ls) {
    GList hp, tp;
    // ��ģ���ҲҪ�ݹ�����ѽ
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
    // ���㷨ʶ��һ��������Ĵ��ַ�'('��','֮��Ĺ�����ַ���
    // ��������Ӧ�Ĵ洢�ṹ
    char ch;
    getAChar(&ch);              // ʰȡ��һ���Ϸ����ַ�
    if(ch == '\n') return TRUE;
    if(ch == ' ') {              // �ձ�����
        (*Ls) = NULL;
        getAChar(&ch);          // ʰȡ��һ���Ϸ����ַ���Ӧ����')'
        if(ch != ')') return ERROR;
    } else {
        // ������Ĺ����ǿ�
        *Ls = (GList)malloc(sizeof(GLNode));
        (*Ls)->tag = LIST;       // ������
        if(isalpha(ch)) {           // ��ͷΪ��ԭ�ӣ�����ֱ������ĸ������(, ...
            (*Ls)->ptr.hp = (GList)malloc(sizeof(GLNode));
            (*Ls)->ptr.hp->tag = ATOM;
            (*Ls)->ptr.hp->data = ch;
        } else if(ch == '('){   // ��ͷΪ�����
            // ����ִ��crtLtBU
            crtLtBU(&((*Ls)->ptr.hp));
        } else return ERROR;        // �����ַ���Ϊ�������
        getAChar(&ch);          // ʰȡ��һ���Ϸ��ַ�
        if(ch == ')') (*Ls)->ptr.tp = NULL;
        else if(ch == ',') crtLtBU(&((*Ls)->ptr.tp));          // ��β��Ϊ��
        else return ERROR;
    }
    return TRUE;
}
void getAChar(char * ch) {
    scanf("%c", ch);
//    printf("%c ", *ch);
}
void Decompose(GList Ls, char * cmds) {
    // �������str���Թ����Hlinkִ�С����ͷ�������β������
    // �����ÿһ����������õ���ӡ�б�ͷ���β���ַ���
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
    // ϵͳ��ʼ��
    system("cls");      // ����������
    // ����˵�
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
            // �ͷŵ��ѽ����Ĺ����Ĵ洢�ռ䣬��ʾ�û������������д��ʽ�ַ���
            printf("������������ַ���: ");
//            getchar();
            CreateList(&Hlink);
//            Traverse_GL(Hlink);
//            while(getchar()) getchar();
//            getchar();
            break;
        case 'd':
        case 'D':
            Traverse_GL(Hlink);
            printf("�����������ַ�����");
            scanf("%s", cmds);
            if(GListEmpty(Hlink)){
                printf("Ϊ�գ�����������");
                CreateList(&Hlink);
            } else Decompose(Hlink, cmds);
            break;
    }
}
