#ifndef PRACTICE4_3_H_INCLUDED
#define PRACTICE4_3_H_INCLUDED

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

// 1. ����������Ͷ���
typedef enum { ATOM, LIST } ElemTag;
typedef struct GLNode {
    ElemTag tag;
    union {
        char data;
        struct { struct GLNode *hp, *tp; } ptr;
    };
} GLNode, * GList;

char GL_Elem(GList Ls);
// ��Ls->tag == ATOMʱ��������ԭ����

// 2. �����Ļ�����������
void InitGList(GList * Ls);
// ��ʼ�������LsΪ�ձ�Ls = NULL
Status CreateList(GList * Ls);
// �ɼ�����ն������������д����������߽������Ls�Ĵ洢�ṹ
void DestroyGList(GList * Ls);
// ���ٹ����Ls�ṹ��ͬʱ�ͷŽ��ռ�
Status GListEmpty(GList Ls);
// �������LsΪ�ձ��򷵻�TRUE�����򷵻�FALSE
GList GetHead(GList Ls);
// �������Ls�ǿգ��򷵻����ͷLs->hp�����򷵻�NULL
GList GetTail(GList Ls);
// �������Ls�ǿգ��򷵻����βLs->tp�����򷵻�NULL
void Traverse_GL(GList Ls);
// ���������Ls������д��ʽ������ն�

// 3. ������������
void getAChar(char * ch);
// �Ӽ��̽���һ���ܹ��ɹ����ĺϷ��ַ�����ch
// Ϊ������['a'...'z','(',')','','A'...'Z']�е��ַ�
Status crtLtBU(GList * Ls);
// ʶ��һ��������Ĵ��ַ�'('��','֮��Ĺ�����ַ���
// ��������Ӧ�Ĵ洢�ṹ
void Decompose(GList Ls, char * cmds);

// ��ʼ������
void Initialization();
void ReadCommand(char * cmd);
void Interpret(char cmd);



#endif // PRACTICE4_3_H_INCLUDED
