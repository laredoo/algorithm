#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Implementacao do algoritmo de Kosaraju para construir o componente fortemente conexo

class graph
{
  public:
    int v;    //numero de vertices
    int s;
    vector<int> *adj;    //um array de vectors de adjacencia
    vector<int> *adjInv; //vector de adjacencia inverso
    bool *visited;
    bool *visitedInv;
    stack<int> pilha;

    // this array will store the SCC that the
    // particular node belongs to
    int *scc;

    // counter maintains the number of the SCC
    int counter;

    graph(int v, int s) {
        this->v = v;
        this->s = s;
        adj = new vector<int>[50000];
        adjInv = new vector<int>[50000];
        visited =  new bool[50000];
        visitedInv = new bool[50000];
        scc = new int[50000];
        counter = 1;
    }

    void addEdges(int a, int b);

    void addEdgesInv(int a, int b);

    void dfsFirst(int u);

    void dfsSecond(int u);

    void is2sat(int n, int m, int a[], int b[]);
};

#endif