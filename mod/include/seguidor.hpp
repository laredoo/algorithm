#ifndef SEGUIDOR_H
#define SEGUIDOR_H

#include <iostream>
#include <string>
#include <utility>
#include <list>

using namespace std;

class seguidor{

    public:

        int S;
        int P;
        
        //Array de lista
        list<pair<int,int>> *follower;

        seguidor() {}

        seguidor(int S, int P) {
            this->S = S;
            this->P = P;
            follower = new list<pair<int,int>>[this->S];
        }

        void addEdge(pair<int,int> follower_pair, int seguidor);

        void imprimeLista(list<pair<int,int>> lista);

        void imprimeGrafo();

};


#endif