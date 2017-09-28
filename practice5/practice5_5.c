#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "practice5_5.h"

GraphType ga;
VisitEdgeList VEList;      //���ڴ洢�ѷ��ʵıߵ��б�


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
    // ϵͳ��ʼ��
//    char filename[30] = "./practice5/Graph.dat";
    char filename[30] = "./practice5/Graph.dat";
//    char filename[20];
    FILE * fin;
    system("cls");
//    printf("���뵼��ͼ�����ļ�����");
//    scanf("%s", filename);
    fin = fopen(filename, "r");
    if(fin) CreateGraph(&ga, fin);
}
void ReadCommand(char * cmd) {
    printf("������������");
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
            printf("���뾰�����ƣ���ѯ������Ϣ��");
            scanf("%s", sname);
            PrintScenery(sname);
            break;
        case 'v':
        case 'V':
//            printf("����ʼ�㣺");
//            scanf("%s", sname);
//            printf("�����յ㣺");
//            scanf("%s", tname);
//            GetShortestPath(ga, sname, tname, &pathlength, &pathinfo);
            ShortestPath(ga, 1, 15, &pathlength, &pathinfo);
            PrintPathInfo(ga, pathinfo);
            printf("Shortest Distance(���·������)��%d\n", pathlength);
    }
}
void CreateGraph(GraphType * G, FILE * f) {
    int i, k;
    VertexType v;
    EdgeType e;
    InitGraph(G);
    // 1. ��ȡ�ڵ������ͱ���
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
    // ��ͼG���ڽӶ��ر����һ����
    EdgePtr p, q, pre;
    p = (EdgePtr)malloc(sizeof(EdgeNode));
    p->elem = e;
//    p->ilink = FirstEdge(*G, e.ivex);
//    p->jlink = FirstEdge(*G, e.jvex);
//    G->Adjmulist[e.ivex].firstEdge = G->Adjmulist[e.jvex].firstEdge = p;

    // ˳��洢
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
    // ��vj�����ڽ��ڶ���vi����p��ָ�ߵ���һ������
    // ��q����ͼ�������ڶ���vi������ڸñߵ���һ����
    if(p->elem.ivex == vi) {
        *q = p->ilink;
        *vj = p->elem.jvex;
    } else {
        *q = p->jlink;
        *vj = p->elem.ivex;
    }
}
void CopyVex(VertexType * v1, VertexType v2) {
    // ʹ��<=�ǰ��ַ���������Ҳ���ƹ���
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
    // ���õ��ؽ�˹�����㷨�Ļ���˼�룬��ͼG�дӶ���st������nd��һ��
    // ���·��pathinfo����·������pathlength
    int dist[MAXVTXNUM], flag[MAXVTXNUM];           // �������Ա�Ƕ�Ӧ�Ľڵ��Ƿ������С·��
    int i, adjvex, imin, inow;
    Status found = FALSE;
    EdgePtr p, q;
    PathType path[MAXVTXNUM];
    // ��ʼ��
    for(i = 1; i <= G.vexNum; i++) {
        dist[i] = maxint;           // �ݽ����ж����Ӧ��·��������Ϊ���ֵ
        InitPath(&path[i]);         // ��ʼ��path[i].length = 0; ��������·��
        flag[i] = 0;
    }
    flag[st] = 1;                   // ��ʼ�ڵ�st��Ϊtrue�������
    dist[st] = 0;                   // ��ʼ�ڵ�st��st��·��ֵΪ0
//    pathinfo->vertices[pathinfo->num++] = st;           // ·��pathinfo��0���ڵ����st����
    // ��ȡ����st�ĵ�һ���ڽӱ�
    p = FirstEdge(G, st);
    // ��ʼ��dist���飬����������ʼ��ĵ�һ����
    while(p) {
        NextEdge(G, st, p, &adjvex, &q);    // adjvexָ��p����һ������
        printf("%d-%d-%d\n", p->elem.ivex, p->elem.jvex, p->elem.length);
        dist[adjvex] = p->elem.length;
        InsertPath(&path[adjvex], st, adjvex);
        VEList.EdgeList[VEList.size++] = p->elem;
        p = q;      // ��һ����
    }
//    imin = MinLength(dist);
//    printf("%d--", imin);
    int count = 0;
    while(found == FALSE) {
        count++;
        // ������δ������·���Ķ�������ʹdist[i]ȡ��Сֵ��i�����ǵ�i���ڵ�
        imin = MinLength(dist, flag);
        flag[imin] = 1;
        printf("%d-imin\n", imin);
        if(imin == nd) found = TRUE;
        else {
            inow = imin;
            flag[inow] = 1;         // ��ǰ��С·���Ľڵ���Ϊ�����
            p = FirstEdge(G, inow);
            while(p) { // ��������ڵ�ǰ��СȨֵ�ڵ��ÿһ��δ�����ʵĽڵ�
                NextEdge(G, inow, p, &adjvex, &q);
                // �жϱ��Ƿ����Ѿ������б���
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
    printf("Shortest path(���·��)��");
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
// ·����ز���
void CopyPath(PathType * pa, PathType pb) {
    int i;
    for(i = 0; i < pb.len; i++) {
        pa->edges[i].vx = pb.edges[i].vx;
        pa->edges[i].vy = pb.edges[i].vy;
    }
    pa->len = pb.len;
}
void InsertPath(PathType * pa, int v, int w) {
    // ��·���в���һ����
    pa->edges[pa->len].vx = v;
    pa->edges[pa->len].vy = w;
    pa->len++;
}

void CopyStr(char * str1, char * str2) {
    // ֻ���±ߵ����Լ���
    int i;
    for(i = 0; i <= strlen(str2); i++) {
        str1[i] = str2[i];
    }
}
void OutPath(GraphType G, PathType pa, PType * vtxes) {
    // ��·��ת��Ϊ�������Ƶ�����
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
    // ��ȡ������������
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
    name[i] = '\0';         // �ַ���������־������name[i] i֮��Ŀ�λ
    // ����ط�ԭ��ֻ����1��������fgets��ѻ��з���������������ڣ��ͼ���2
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
    if(i != -1) printf("%s��Ӣ�������ǣ�%s\n", name, ga.Adjmulist[i].data.info);
    else printf("û����ؾ������Ϣ��\n");
}
Status CompareStr(char * str1, char * str2) {
    int i = 0;
    while(i < strlen(str1) && i < strlen(str2)) {
        i++;
        if(str1[i] != str2[i]) return FALSE;
    }
    if(strlen(str1) == strlen(str2)) return TRUE;
}
