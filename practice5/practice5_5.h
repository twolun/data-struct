#ifndef PRACTICE5_5_H_INCLUDED
#define PRACTICE5_5_H_INCLUDED
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2

// 全局变量
#define MAXVTXNUM     20    // 图中最大顶点数
#define MAXEDGENUM    200   // 边的最大数
#define maxint 32767
typedef int Status;

typedef struct {
    char name[20];          // 景点的姓名，最大长度20
    char info[50];          // 景点信息，最大长度50
} VertexType;               // 顶点数据域类型

typedef struct {
    int length;             // 边的权值，表示路径长度
    int ivex, jvex;         // 边的两端顶点号
} EdgeType;                 // 边的类型

typedef struct EdgeNode {
    EdgeType elem;
    EdgeType * ilink, * jlink;
} EdgeNode, * EdgePtr;      // 边的节点类型，指向边的指针

typedef struct {
    VertexType data;
    EdgePtr firstEdge;      // 指向第一条邻接该顶点的边
    EdgePtr lastEdge;       // 指向最后一个邻接该顶点的边
} VNode;                    // 顶点类型

typedef struct {
    VNode Adjmulist[MAXVTXNUM];     // 这不是邻接多重表，这是顶点的顺序表
    int vexNum, edgeNum;            // 图中顶点数和边数
} GraphType;
                    // 图类型
typedef struct {
    EdgeType EdgeList[MAXEDGENUM];   // 存放已访问的边的数组
    int size;
} VisitEdgeList;
// 图的基本操作
void InitGraph(GraphType * G);
// 初始化邻接多重表，表示一个空图，G->vexNum = G->edgeNum = 0;
Status LocateVex(GraphType G, char * uname, int * i);
// 在图中查找其景点名称和uname相同的顶点，若存在，返回其在邻接多重表中的位置
// 并返回TRUE，G.Adjmullist[i].data.name = uname，否则返回FALSE
void GetVex(GraphType G, int i, VertexType * v);
// 以v返回邻接多重表中序号为i的顶点G.Adjmulist[i].data
void CopyVex(VertexType * v1, VertexType v2);
//
EdgePtr FirstEdge(GraphType G, int vi);
// 返回图中指向依附于顶点vi的第一条边的指针，G.Adjmulist[vi].firstEdge
void NextEdge(GraphType G, int vi, EdgePtr p, int * vj, EdgePtr * q);
// 以vj返回G中依附于顶点vi的一条的边的另一个顶点，边由p指定
// 以q返回图G中依附于顶点vi且相对于指针p所指边的下一条边
void InsertVex(GraphType * G, VertexType v, int i);
// 在图中邻接多重表添加一个顶点v
void InsertEdge(GraphType * G, EdgeType e);
// 在图G的邻接多重表添加一条边e
void DeleteVex(GraphType * G, VertexType v);
// 从图删除顶点v及所依附于该顶点的边
void DeleteEdge(GraphType * G, EdgeType e);
// 从图G中删除边e
Status EdgeVisited(VisitEdgeList VEList, EdgeType et);
// 判断边是否在已经访问的列表中：VEList[i].ivex = et.ivex && VEList[i].jvex = et.jvex

// 2. 路径类型
typedef struct {
    int vx, vy;
} Edge;

typedef struct {
    Edge edges[MAXVTXNUM];          // 路径中边的序列
    int len;                        // 路径中边的数量
} PathType;

typedef struct {
    char vertices[20][100];            // 路径中景点的序列
    int num;
} PType;

// 其他辅助函数
void CreateGraph(GraphType * G, FILE * f);
// 从文件中读取顶点和边的数据，建立邻接多重表

void GetShortestPath(GraphType G, char * sname, char * tname, int * pathlength, PType * pathinfo);
// 从景点sname到景点tname的一条最短路径及其长度

void InitPath(PathType * pa);
// 初始化pa为一条空路径，pa->len = 0;
void CopyPath(PathType * pa, PathType pb);
// 复制路径 pa = pb
void InsertPath(PathType * pa, int v, int w);
// 在路径中pa中插入一条边(v,w)
int PathLength(PathType pa);
// 返回路径pa的长度
void OutPath(GraphType G, PathType pa, PType * vtxes);
// 将路径转换为景点名称的序列
void PrintPathInfo(GraphType G, PType pathinfo);

void Initialization(void);
void ReadCommand(char * cmd);
void Interpret(char cmd);

void ShortestPath(GraphType G, int st, int nd, int * pathlength, PType * pathinfo);

void fscanfNum(FILE * f, int * vnum, int * ednum);
// 读取顶点数，边数
void fscanfVex(FILE * f, char * name, char * info);
// 读取顶点name, info
void fscanfEdge(FILE * f, int * ivex, int * jvex, int * length);
void PrintScenery(char * name);
// 根据景点名，打印景点信息
Status CompareStr(char * str1, char * str2);
// 比较两个字符串是否相等，str1 == str2 返回TRUE，否则返回FALSE
int MinLength(int * dist, int * flag);
// 在所有未求得最短路径的顶点中，求dist[i]最小值的i


#endif // PRACTICE5_5_H_INCLUDED

/*
ADT Graph {
    数据对象 V: V不是具有相同特性的数据元素的集合，称为顶点
    数据关系 R:
        R = {VR}
        VR = {(v,w)|v,w属于V,(v,w)表示v和w之间存在路径}
    基本操作：
        CreateGraph(&G, V, VR);
            初始条件：V是图中顶点集，VR是图中边的集合
            操作结果：按V和VR的定义构造图G
        DestroyGraph(&G);
            初始条件：图G存在
            操作结果：销毁图G
        LocateVex(G, u);
            初始条件：图G存在，u与图中的顶点具有相同的数据结构
            操作结果：图中存在顶点u，则返回顶点u在图G中的位置，否则返回其他信息
        GetVex(G, v);
            初始条件：图G存在，v是图中某个顶点
            操作结果：返回v的信息
        FirstEdge(G, v);
            初始条件：图G存在，v是图中某个顶点
            操作结果：返回依附于v的第一条边，若该顶点在图G中没有邻接点，则返回空
        InsertVex(G, v);
            初始条件：图G存在，v和图中顶点具有相同的特征
            操作结果：在图中增添新顶点v
        DeleteVex(G, v);
            初始条件：图G存在，v是G中某个顶点
            操作结果：删除G中顶点v及其相关的边
        InsertEdge(G, v, w);
            初始条件：图G存在，v和w是G中两个顶点
            操作结果：在G中增加边(v,w)
        DeleteEdge(G, v, w);
            初始条件：图G存在，v和w是G中两个顶点
            操作结果：在G中删除边(v,w)
        GetShortPath(G, st, nd, &path);
            初始条件：图G存在，st, nd是图中两个顶点
            操作结果：若st和nd之间存在路径，则以path返回两点之间一条最短路径，
                      否则返回其他信息

}
*/
