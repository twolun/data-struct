#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "practice5_5.h"

GraphType ga;

void MainPractice5_5(void) {
//    int input;
//    char ch;
//    while(scanf("%d", &input) != 1) {
//        while((ch = getchar()) != '\n') continue;
////            putchar(ch);
//        printf(" is not an integer, \nPlease enter an integer value");
//    }
//    return ;
    char cmd;
    Initialization();
    return ;
    do {
        ReadCommand(&cmd);
        Interpret(cmd);
    } while(cmd != 'q' && cmd != 'Q');
}
void Initialization(void) {
    // ϵͳ��ʼ��
    char filename[30] = "./practice5/Graph.dat";
//    char filename[20];
    FILE * fin;
    system("cls");
    printf("���뵼��ͼ�����ļ�����");
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

}
void CreateGraph(GraphType * G, FILE * f) {
    int i, k;
    VertexType v;
    EdgeType e;
    InitGraph(G);
    // 1. ��ȡ�ڵ������ͱ���
    fscanfNum(f, &(G->vexNum), &(G->edgeNum));
    for(i = 0; i < G->vexNum - 1; i++) {
        fscanfVex(f, v.name, v.info);
        InsertVex(G, v, i);
    }
//    for(i = 0; i < G->vexNum - 1; i++) {
//        printf("%s--%s\n", G->Adjmulist[i].data.name, G->Adjmulist[i].data.info);
//    }
//    return ;
    for(k = 0; k < G->edgeNum; k++) {
         fscanfEdge(f, &e.ivex, &e.jvex, &e.length);
//         printf("%d-%d-%d\n", e.ivex, e.jvex, e.length);
        if(e.length) InsertEdge(G, e);
    }
//    EdgePtr ep = G->Adjmulist[12].firstEdge;
//    while(ep) {
//        printf("ivex: %d, jvex: %d, length: %d\n", ep->elem.ivex, ep->elem.jvex, ep->elem.length);
//        ep = ep->ilink;
//    }
    EdgePtr ep;
    printf("\n");
    for(k = 0; k < G->vexNum; k++) {
        ep = G->Adjmulist[k+1].firstEdge;
        if(ep)
            printf("%d, %d-%d-%d\n", k+1, ep->elem.ivex, ep->elem.jvex, ep->elem.length);
    }
}
void InsertVex(GraphType * G, VertexType v, int i) {
    VNode * vnp = (VNode *)malloc(sizeof(VNode));
    if(!vnp) exit(OVERFLOW);
    CopyVex(&(vnp->data), v);
    vnp->firstEdge = NULL;
    G->Adjmulist[i] = *vnp;
}
void InsertEdge(GraphType * G, EdgeType e) {
    // ��ͼG���ڽӶ��ر����һ����
    EdgePtr p;
    p = (EdgePtr)malloc(sizeof(EdgeNode));
    p->elem = e;
    p->ilink = FirstEdge(*G, e.ivex);
    p->jlink = FirstEdge(*G, e.jvex);
    G->Adjmulist[e.ivex].firstEdge = G->Adjmulist[e.jvex].firstEdge = p;
}

EdgePtr FirstEdge(GraphType G, int vi) {
    return G.Adjmulist[vi].firstEdge;
}

void NextEdge(GraphType G, int vi, EdgePtr p, int * vj, EdgePtr * q) {
    // ��vj��������ڶ���vi����p��ָ�ߵ���һ������
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

}
void GetVex(GraphType G, int i, VertexType * v) {

}

void InitGraph(GraphType * G) {
    G->vexNum = G->edgeNum = 0;
}


void GetShortPath(GraphType G, char * sname, char * tname, int * pathlength, PType * pathinfo) {
    int sv, tv;
    LocateVex(G, sname, sv);
    LocateVex(G, tname, tv);
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
void InserPath(PathType * pa, int v, int w) {
    // ��·���в���һ����
    pa->edges[pa->len].vx = v;
    pa->edges[pa->len].vy = w;
    pa->len++;
}

void OutPath(GraphType G, PathType pa, PType * vtxes) {
    // ��·��ת��Ϊ�������Ƶ�����
    int i, m = 0;
    VertexType vtx;
    for(i = 0; i < pa.len; i++) {
        GetVex(G, pa.edges[i].vx, &vtx);
        vtxes->vertices[m++] = vtx.name;
    }
    GetVex(G, pa.edges[pa.len].vy, &vtx);
    vtxes->vertices[m] = vtx.name;
    vtxes->num = m;
}
void ShortestPath(GraphType G, int st, int nd, int pathlength, PType * pathinfo) {
    // ���õ��ؽ�˹�����㷨�Ļ���˼�룬��ͼG�дӶ���st������nd��һ��
    // ���·��pathinfo����·������pathlength
    int dist[MAXVTXNUM];
    PathType path[MAXVTXNUM];

}

void fscanfNum(FILE * f, int * vnum, int * ednum) {
    // ��ȡ������������
    char frow[20];
    fgets(frow, 20, f);
    *vnum = atoi(frow);
    *ednum = atoi(frow + 3);
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
    for(k = 0; k < strlen(frow) - i - 1; k++) {
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
