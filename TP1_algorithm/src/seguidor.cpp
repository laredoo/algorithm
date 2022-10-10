#include <iostream>
#include <string>
#include <utility>
#include <list>
#include "../include/seguidor.hpp"

using namespace std;

void seguidor::addEdge(pair<int,int> follower_pair, int seguidor) {
    follower[seguidor].push_back(follower_pair);
}

void seguidor::imprimeLista(list<pair<int,int>> lista) {
    for(const auto& iterator: lista)
            cout << iterator.first << ", " << iterator.second << endl;
}

void seguidor::imprimeGrafo() {
    for(int i = 0; i < this->S; i++)
        for(const auto& iterator: follower[i])
            cout << iterator.first << ", " << iterator.second << endl;
}

void seguidor::negRemover() {
}
