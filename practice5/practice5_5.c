#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "practice5_5.h"

GraphType ga;
VisitEdgeList VEList;      //用于存储已访问的边的列表


void MainPractice5_5(void) {
//    int input;
//    char ch;
//    while(scanf("%d", &input) != 1) {
//        while((ch = getchar()) != '\n') continue;
////            putchar(ch);
//        printf(" is not an integer, \nPlease enter an integer value");
//    }
//    return ;
    VEList.size = 0;
    char cmd;
    Initialization();
    do {
        ReadCommand(&cmd);
        Interpret(cmd);
    } while(cmd != 'q' && cmd != 'Q');
}
void Initialization(void) {
    // 系统初始化
//    char filename[30] = "./practice5/Graph.dat";
    char filename[30] = "./practice5/Graph.dat";
//    char filename[20];
    FILE * fin;
    system("cls");
//    printf("输入导游图数据文件名：");
//    scanf("%s", filename);
    fin = fopen(filename, "r");
    if(fin) CreateGraph(&ga, fin);
}
void ReadCommand(char * cmd) {
    printf("请输入操作命令：");
    do {
        *cmd = getchar();
    }while(*cmd != 's' && *cmd != 'S' && *cmd != 'v' && *cmd != 'V' && *cmd != 'q' && *cmd != 'Q');
}
void Interpret(char cmd) {
    char sname[50], tname[50];
    int pathlength;
    PType pathinfo;
    pathinfo.num = 0;
    switch(cmd) {
        case 's':
        case 'S':
            printf("输入景点名称，查询景点信息：");
            scanf("%s", sname);
            PrintScenery(sname);
            break;
        case 'v':
        case 'V':
//            printf("输入始点：");
//            scanf("%s", sname);
//            printf("输入终点：");
//            scanf("%s", tname);
//            GetShortestPath(ga, sname, tname, &pathlength, &pathinfo);
            ShortestPath(ga, 1, 15, &pathlength, &pathinfo);
            PrintPathInfo(ga, pathinfo);
            printf("Shortest Distance(最短路径长度)：%d\n", pathlength);
    }
}
void CreateGraph(GraphType * G, FILE * f) {
    int i, k;
    VertexType v;
    EdgeType e;
    InitGraph(G);
    // 1. 获取节点数，和边数
    fscanfNum(f, &(G->vexNum), &(G->edgeNum));
    for(i = 1; i <= G->vexNum; i++) {
        fscanfVex(f, v.name, v.info);
        InsertVex(G, v, i);
    }
//    for(i = 1; i <= G->vexNum; i++) {
//        printf("%s--%s\n", G->Adjmulist[i].data.name, G->Adjmulist[i].data.info);
//    }
//    return ;
    for(k = 1; k <= G->edgeNum; k++) {
         fscanfEdge(f, &e.ivex, &e.jvex, &e.length);
//         printf("%d-%d-%d\n", e.ivex, e.jvex, e.length);
        if(e.length) InsertEdge(G, e);
    }
//    int vi = 5, vj;
//    EdgePtr ep = G->Adjmulist[vi].firstEdge, eq;
//    eq = ep;
//    while(eq) {
//        printf("ivex: %d, jvex: %d, length: %d\n", eq->elem.ivex, eq->elem.jvex, eq->elem.length);
//        ep = eq;
//        NextEdge(*G, vi, ep, &vj, &eq);
//    }
//    EdgePtr ep;
//    printf("\n");
//    for(k = 0; k < G->vexNum; k++) {
//        ep = G->Adjmulist[k].firstEdge;
//        if(ep)
//            printf("%d, %d-%d-%d\n", k+1, ep->elem.ivex, ep->elem.jvex, ep->elem.length);
//    }
}
void InsertVex(GraphType * G, VertexType v, int i) {
    VNode * vnp = (VNode *)malloc(sizeof(VNode));
    if(!vnp) exit(OVERFLOW);
    CopyVex(&(vnp->data), v);
    vnp->firstEdge = NULL;
    vnp->lastEdge = NULL;
    G->Adjmulist[i] = *vnp;
}
void InsertEdge(GraphType * G, EdgeType e) {
    // 在图G的邻接多重表添加一条边
    EdgePtr p, q, pre;
    p = (EdgePtr)malloc(sizeof(EdgeNode));
    p->elem = e;
//    p->ilink = FirstEdge(*G, e.ivex);
//    p->jlink = FirstEdge(*G, e.jvex);
//    G->Adjmulist[e.ivex].firstEdge = G->Adjmulist[e.jvex].firstEdge = p;

    // 顺序存储
    p->ilink = NULL;
    p->jlink = NULL;

    q = G->Adjmulist[e.ivex].firstEdge;
    if(!q) {
        G->Adjmulist[e.ivex].firstEdge = G->Adjmulist[e.ivex].lastEdge = p;
    } else {
        if(G->Adjmulist[e.ivex].lastEdge->elem.jvex == p->elem.ivex) {
            G->Adjmulist[e.ivex].lastEdge->jlink = p;
        } else G->Adjmulist[e.ivex].lastEdge->ilink = p;
        G->Adjmulist[e.ivex].lastEdge = p;
    }

    q = G->Adjmulist[e.jvex].firstEdge;
    if(!q) {
        G->Adjmulist[e.jvex].firstEdge = G->Adjmulist[e.jvex].lastEdge = p;
    } else {
        if(G->Adjmulist[e.jvex].lastEdge->elem.ivex == p->elem.jvex) {
            G->Adjmulist[e.jvex].lastEdge->ilink = p;
        } else G->Adjmulist[e.jvex].lastEdge->jlink = p;
        G->Adjmulist[e.jvex].lastEdge = p;
    }
}

EdgePtr FirstEdge(GraphType G, int vi) {
    return G.Adjmulist[vi].firstEdge;
}

void NextEdge(GraphType G, int vi, EdgePtr p, int * vj, EdgePtr * q) {
    // 以vj返回邻接于顶点vi，由p所指边的另一个顶点
    // 以q返回图中依附于顶点vi，相对于该边的下一条边
    if(p->elem.ivex == vi) {
        *q = p->ilink;
        *vj = p->elem.jvex;
    } else {
        *q = p->jlink;
        *vj = p->elem.ivex;
    }
}
void CopyVex(VertexType * v1, VertexType v2) {
    // 使用<=是把字符串结束符也复制过来
    VertexType v;
    int i;
    for(i = 0; i <= strlen(v2.name); i++) {
        v.name[i] = v2.name[i];
    }
    for(i = 0; i<= strlen(v2.info); i++) {
        v.info[i] = v2.info[i];
    }
    *v1 = v;
}

Status LocateVex(GraphType G, char * uname, int * i) {
    int k;
    Status ok;
    for(k = 0; k < G.vexNum; k++) {
        ok = CompareStr(uname, G.Adjmulist[k].data.name);
        if(ok == 1) {
            *i = k;
            break;
        }
    }
    if(k == G.vexNum && ok != 1) *i = -1;
}
void GetVex(GraphType G, int i, VertexType * v) {
//    printf("i-: %d", i);
    if(i>=1 && i<=G.vexNum) *v = G.Adjmulist[i].data;
}

void InitGraph(GraphType * G) {
    G->vexNum = G->edgeNum = 0;
}


void GetShortestPath(GraphType G, char * sname, char * tname, int * pathlength, PType * pathinfo) {
    int sv, tv;
    LocateVex(G, sname, &sv);
    LocateVex(G, tname, &tv);
//    printf("%d-%d\n", sv, tv);
    ShortestPath(G, sv, tv, pathlength, pathinfo);
}
void ShortestPath(GraphType G, int st, int nd, int * pathlength, PType * pathinfo) {
    // 利用迪特杰斯特拉算法的基本思想，求图G中从顶点st到顶点nd的一条
    // 最短路径pathinfo及其路径长度pathlength
    int dist[MAXVTXNUM], flag[MAXVTXNUM];           // 数组用以标记对应的节点是否被求得最小路径
    int i, adjvex, imin, inow;
    Status found = FALSE;
    EdgePtr p, q;
    PathType path[MAXVTXNUM];
    // 初始化
    for(i = 1; i <= G.vexNum; i++) {
        dist[i] = maxint;           // 暂将所有顶点对应的路径长度设为最大值
        InitPath(&path[i]);         // 初始化path[i].length = 0; 即不存在路径
        flag[i] = 0;
    }
    flag[st] = 1;                   // 开始节点st设为true，已求得
    dist[st] = 0;                   // 开始节点st到st的路径值为0
//    pathinfo->vertices[pathinfo->num++] = st;           // 路径pathinfo第0个节点放置st景点
    // 获取顶点st的第一条邻接边
    p = FirstEdge(G, st);
    // 初始化dist数组，检测领队于起始点的第一条边
    while(p) {
        NextEdge(G, st, p, &adjvex, &q);    // adjvex指边p的另一个顶点
        printf("%d-%d-%d\n", p->elem.ivex, p->elem.jvex, p->elem.length);
        dist[adjvex] = p->elem.length;
        InsertPath(&path[adjvex], st, adjvex);
        VEList.EdgeList[VEList.size++] = p->elem;
        p = q;      // 下一条边
    }
//    imin = MinLength(dist);
//    printf("%d--", imin);
    int count = 0;
    while(found == FALSE) {
        count++;
        // 在所有未求得最短路径的顶点中求使dist[i]取最小值的i，即是第i个节点
        imin = MinLength(dist, flag);
        flag[imin] = 1;
        printf("%d-imin\n", imin);
        if(imin == nd) found = TRUE;
        else {
            inow = imin;
            flag[inow] = 1;         // 当前最小路径的节点设为已求得
            p = FirstEdge(G, inow);
            while(p) { // 检测依附于当前最小权值节点的每一条未被访问的节点
                NextEdge(G, inow, p, &adjvex, &q);
                // 判断边是否在已经访问列表中
                if(EdgeVisited(VEList, p->elem)==0 && ((dist[inow]+p->elem.length) < dist[adjvex])) {
                    dist[adjvex] = dist[inow] + p->elem.length;
                    CopyPath(&path[adjvex], path[inow]);
                    InsertPath(&path[adjvex], inow, adjvex);
                }
                p = q;
            }
        }
    }
    //
    *pathlength = dist[nd];
    OutPath(G, path[nd], pathinfo);

}
int MinLength(int * dist, int * flag) {
    int i = 0, imin, vmin = maxint;
    for(i = 1; i < ga.vexNum; i++) {
        if(flag[i] == 1) continue;
        if(dist[i] < vmin) {
            vmin = dist[i];
            imin = i;
        }
    }
    return imin;
}
Status EdgeVisited(VisitEdgeList VEList, EdgeType et) {
    int i, ok = 0;
    for(i = 0; i < VEList.size; i++) {
        if(VEList.EdgeList[i].ivex == et.ivex && VEList.EdgeList[i].jvex == et.jvex) {
            ok = 1;
            break;
        }
    }
    return ok;
}
void PrintPathInfo(GraphType G, PType pathinfo) {
    int i, k;
    VertexType v;
    printf("Shortest path(最短路径)：");
    for(i = 0; i < pathinfo.num - 1; i++) {
        LocateVex(G, pathinfo.vertices[i], &k);
        GetVex(G, k, &v);
        printf("%s(%s)-----", v.info, v.name);
    }
    LocateVex(G, pathinfo.vertices[i], &k);
    GetVex(G, k, &v);
    printf("%s(%s)", v.info, v.name);
    printf("\n");
}
void InitPath(PathType * pa) {
    pa->len = 0;
}
// 路径相关操作
void CopyPath(PathType * pa, PathType pb) {
    int i;
    for(i = 0; i < pb.len; i++) {
        pa->edges[i].vx = pb.edges[i].vx;
        pa->edges[i].vy = pb.edges[i].vy;
    }
    pa->len = pb.len;
}
void InsertPath(PathType * pa, int v, int w) {
    // 在路径中插入一条边
    pa->edges[pa->len].vx = v;
    pa->edges[pa->len].vy = w;
    pa->len++;
}

void CopyStr(char * str1, char * str2) {
    // 只给下边的你自己用
    int i;
    for(i = 0; i <= strlen(str2); i++) {
        str1[i] = str2[i];
    }
}
void OutPath(GraphType G, PathType pa, PType * vtxes) {
    // 将路径转换为景点名称的序列
    int i, m = 0;
    VertexType vtx;
    for(i = 0; i < pa.len; i++) {
//        printf("path.edges[%d].vx:%d--vy:%d\n", i, pa.edges[i].vx, pa.edges[i].vy);
        GetVex(G, pa.edges[i].vx, &vtx);
//        printf("%s--\n", vtx.name);
//        vtxes->vertices[m++] = vtx.name;
        CopyStr(vtxes->vertices[m++], vtx.name);
    }
//    printf("%s", vtxes->vertices[4]);
    GetVex(G, pa.edges[pa.len-1].vy, &vtx);
//    vtxes->vertices[m] = vtx.name;
//    printf("%s--\n", vtx.name);
    CopyStr(vtxes->vertices[m], vtx.name);
    vtxes->num = m + 1;
//    for(i = 0; i < vtxes->num; i++) {
//        printf("%s\n", vtxes->vertices[i]);
//    }
}


void fscanfNum(FILE * f, int * vnum, int * ednum) {
    // 获取顶点数，边数
    char frow[20];
    int i = 3;
    fgets(frow, 20, f);
    *vnum = atoi(frow);
    if(*vnum < 10) i = 2;
    *ednum = atoi(frow + i);
}
void fscanfVex(FILE * f, char * name, char * info) {
    int i, k;
    char frow[50];
    fgets(frow, 30, f);
    for(i = 0; i < strlen(frow); i++) {
        if(frow[i] == ',') break;
        name[i] = frow[i];
    }
    name[i] = '\0';         // 字符串结束标志，略云name[i] i之后的空位
    // 这个地方原来只减了1，本想着fgets会把换行符给丢掉，结果还在，就减了2
    for(k = 0; k < strlen(frow) - i - 2; k++) {
        info[k] = frow[k + i + 1];
    }
    info[k] = '\0';
}
void fscanfEdge(FILE * f, int * ivex, int * jvex, int * length) {
    int i, j, l, len;
    char frow[20], tmp[3];
    fgets(frow, 20, f);
    len = strlen(frow);
    for(i = 0; i < len - 1; i++) {
        if(frow[i] == ',') break;
        tmp[i] = frow[i];
    }
    tmp[i] = '\0';
    *ivex = atoi(tmp);
    l = 0;
    for(j = i + 1; j < len - 1; j++) {
        if(frow[j] == ',') break;
        tmp[l++] = frow[j];
    }
    tmp[l] = '\0';
    *jvex = atoi(tmp);
    i = 0;
    for(l = j + 1; l < len - 1; l++) {
        tmp[i++] = frow[l];
    }
    tmp[i] = '\0';
    *length = atoi(tmp);
}

void PrintScenery(char * name) {
    int i;
    LocateVex(ga, name, &i);
    if(i != -1) printf("%s的英文名称是：%s\n", name, ga.Adjmulist[i].data.info);
    else printf("没有相关景点的信息。\n");
}
Status CompareStr(char * str1, char * str2) {
    int i = 0;
    while(i < strlen(str1) && i < strlen(str2)) {
        i++;
        if(str1[i] != str2[i]) return FALSE;
    }
    if(strlen(str1) == strlen(str2)) return TRUE;
}
