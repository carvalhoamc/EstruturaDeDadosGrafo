/**
 * Created by Alexandre Miguel de Carvalho on 25/06/17.
 * orcid.org/0000-0002-8801-4321
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define branco "BRANCO"
#define cinza "CINZA"
#define preto "PRETO"


using namespace std;


class V {

private:
    unsigned int id;
    string cor;
    string nome;
    int d;
    int f;
    int chave;
    bool visitado;
    V *paiPtr;

    void preparaVertice(){
        this->id = 0;
        this->cor = branco;
        this->nome = "0";
        this->d = std::numeric_limits<int>::max();
        this->f = 0;
        this->chave = 0;
        this->visitado = false;
        this->paiPtr = 0;
    }

public:


    V() {
        preparaVertice();
    };

    V(unsigned int id, string nome, string cor, int d, int f, int chave, bool visitado, V *paiPtr) {

        preparaVertice(); //garante valores padrao
        this->id = id;
        this->cor = cor;
        this->nome = nome;
        this->d = d;
        this->f = f;
        this->chave = chave;
        this->visitado = visitado;
        this->paiPtr = paiPtr;
    }

    V(unsigned int id, string nome, int chave){

        preparaVertice();
        this->id = id;
        this->nome = nome;
        this->chave = chave;

    }





    unsigned int getId() const {
        return id;
    }

    void setId(unsigned int id) {
        V::id = id;
    }

    const string &getCor() const {
        return cor;
    }

    void setCor(const string &cor) {
        V::cor = cor;
    }

    const string &getNome() const {
        return nome;
    }

    void setNome(const string &nome) {
        V::nome = nome;
    }

    int getD() const {
        return d;
    }

    void setD(int d) {
        V::d = d;
    }

    int getF() const {
        return f;
    }

    void setF(int f) {
        V::f = f;
    }

    int getChave() const {
        return chave;
    }

    void setChave(int chave) {
        V::chave = chave;
    }

    bool isVisitado() const {
        return visitado;
    }

    void setVisitado(bool visitado) {
        V::visitado = visitado;
    }

    V *getPaiPtr() const {
        return paiPtr;
    }

    void setPaiPtr(V *paiPtr) {
        V::paiPtr = paiPtr;
    }
};

class E {

private:

    unsigned int origem;
    unsigned int destino;
    float peso;


public:

    E() {
        origem = 0;
        destino = 0;
        peso = 0;
    };

    E(unsigned int origem, unsigned int destino, float peso) {
        E::setOrigem(origem);
        E::setDestino(destino);
        E::setPeso(peso);
    }

    unsigned int getOrigem() const {
        return origem;
    }

    void setOrigem(unsigned int origem) {
        E::origem = origem;
    }

    unsigned int getDestino() const {
        return destino;
    }

    void setDestino(unsigned int destino) {
        E::destino = destino;
    }

    float getPeso() const {
        return peso;
    }

    void setPeso(float peso) {
        E::peso = peso;
    }
};




class AdjListGraph{

private:
    unsigned int N; //numero de vertices
    std::vector <std::map<unsigned int , V*>> adjList; //lista de adjacencias
    std::map<unsigned int , V*> listaVmap; 
    list<E *> listaE; //lista de arestas
    list<E *> caminhoE; //lista de caminhos de arestas

    bool isDirecionado = true; //true -> direcionado
    bool isPonderado = true;   //true -> ponderado
    bool alteradaListaV = true; //true -> vertices alterados, atualizar listaE e adjlist
    bool alteradaListaE = true; //true -> arestas alteradas, atualizar adjlist

public:

    AdjListGraph(unsigned int N, bool isDirecionado, bool isPonderado) :
                                    N(N), isDirecionado(isDirecionado),
                                    isPonderado(isPonderado) {


    }

    unsigned int getN() const {
        return N;
    }

    const std::map<unsigned int , V*> &getListaV() const {
        return listaVmap;
    }

    const list<E *> &getListaE() const {
        return listaE;
    }

    const list<E *> &getCaminhoE() const {
        return caminhoE;
    }

    bool isIsDirecionado() const {
        return isDirecionado;
    }

    bool isIsPonderado() const {
        return isPonderado;
    }

    bool isAlteradaListaV() const {
        return alteradaListaV;
    }

    bool isAlteradaListaE() const {
        return alteradaListaE;
    }


    void criaVertice(unsigned int id, string nome, int chave) {

        V *novoPtr = new V(id,nome,chave);

        listaVmap.insert(make_pair(id,novoPtr));
        alteradaListaV = true;
        alteradaListaE = true;

    }

    void criaArestaById(int origem, int destino, float peso){

        V *origemPtr = findVerticeById(origem);
        V *destinoPtr = findVerticeById(destino);

        if((origemPtr != NULL) && (destinoPtr != NULL)){
            E *arestaPtr = new E(origemPtr->getId(), destinoPtr->getId(), peso);
            listaE.push_back(arestaPtr);
            alteradaListaE = true;
        }
    }

    V *findVerticeById(unsigned int id) {

        V *verticePtr = NULL;

        map<unsigned int , V*>::iterator it = listaVmap.find(id);
        verticePtr = (*it).second;

        return verticePtr;
    }

    void printListaV(){

        map<unsigned int , V*>::iterator indexListaV;

        for( indexListaV = begin(listaVmap); indexListaV != end(listaVmap); ++indexListaV){

            cout << "Chave do Vertice= " << (*indexListaV).first << endl;
            cout << "Dados dos Vertice" << "  ";
            cout << "nome:"<<(*indexListaV).second->getNome() << "  ";
            cout << "id:"<<(*indexListaV).second->getId() << "  ";
            cout << "chave:"<<(*indexListaV).second->getChave() << "  ";
            cout << "cor:"<<(*indexListaV).second->getCor() << "  ";
            cout << "d:"<<(*indexListaV).second->getD() << "  ";
            cout << "f:"<<(*indexListaV).second->getF() << "  ";
            cout << "Pai:"<<(*indexListaV).second->getPaiPtr() << "  ";
            cout << "Visitado:"<<(*indexListaV).second->isVisitado() << "  " << endl;

        }




    }

    void printListaE(){

        list<E *>::iterator indexListaE = begin(listaE);
        unsigned int vOrigem;
        unsigned int vDestino;


        while (indexListaE != end(listaE)) {

            vOrigem = (*indexListaE)->getOrigem();
            vDestino = (*indexListaE)->getDestino();
            cout << "(" << findVerticeById(vOrigem)->getId() << "," << findVerticeById(vDestino)->getId() << ")" << (*indexListaE)->getPeso() << endl;
            ++indexListaE;
        }
    }




    bool isVisitedById(unsigned int id){
        bool visitado = false;
        V *verticePtr = NULL;

        verticePtr = findVerticeById(id);
        if((verticePtr!= NULL)&&(verticePtr->isVisitado() == true)){
            visitado = true;
        }

        return visitado;

    }

    void BFS(int s){

        std::vector <std::map<unsigned int , V*>>::iterator itAdj = begin(adjList);
        map<unsigned int , V*>::iterator mapAdjListIt;
        map<unsigned int , V*>::iterator itV = begin(listaVmap);
        std::queue<int> Q;
        V* uPtr = NULL;
        V* vPtr = NULL;
        V* sPtr = NULL;

        int u = 0;
        int ud = 0;

        sPtr = findVerticeById(s);
        sPtr->setCor(cinza);
        sPtr->setD(0);
        sPtr->setPaiPtr(NULL);

        Q.empty();
        Q.emplace(s);

        while(!Q.empty()){
            u = Q.front();
            Q.pop();

            //for each v E Adj[u]
            for (mapAdjListIt = adjList[u].begin(); mapAdjListIt != adjList[u].end(); ++mapAdjListIt){
                vPtr = mapAdjListIt->second;
                uPtr = findVerticeById(u);

                if(vPtr->getCor() == branco){ //if v.color == white

                    vPtr->setCor(cinza);
                    vPtr->setD(uPtr->getD()+1);
                    vPtr->setPaiPtr(uPtr);
                    Q.emplace(vPtr->getId());
                }
            }

            uPtr->setCor(preto);
        }
    }

    void DFS(){



    }

    void criaAdjList(){

        if(isAlteradaListaE()||isAlteradaListaV()){

            adjList.resize(listaVmap.size());
            std::vector <std::map<unsigned int , V*>>::iterator itAdj = begin(adjList);
            list<E*>::iterator itE = begin(listaE);

            for(auto &&i : listaE){
                adjList[i->getOrigem()].insert(make_pair(i->getDestino(),findVerticeById(i->getDestino())));
            }

        }
    }

};






int main() {

    AdjListGraph *grafo = new AdjListGraph(6,true,false);
    grafo->criaVertice(0, "r", 0);
    grafo->criaVertice(1, "s", 0);
    grafo->criaVertice(2, "t", 0);
    grafo->criaVertice(3, "u", 0);
    grafo->criaVertice(4, "y", 0);
    grafo->criaVertice(5, "x", 0);
    grafo->criaVertice(6, "w", 0);
    grafo->criaVertice(7, "v", 0);


    grafo->criaArestaById(0, 1, 0);
    grafo->criaArestaById(0, 7, 0);
    grafo->criaArestaById(1, 0, 0);
    grafo->criaArestaById(1, 6, 0);
    grafo->criaArestaById(2, 3, 0);
    grafo->criaArestaById(2, 5, 0);
    grafo->criaArestaById(2, 6, 0);
    grafo->criaArestaById(3, 2, 0);
    grafo->criaArestaById(3, 4, 0);
    grafo->criaArestaById(3, 5, 0);
    grafo->criaArestaById(4, 3, 0);
    grafo->criaArestaById(4, 5, 0);
    grafo->criaArestaById(5, 4, 0);
    grafo->criaArestaById(5, 3, 0);
    grafo->criaArestaById(5, 2, 0);
    grafo->criaArestaById(5, 6, 0);
    grafo->criaArestaById(6, 5, 0);
    grafo->criaArestaById(6, 2, 0);
    grafo->criaArestaById(6, 1, 0);
    grafo->criaArestaById(7, 0, 0);




    grafo->printListaV();
    grafo->printListaE();
    grafo->criaAdjList();

    grafo->BFS(1);

    grafo->printListaV();
    grafo->printListaE();






    return 0;
}



/*

struct coordenadas{
    int X;
    int Y;
};


int N = 0;          //numero de cidades (vertices)
int Ci = 0;
string nomeCidade;
vector<coordenadas> latlong;



for (;;) {

cin >> N;
if (N == 0) break;

cin >> nomeCidade >> Ci;


for (int i = 1; i <= N; i++) {
for (int j = 1; j <= Ci; j++) {
cin >> latlong[j].X >> latlong[j].Y;


}
}

}*/
