#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "../include/campanha.hpp"
#include "../include/seguidor.hpp"
#include "../include/graph.hpp"


using namespace std;

//funcao para preencher os vetores de literais
void fillLiteral(int *a, int *b, seguidor f) {

  int aux = 0;

  for(int i = 0; i < f.S; i++)
    for(const auto &iterator:f.follower[i]){
      a[aux] = iterator.first;
      b[aux] = iterator.second;
      aux++;
    }

}

//le entrada e preenche valores das variaveis
void fillVariables(string fileName, seguidor *seguidores) {

  //cria e le o arquivo *.txt
  ifstream FILE(fileName);

  //caso leitura do arquivo nao seja viavel
  if(!FILE.is_open())
    {
      cout << "File could not be opened" << endl;
      exit(1);
    }

  //S e P artificiais
  int S, P;

  //par que sera avaliado
  pair<int,int> par;

  //palavras do arquivo
  string token;

  while(FILE >> token)
  {
    //preenche S e P artificiais
    S = stoi(token);
    FILE>>token;
    P = stoi(token);
    FILE>>token;

    //testa se devemos encerrar a leitra
    if(S==0 && P==0)
      break;

    //obtem os valores S e P
    seguidores->S = S;
    seguidores->P = P;

    seguidores->follower = new list<pair<int,int>>[seguidores->S];

    //preenchemos o vetor de lista
    for(int i = 0; i < seguidores->S; i++) {
        par.first = stoi(token);
        //cout << par.first << endl;
        FILE>>token;
        par.second = stoi(token);
        //cout << par.second << endl;
        //adicionamos o par de aprovacoes do seguidor 'i' na lista
        seguidores->addEdge(par, i);
        FILE>>token;
        par.first = -stoi(token);
        FILE>>token;
        par.second = -stoi(token);
        if(i != seguidores->S - 1)
          FILE>>token;
        seguidores->addEdge(par, i);
    } 

    //vetores com os literais
    int clausulas = seguidores->S * 2;
    int primeiroLiteral[clausulas];
    int segundoLiteral[clausulas];

    //preenchendo os arrays com os literais
    fillLiteral(primeiroLiteral, segundoLiteral, *seguidores);

    
    //imprimindo o grafo
    //cout << "S: " << S << " P: " << P << endl;
    //seguidores->imprimeGrafo();

    //inicializamos o grafo
    graph grafo(seguidores->P, clausulas);

    //verificamos satisfatibilidade
    grafo.is2sat(seguidores->P, clausulas, primeiroLiteral, segundoLiteral);

  }

  FILE.close();
}

/* //funcao para verificar satisfatibilidade
void twoSat(int propostas, int clausulas, int a[], int b[]) {

} */

int main(int argc, char ** argv) {

  /*
    S (seguidores) P (propostas)
    X_1 e X_2 -> Seguidor deseja manter
    Y_1 e Y_2 -> Seguidor deseja retirar do plano de campanha
    if 0 -> nao quer opinar
  */

  //inicializando o grafo
  seguidor seguidores;

  //nome do arquivo de entrada
  std::string fileName = argv[1];

  //preenche as variaveis
  fillVariables(fileName, &seguidores);

  /*
  //definir o numero de propostas e clausulas
  int propostas = seguidores.P;
  int clausulas = seguidores.S * 2; //cada seguidor possui duas clausulas (x_1+x_2)*(y_1+y_2)

  //definir os vetores das primeiros (a) e segundos (b) literais
  int primeiroLiteral[clausulas];
  int segundoLiteral[clausulas];

  //vamos agora preencher o grafo com as implicacoes
  //x_1 + x_2 se torna ¬x_1 -> x_2 && ¬x_2 -> x_1

  //inicializamos o grafo
  graph grafo(propostas, clausulas);

  //preenche os vetores
  fillLiteral(primeiroLiteral, segundoLiteral, seguidores);

  //populamos o grafo com as implicacoes
  grafo.is2sat(propostas, clausulas, primeiroLiteral, segundoLiteral);

  //imprime o grafo
  seguidores.imprimeGrafo();

  // call a function in another file
  //test();
  */

  return(0);
}
