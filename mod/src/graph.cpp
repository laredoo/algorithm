#include "../include/graph.hpp"

void graph::addAresta(int a, int b) {

    this->adj[a].push_back(b);

}

void graph::addArestaInv(int a, int b) {

    this->adjInv[b].push_back(a);

}

void graph::dfsFirst(int u) {
    if(visited[u])
        return;
    visited[u] = 1;
    for(int i = 0; i <adj[u].size();i++){
        dfsFirst(adj[u][i]);
    }   
    pilha.push(u);
}

void graph::dfsSecond(int u)
{
    if(visitedInv[u])
        return;
    visitedInv[u] = 1;
    for (int i=0;i<adjInv[u].size();i++)
        dfsSecond(adjInv[u][i]);
    scc[u] = counter;
}

void graph::is2sat(int n, int m, int a[], int b[]) {
    
    for(int i = 0; i < m; i++) {
        //x eh mapeado para x
        //-x eh mapeado para n+x = n - (-x)

        //para a[i] or b[i], addAresta -a[i] -> b[i]
        //AND -b[i] -> a[i]

        //ex:<-3,-4>
        if(a[i] < 0 && b[i] < 0) {
            this->adj[-a[i]].push_back(n - b[i]);
            this->adjInv[n - b[i]].push_back(-a[i]);
            this->adj[-b[i]].push_back(n-a[i]);
            this->adjInv[n-a[i]].push_back(-b[i]);
        }

        //ex:<3,4>
        if(a[i] > 0 && b[i] > 0) {
            this->adj[a[i] + n].push_back(b[i]);
            this->adj[b[i] + n].push_back(a[i]);
            this->adjInv[b[i]].push_back(a[i] + n);
            this->adjInv[a[i]].push_back(b[i] + n);
        }

        //ex:<0,2>
        if(a[i]==0 && b[i] > 0) {
            addAresta(b[i], b[i]);
            addArestaInv(b[i], b[i]);
        }

        //ex:<2,0>
        if(a[i] > 0 && b[i]==0) {
            addAresta(a[i], a[i]);
            addArestaInv(a[i], a[i]);
        }

        //ex:<0,-2>
        if(a[i]==0 && b[i] < 0) {
            addAresta(n-b[i], n-b[i]);
            addArestaInv(n-b[i], n-b[i]);
        }

        //ex:<-2,0>
        if(a[i] < 0 && b[i] == 0) {
            addAresta(n-a[i], n-a[i]);
            addArestaInv(n-a[i], n-a[i]);
        }
    }

    for(int i = 1; i <= 2*n; i++) 
        if(!visited[i])
            dfsFirst(i);

    while (!pilha.empty())
    {
        int topo = pilha.top();
        pilha.pop();

        if(!visitedInv[topo]) {
            dfsSecond(topo);
            counter++;
        }
    }

    for (int i=1;i<=n;i++)
    {
        // Caso x e -x estiverem na mesma CFC
        if(scc[i]==scc[i+n])
        {
            cout << "Não"
                 << endl;
            return;
        }
    }

    // Caso não exista x, tal que x e -x não estiverem na mesma CFC
    cout << "Sim"
         << endl;
    return; 
}