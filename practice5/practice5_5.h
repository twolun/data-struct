#ifndef PRACTICE5_5_H_INCLUDED
#define PRACTICE5_5_H_INCLUDED
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2

// ȫ�ֱ���
#define MAXVTXNUM     20    // ͼ����󶥵���
typedef int Status;

typedef struct {
    char name[20];          // �������������󳤶�20
    char info[50];          // ������Ϣ����󳤶�50
} VertexType;               // ��������������

typedef struct {
    int length;             // �ߵ�Ȩֵ����ʾ·������
    int ivex, jvex;         // �ߵ����˶����
} EdgeType;                 // �ߵ�����

typedef struct EdgeNode {
    EdgeType elem;
    EdgeType * ilink, * jlink;
} EdgeNode, * EdgePtr;      // �ߵĽڵ����ͣ�ָ��ߵ�ָ��

typedef struct {
    VertexType data;
    EdgePtr firstEdge;      // ָ���һ���ڽӸö���ı�
} VNode;                    // ��������

typedef struct {
    VNode Adjmulist[MAXVTXNUM];     // �ⲻ���ڽӶ��ر����Ƕ����˳���
    int vexNum, edgeNum;            // ͼ�ж������ͱ���
} GraphType;                        // ͼ����

// ͼ�Ļ�������
void InitGraph(GraphType * G);
// ��ʼ���ڽӶ��ر���ʾһ����ͼ��G->vexNum = G->edgeNum = 0;
Status LocateVex(GraphType G, char * uname, int * i);
// ��ͼ�в����侰�����ƺ�uname��ͬ�Ķ��㣬�����ڣ����������ڽӶ��ر��е�λ��
// ������TRUE��G.Adjmullist[i].data.name = uname�����򷵻�FALSE
void GetVex(GraphType G, int i, VertexType * v);
// ��v�����ڽӶ��ر������Ϊi�Ķ���G.Adjmulist[i].data
void CopyVex(VertexType * v1, VertexType v2);
//
EdgePtr FirstEdge(GraphType G, int vi);
// ����ͼ��ָ�������ڶ���vi�ĵ�һ���ߵ�ָ�룬G.Adjmulist[vi].firstEdge
void NextEdge(GraphType G, int vi, EdgePtr p, int * vj, EdgePtr * q);
// ��vj����G�������ڶ���vi��һ���ıߵ���һ�����㣬����pָ��
// ��q����ͼG�������ڶ���vi�������ָ��p��ָ�ߵ���һ����
void InsertVex(GraphType * G, VertexType v, int i);
// ��ͼ���ڽӶ��ر����һ������v
void InsertEdge(GraphType * G, EdgeType e);
// ��ͼG���ڽӶ��ر����һ����e
void DeleteVex(GraphType * G, VertexType v);
// ��ͼɾ������v���������ڸö���ı�
void DeleteEdge(GraphType * G, EdgeType e);
// ��ͼG��ɾ����e


// 2. ·������
typedef struct {
    int vx, vy;
} Edge;

typedef struct {
    Edge edges[MAXVTXNUM];          // ·���бߵ�����
    int len;                        // ·���бߵ�����
} PathType;

typedef struct {
    char * vertices[20];            // ·���о��������
    int num;
}PType;

// ������������
void CreateGraph(GraphType * G, FILE * f);
// ���ļ��ж�ȡ����ͱߵ����ݣ������ڽӶ��ر�

void GetShortPath(GraphType G, char * sname, char * tname, int * pathlength, PType * pathinfo);
// �Ӿ���sname������tname��һ�����·�����䳤��

void InitPath(PathType * pa);
// ��ʼ��paΪһ����·����pa->len = 0;
void CopyPath(PathType * pa, PathType pb);
// ����·�� pa = pb
void InserPath(PathType * pa, int v, int w);
// ��·����pa�в���һ����(v,w)
int PathLength(PathType pa);
// ����·��pa�ĳ���
void OutPath(GraphType G, PathType pa, PType * vtxes);
// ��·��ת��Ϊ�������Ƶ�����

void Initialization(void);
void ReadCommand(char * cmd);
void Interpret(char cmd);

void ShortestPath(GraphType G, int st, int nd, int pathlength, PType * pathinfo);

void fscanfNum(FILE * f, int * vnum, int * ednum);
// ��ȡ������������
void fscanfVex(FILE * f, char * name, char * info);
// ��ȡ����name, info
void fscanfEdge(FILE * f, int * ivex, int * jvex, int * length);

#endif // PRACTICE5_5_H_INCLUDED

/*
ADT Graph {
    ���ݶ��� V: V���Ǿ�����ͬ���Ե�����Ԫ�صļ��ϣ���Ϊ����
    ���ݹ�ϵ R:
        R = {VR}
        VR = {(v,w)|v,w����V,(v,w)��ʾv��w֮�����·��}
    ����������
        CreateGraph(&G, V, VR);
            ��ʼ������V��ͼ�ж��㼯��VR��ͼ�бߵļ���
            �����������V��VR�Ķ��幹��ͼG
        DestroyGraph(&G);
            ��ʼ������ͼG����
            �������������ͼG
        LocateVex(G, u);
            ��ʼ������ͼG���ڣ�u��ͼ�еĶ��������ͬ�����ݽṹ
            ���������ͼ�д��ڶ���u���򷵻ض���u��ͼG�е�λ�ã����򷵻�������Ϣ
        GetVex(G, v);
            ��ʼ������ͼG���ڣ�v��ͼ��ĳ������
            �������������v����Ϣ
        FirstEdge(G, v);
            ��ʼ������ͼG���ڣ�v��ͼ��ĳ������
            �������������������v�ĵ�һ���ߣ����ö�����ͼG��û���ڽӵ㣬�򷵻ؿ�
        InsertVex(G, v);
            ��ʼ������ͼG���ڣ�v��ͼ�ж��������ͬ������
            �����������ͼ�������¶���v
        DeleteVex(G, v);
            ��ʼ������ͼG���ڣ�v��G��ĳ������
            ���������ɾ��G�ж���v������صı�
        InsertEdge(G, v, w);
            ��ʼ������ͼG���ڣ�v��w��G����������
            �����������G�����ӱ�(v,w)
        DeleteEdge(G, v, w);
            ��ʼ������ͼG���ڣ�v��w��G����������
            �����������G��ɾ����(v,w)
        GetShortPath(G, st, nd, &path);
            ��ʼ������ͼG���ڣ�st, nd��ͼ����������
            �����������st��nd֮�����·��������path��������֮��һ�����·����
                      ���򷵻�������Ϣ

}
*/
