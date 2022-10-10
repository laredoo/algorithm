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
    bool *visited; //array com os nos ja percorridos
    bool *visitedInv; //array com os nos do vetor inverso ja percorrido
    stack<int> pilha; //pilha preenchida pelos index dos vertices visitados

    // array que armazera os CFC que cada no pertence
    int *scc;

    // variavel que conta o numero de CFC
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

    //funcao que adiciona uma aresta ao vetor de adjacencia
    void addAresta(int a, int b);

    //funcao que adiciona uma aresta ao vetor de adjacencia inverso
    void addArestaInv(int a, int b);

    //primeira dfs que percorre o vetor de adjacencia e preenche a pilha
    void dfsFirst(int u);

    //segunda dfs que para cada entrada da pilha percorre o vetor de adjacencia inverso e preenche o array de scc
    void dfsSecond(int u);

    //funcao principal do algoritmo de satisfatibilidade
    void is2sat(int n, int m, int a[], int b[]);
};

#endif