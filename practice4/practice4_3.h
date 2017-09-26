#ifndef PRACTICE4_3_H_INCLUDED
#define PRACTICE4_3_H_INCLUDED

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

// 1. 广义表结点类型定义
typedef enum { ATOM, LIST } ElemTag;
typedef struct GLNode {
    ElemTag tag;
    union {
        char data;
        struct { struct GLNode *hp, *tp; } ptr;
    };
} GLNode, * GList;

char GL_Elem(GList Ls);
// 当Ls->tag == ATOM时，返回其原子项

// 2. 广义表的基本操作定义
void InitGList(GList * Ls);
// 初始化广义表Ls为空表，Ls = NULL
Status CreateList(GList * Ls);
// 由计算机终端输入广义表的书写串，连读入边建广义表Ls的存储结构
void DestroyGList(GList * Ls);
// 销毁广义表Ls结构，同时释放结点空间
Status GListEmpty(GList Ls);
// 若广义表Ls为空表，则返回TRUE，否则返回FALSE
GList GetHead(GList Ls);
// 若广义表Ls非空，则返回其表头Ls->hp，否则返回NULL
GList GetTail(GList Ls);
// 若广义表Ls非空，则返回其表尾Ls->tp，否则返回NULL
void Traverse_GL(GList Ls);
// 遍历广义表Ls，以书写形式输出到终端

// 3. 其他辅助函数
void getAChar(char * ch);
// 从键盘接受一个能构成广义表的合法字符，即ch
// 为属集合['a'...'z','(',')','','A'...'Z']中的字符
Status crtLtBU(GList * Ls);
// 识别一个待输入的从字符'('或','之后的广义表字符串
// 并建立相应的存储结构
void Decompose(GList Ls, char * cmds);

// 初始化操作
void Initialization();
void ReadCommand(char * cmd);
void Interpret(char cmd);



#endif // PRACTICE4_3_H_INCLUDED
