#include "../include/graph.hpp"

void graph::addEdges(int a, int b) {

    this->adj[a].push_back(b);

}

void graph::addEdgesInv(int a, int b) {

    this->adjInv[b].push_back(a);

}

void graph::dfsFirst(int u) {
    if(visited[u])
        return;
    visited[u] = 1;
    //if(adj[u].size() > 0)
        for(int i = 0; i <adj[u].size();i++){
            dfsFirst(adj[u][i]);
        }   
    //if(adj[u].size() > 0)
        pilha.push(u);
}

void graph::dfsSecond(int u)
{
    if(visitedInv[u])
        return;
    visitedInv[u] = 1;
    //if(adj[u].size() > 0)
        for (int i=0;i<adjInv[u].size();i++)
            dfsSecond(adjInv[u][i]);
    scc[u] = counter;
}

void graph::is2sat(int n, int m, int a[], int b[]) {
    
    for(int i = 0; i < m; i++) {
        //x eh mapeado para x
        //-x eh mapeado para n+x = n - (-x)

        //para a[i] or b[i], addEdges -a[i] -> b[i]
        //AND -b[i] -> a[i]

        //ex:<-3,-4>
        if(a[i] < 0 && b[i] < 0) {
            addEdges(-a[i], n - b[i]);
            addEdgesInv(-a[i], n - b[i]);
            addEdges(-b[i], n-a[i]);
            addEdgesInv(-b[i], n-a[i]);
        }

        //ex:<3,4>
        if(a[i] > 0 && b[i] > 0) {
            addEdges(a[i] + n, b[i]);
            addEdges(b[i] + n, a[i]);
            addEdgesInv(a[i] + n, b[i]);
            addEdgesInv(b[i] + n, a[i]);
        }

        //ex:<0,2>
        if(a[i]==0 && b[i] > 0) {
            cout << "i que popula addEdges: " << i << endl;
            cout << "b[i]: " << b[i] << endl;
            addEdges(b[i], b[i]);
            addEdgesInv(b[i], b[i]);
        }

        //ex:<2,0>
        if(a[i] > 0 && b[i]==0) {
            cout << "i que popula addEdges: " << i << endl;
            cout << "a[i]: " << a[i] << endl;
            addEdges(a[i], a[i]);
            addEdgesInv(a[i], a[i]);
        }

        //ex:<0,-2>
        if(a[i]==0 && b[i] < 0) {
            cout << "i que popula addEdges: " << i << endl;
            cout << "n-b[i]: " << n-b[i] << endl;
            addEdges(n-b[i], n-b[i]);
            addEdgesInv(n-b[i], n-b[i]);
        }

        //ex:<-2,0>
        if(a[i] < 0 && b[i] == 0) {
            cout << "i que popula addEdges: " << i << endl;
            cout << "n-a[i]: " << n-a[i] << endl;
            addEdges(n-a[i], n-a[i]);
            addEdgesInv(n-a[i], n-a[i]);
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
            cout << "N??o"
                 << endl;
            return;
        }
    }

    // Caso n??o exista x, tal que x e -x n??o estiverem na mesma CFC
    cout << "Sim"
         << endl;
    return; 
}