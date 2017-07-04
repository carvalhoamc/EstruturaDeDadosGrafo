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
#include <cmath>
#include <cstdlib>

#define branco "BRANCO"
#define cinza "CINZA"
#define preto "PRETO"
#define infitino 900000.0


using namespace std;


class V {

private:
    unsigned int id;
    string cor;
    string nome;
    float d;
    int f;
    int chave;
    bool visitado;
    V *paiPtr;
    int X; //latitude
    int Y; //longitude

    void preparaVertice() {
        this->id = 0;
        this->cor = branco;
        this->nome = "0";
        this->d = std::numeric_limits<float>::max();
        this->f = 0;
        this->chave = 0;
        this->visitado = false;
        this->paiPtr = 0;
        this->X = 0;
        this->Y = 0;
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

    V(unsigned int id, string nome, int chave) {

        preparaVertice();
        this->id = id;
        this->nome = nome;
        this->chave = chave;

    }
    V(unsigned int id, string nome, int chave, int x, int y) {

        preparaVertice();
        this->id = id;
        this->nome = nome;
        this->chave = chave;
        this->X = x;
        this->Y = y;
    }


    int getX() const {
        return X;
    }

    void setX(int X) {
        V::X = X;
    }

    int getY() const {
        return Y;
    }

    void setY(int Y) {
        V::Y = Y;
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

    float getD() const {
        return d;
    }

    void setD(float d) {
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

    string chave;
    unsigned int origem;
    unsigned int destino;
    float peso;

public:

    E() {
        origem = 0;
        destino = 0;
        peso = 0;
        E::setChave(std::to_string(origem) + std::to_string(destino));
    };

    E(unsigned int origem, unsigned int destino, float peso) {
        E::setOrigem(origem);
        E::setDestino(destino);
        E::setPeso(peso);
        E::setChave(std::to_string(origem) + std::to_string(destino));
    }

    const string &getChave() const {
        return chave;
    }

    void setChave(const string &chave) {
        E::chave = chave;
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


class AdjListGraph {

private:
    unsigned int N; //numero de vertices
    std::vector<std::map<unsigned int, V *>> adjList; //lista de adjacencias
    std::map<unsigned int, V *> listaVmap; //lista de vertices onde um inteiro e a chave unica
    std::map<std::string, E *> listaEmap;   //lista de arestas onde a combinacao de origem-destino formam a chave string

    bool isDirecionado = true; //true -> direcionado
    bool isPonderado = true;   //true -> ponderado
    bool alteradaListaV = true; //true -> vertices alterados, atualizar listaE e adjlist
    bool alteradaListaE = true; //true -> arestas alteradas, atualizar adjlist
    int tempo = 0;

public:

    AdjListGraph(unsigned int N, bool isDirecionado, bool isPonderado) :
            N(N), isDirecionado(isDirecionado),
            isPonderado(isPonderado) {
    }

    //Min priority queue
    template<class T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
    min_heap<int> Qpriority;
    min_heap<std::map<unsigned int, V *> > Qdminimo;


    unsigned int getListaVmapSize(){
        return listaVmap.size();
    }

    int getTempo() const {
        return tempo;
    }

    void setTempo(int tempo) {
        AdjListGraph::tempo = tempo;
    }

    unsigned int getN() const {
        return N;
    }

    const std::map<unsigned int, V *> &getListaV() const {
        return listaVmap;
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

    const map<string, E *> &getListaEmap() const {
        return listaEmap;
    }

    void setListaEmap(const map<string, E *> &listaEmap) {
        AdjListGraph::listaEmap = listaEmap;
    }

    void criaVertice(unsigned int id, string nome, int chave) {

        V *novoPtr = new V(id, nome, chave);

        listaVmap.insert(make_pair(id, novoPtr));
        alteradaListaV = true;
        alteradaListaE = true;

    }

    void criaVertice(unsigned int id, string nome, int chave, int x, int y) {

        V *novoPtr = new V(id, nome, chave, x, y);

        listaVmap.insert(make_pair(id, novoPtr));
        alteradaListaV = true;
        alteradaListaE = true;

    }

    void criaArestaById(int origem, int destino, float peso) {

        V *origemPtr = findVerticeById(origem);
        V *destinoPtr = findVerticeById(destino);

        if ((origemPtr != NULL) && (destinoPtr != NULL)) {
            E *arestaPtr = new E(origemPtr->getId(), destinoPtr->getId(), peso);
            listaEmap.insert(make_pair(arestaPtr->getChave(), arestaPtr));
            alteradaListaE = true;
        }
    }

    E *findArestaById(string chave) {

        E *arestaPtr = NULL;

        std::map<std::string, E *>::iterator it = listaEmap.find(chave);
        arestaPtr = (*it).second;
        return arestaPtr;
    }

    V *findVerticeById(unsigned int id) {

        V *verticePtr = NULL;

        map<unsigned int, V *>::iterator it = listaVmap.find(id);
        verticePtr = (*it).second;

        return verticePtr;
    }

    V *findVerticeByName(string nome){
        map<unsigned int, V *>::iterator indexListaV;
        V *vPtr = NULL;

        for (indexListaV = begin(listaVmap); indexListaV != end(listaVmap); ++indexListaV) {

            if ((*indexListaV).second->getNome() == nome){
                vPtr = (*indexListaV).second;
                return vPtr;
            }
        }
        return vPtr;
    }

    void printListaV() {

        map<unsigned int, V *>::iterator indexListaV;
        V *paiPtr = NULL;

        for (indexListaV = begin(listaVmap); indexListaV != end(listaVmap); ++indexListaV) {

            //cout << "Chave do Vertice:" << (*indexListaV).first << "  ";
            cout << "Nome do Vertice:" << (*indexListaV).second->getNome() << "  ";
            cout << "id:" << (*indexListaV).second->getId() << "  ";
            paiPtr = (*indexListaV).second->getPaiPtr();
            if (paiPtr == NULL) {
                cout << "id Pai:" << (*indexListaV).second->getId() << "   ";
            } else {
                cout << "id Pai:" << paiPtr->getId() << "   ";
            }
            //cout << "chave:" << (*indexListaV).second->getChave() << "  ";
            cout << "cor:" << (*indexListaV).second->getCor() << "  ";
            cout << "d:" << (*indexListaV).second->getD() << "  ";
            //cout << "f:" << (*indexListaV).second->getF() << "  ";
            cout << "Pai:" << (*indexListaV).second->getPaiPtr() << "  ";
            cout << "Visitado:" << (*indexListaV).second->isVisitado() << "  " << endl;
        }
    }

    void printListaE() {

        std::map<std::string, E *>::iterator indexListaE;
        unsigned int vOrigem;
        unsigned int vDestino;

        for (indexListaE = begin(listaEmap); indexListaE != end(listaEmap); ++indexListaE) {

            vOrigem = (*indexListaE).second->getOrigem();
            vDestino = (*indexListaE).second->getDestino();
            cout << "(" << findVerticeById(vOrigem)->getId() << "," << findVerticeById(vDestino)->getId() << ")"
                 << (*indexListaE).second->getPeso() << endl;
        }
    }

    bool isVisitedById(unsigned int id) {
        bool visitado = false;
        V *verticePtr = NULL;

        verticePtr = findVerticeById(id);
        if ((verticePtr != NULL) && (verticePtr->isVisitado() == true)) {
            visitado = true;
        }

        return visitado;
    }

    void BFS(int s) {

        map<unsigned int, V *>::iterator mapAdjListIt;
        map<unsigned int, V *>::iterator itV;
        std::queue<int> Q;
        V *uPtr = NULL;
        V *vPtr = NULL;
        V *sPtr = NULL;
        int u = 0;

        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {

            itV->second->setCor(branco);
            itV->second->setPaiPtr(NULL);
            itV->second->setD(infitino);
        }

        sPtr = findVerticeById(s);
        sPtr->setCor(cinza);
        sPtr->setD(0);
        sPtr->setPaiPtr(NULL);

        Q.empty();
        Q.emplace(s);

        while (!Q.empty()) {
            u = Q.front();
            Q.pop();

            //for each v E Adj[u]
            for (mapAdjListIt = adjList[u].begin(); mapAdjListIt != adjList[u].end(); ++mapAdjListIt) {
                vPtr = mapAdjListIt->second;
                uPtr = findVerticeById(u);
                if (vPtr->getCor() == branco) { //if v.color == white
                    vPtr->setCor(cinza);
                    vPtr->setD(uPtr->getD() + 1);
                    vPtr->setPaiPtr(uPtr);
                    Q.emplace(vPtr->getId());
                }
            }
            uPtr->setCor(preto);
        }
    }

    void printPathBFS(int s, int v) {
        V *vPtr = NULL;
        V *sPtr = NULL;

        vPtr = findVerticeById(v);
        sPtr = findVerticeById(s);

        if(s == v){
            cout << s << ", " ;
        }else if(vPtr->getPaiPtr() == NULL){
            cout << s << " to " << v << " Não existe " ;
        }else{
            printPathBFS(s,vPtr->getPaiPtr()->getId());
            cout << v << ", ";
        }

    }


    void BFSDig(int s) {

        map<unsigned int, V *>::iterator mapAdjListIt;
        map<unsigned int, V *>::iterator itV;
        std::queue<int> Q;
        V *uPtr = NULL;
        V *vPtr = NULL;
        V *sPtr = NULL;
        int u = 0;
        int v = 0;
        E *arestaPtr = NULL;
        float W = 0;

        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {

            itV->second->setCor(branco);
            itV->second->setPaiPtr(NULL);
            itV->second->setD(infitino);
        }

        sPtr = findVerticeById(s);
        //cout << "defeito S: " << sPtr;
        sPtr->setCor(cinza);
        sPtr->setD(0.0); //distancia
        sPtr->setPaiPtr(NULL);

        Q.empty();
        Q.emplace(s);

        while (!Q.empty()) {
            u = Q.front();
            Q.pop();

            //for each v E Adj[u]
            for (mapAdjListIt = adjList[u].begin(); mapAdjListIt != adjList[u].end(); ++mapAdjListIt) {
                vPtr = mapAdjListIt->second;
                uPtr = findVerticeById(u);
                v = vPtr->getId();
                if (vPtr->getCor() == branco) { //if v.color == white
                    vPtr->setCor(cinza);

                    arestaPtr = findArestaById(std::to_string(u) + std::to_string(v));
                    W = arestaPtr->getPeso();

                    vPtr->setD(uPtr->getD() + W);
                    vPtr->setPaiPtr(uPtr);
                    Q.emplace(vPtr->getId());
                }
            }
            uPtr->setCor(preto);
        }
    }



    void DFS() {
        map<unsigned int, V *>::iterator itV;

        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {

            itV->second->setCor(branco);
            itV->second->setPaiPtr(NULL);
        }

        AdjListGraph::tempo = 0;

        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {

            if (itV->second->getCor() == branco) {

                DFSVisit(itV->second->getId());
            }
        }
    }

    void DFSVisit(int u) {

        map<unsigned int, V *>::iterator mapAdjListIt;
        map<unsigned int, V *>::iterator itV = begin(listaVmap);
        std::queue<int> Q;
        V *uPtr = NULL;
        V *vPtr = NULL;

        ++AdjListGraph::tempo;
        uPtr = findVerticeById(u);
        uPtr->setD(AdjListGraph::tempo);
        uPtr->setCor(cinza);

        //for each v E Adj[u]
        for (mapAdjListIt = adjList[u].begin(); mapAdjListIt != adjList[u].end(); ++mapAdjListIt) {
            vPtr = mapAdjListIt->second;
            if (vPtr->getCor() == branco) { //if v.color == white
                vPtr->setPaiPtr(uPtr);
                DFSVisit(vPtr->getId());
            }
        }
        uPtr->setCor(preto);
        ++AdjListGraph::tempo;
        uPtr->setF(AdjListGraph::tempo);
    }

    //Cormen 613
    void topologicalSort() {

        DFS();

    }

    //Cormen 634
    void MSTPrim(int r) {


        map<unsigned int, V *>::iterator mapAdjListIt;
        map<unsigned int, V *>::iterator itV = begin(listaVmap);
        std::map<std::string, E *>::iterator itE = begin(listaEmap);

        V *uPtr = NULL;
        V *rPtr = NULL;
        V *vPtr = NULL;
        E *arestaPtr = NULL;
        int u = 0;
        int v = 0;

        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {
            itV->second->setPaiPtr(NULL);
            itV->second->setChave(std::numeric_limits<int>::max());
            itV->second->setCor(branco);
        }
        rPtr = findVerticeById(r);
        rPtr->setChave(0);
        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {
            Qpriority.emplace(itV->first);
        }
        while (!Qpriority.empty()) {
            u = Qpriority.top(); //acessa
            Qpriority.pop();     //retira
            uPtr = findVerticeById(u);

            //for each v E Adj[u]
            for (mapAdjListIt = adjList[u].begin(); mapAdjListIt != adjList[u].end(); ++mapAdjListIt) {
                vPtr = mapAdjListIt->second;
                arestaPtr = findArestaById(std::to_string(u) + std::to_string(vPtr->getId()));
                if ((vPtr->getCor() == branco) && (arestaPtr->getPeso() < vPtr->getChave())) {
                    vPtr->setChave(arestaPtr->getPeso());
                    vPtr->setPaiPtr(uPtr);
                }
            }
            uPtr->setCor(preto);
        }
    }

    void ISS(unsigned int s){

        map<unsigned int, V *>::iterator itV = begin(listaVmap);

        V *sPtr = findVerticeById(s);
        sPtr->setD(0);

        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {
            itV->second->setCor(branco);
            itV->second->setPaiPtr(NULL);
            itV->second->setD(infitino);
        }
    }

    void Relax(unsigned int u, unsigned int v, float peso){

        V *uPtr = findVerticeById(u);
        V *vPtr = findVerticeById(v);

        if(vPtr->getD() > (uPtr->getD() + peso)){
            vPtr->setD(uPtr->getD() + peso);
            vPtr->setPaiPtr(uPtr);
        }
    }



    //Cormen 658
    void Dijkstra(unsigned int s) {

        map<unsigned int, V *>::iterator mapAdjListIt;
        map<unsigned int, V *>::iterator itV;
        V *sPtr = NULL;
        V *uPtr = NULL;
        V *vPtr = NULL;
        E *arestaPtr = NULL;
        unsigned int u = 0;
        unsigned int v = 0;
        vector<unsigned int> S;

        ISS(s);
        while (!Qdminimo.empty()){ //esvazia
            Qdminimo.pop();
        }

        for (itV = begin(listaVmap); itV != end(listaVmap); ++itV) {
            Qdminimo.emplace(itV->second->getD());
        }

        while (!Qdminimo.empty()) {
           // u = Qdminimo.top(); //acessa
            Qdminimo.pop();     //retira
            S.push_back(u);

            //for each v E Adj[u]
            for (mapAdjListIt = adjList[u].begin(); mapAdjListIt != adjList[u].end(); ++mapAdjListIt) {
                vPtr = mapAdjListIt->second;
                arestaPtr = findArestaById(std::to_string(u) + std::to_string(vPtr->getId()));
                Relax(u, v, arestaPtr->getPeso());
            }
        }

        for(int i = 0; i < S.size(); ++i){
            cout << S.at(i) << " ";
        }

    }


    void criaAdjList() {

        if (isAlteradaListaE() || isAlteradaListaV()) {
            adjList.resize(listaVmap.size());
            std::vector<std::map<unsigned int, V *>>::iterator itAdj = begin(adjList);
            std::map<std::string, E *>::iterator indexListaE;
            unsigned int vOrigem;
            unsigned int vDestino;

            for (indexListaE = begin(listaEmap); indexListaE != end(listaEmap); ++indexListaE) {
                vOrigem = (*indexListaE).second->getOrigem();
                vDestino = (*indexListaE).second->getDestino();
                adjList[vOrigem].insert(make_pair(vDestino, findVerticeById(vDestino)));
            }
        }
    }

    void limpaAdjList() {

        adjList.clear();
    }

    void limpaArestas() {

        listaEmap.clear();
    }

    void limpaVertices() {

        listaVmap.clear();
        limpaArestas();
        limpaAdjList();
    }
};

/*
int main() {

    unsigned int ID = 0;

    struct coordenadas{
        int X;
        int Y;
    };

    vector<coordenadas> latlong;

    std::map<string, vector<coordenadas>> listaCidades; //chave = nomeDaCidade
    std::map<string, vector<coordenadas>>::iterator itOrigem = begin(listaCidades);
    std::map<string, vector<coordenadas>>::iterator itDestino = begin(listaCidades);

    int N = 0;          //numero de cidades (vertices)
    int Ci = 0;
    string nomeCidade;
    string origem;
    string destino;
    int o; //origem
    int d; //destino
    V* vTemp = NULL;
    float distancia = 0.0;
    int x1, y1, x2, y2;

    int x = 0;
    int y = 0;
    coordenadas temp;
    AdjListGraph *grafo;

    for (;;) {

        listaCidades.clear();
        cin >> N;
        if (N == 0) break;
        grafo = new AdjListGraph(N,true,false);
        for (int i = 0; i < N; i++) {

            cin >> nomeCidade >> Ci;

            latlong.clear();

            for (int j = 0; j < Ci; j++) {
                cin >> x >> y;
                temp.X = x;
                temp.Y = y;

                grafo->criaVertice(ID, nomeCidade+":"+std::to_string(x)+":"+std::to_string(y), 0, x, y);
                ++ID;


                latlong.push_back(temp);
            }
            listaCidades.insert(make_pair(nomeCidade, latlong));
        }



        for(int k = 0; k < (N-1); k++) {

            cin >> origem >> destino;

            itOrigem = listaCidades.find(origem);
            itDestino = listaCidades.find(destino);

            for(int indiceOrigem = 0; indiceOrigem < (*itOrigem).second.size(); indiceOrigem++){
                for(int indiceDestino = 0; indiceDestino < (*itDestino).second.size(); indiceDestino++){

                    x1 = (*itOrigem).second[indiceOrigem].X;
                    y1 = (*itOrigem).second[indiceOrigem].Y;

                    x2 = (*itDestino).second[indiceDestino].X;
                    y2 = (*itDestino).second[indiceDestino].Y;

                    distancia = sqrtf(pow(x1 - x2, 2) + pow(y1 - y2, 2));
                    cout << distancia << endl;

                    vTemp = grafo->findVerticeByName(origem+":"+std::to_string(x1)+":"+std::to_string(y1));
                    o = vTemp->getId();
                    vTemp = grafo->findVerticeByName(destino+":"+std::to_string(x2)+":"+std::to_string(y2));
                    d = vTemp->getId();



                    grafo->criaArestaById(o, d, distancia);
                    grafo->criaArestaById(d, o, distancia);

                }
            }





        }

        grafo->printListaV();
        grafo->printListaE();
        grafo->criaAdjList();

        int t = grafo->getListaVmapSize();

        float matrizDistancia[t][t];

        for( int i = 0; i < t; ++i){
            for(int j = 0; j < t; ++j){
                grafo->BFS(0);
                matrizDistancia[i][j] = grafo->findVerticeById(j)->getD();
            }
        }

        cout << "fim" << endl;



        grafo->limpaArestas();
        grafo->limpaVertices();
        grafo->criaAdjList();

    }




    return 0;
}
*/

int main() {


    AdjListGraph *grafo = new AdjListGraph(8, true, false);
    grafo->criaVertice(0, "r", 0);
    grafo->criaVertice(1, "s", 0);
    grafo->criaVertice(2, "t", 0);
    grafo->criaVertice(3, "u", 0);
    grafo->criaVertice(4, "y", 0);
    grafo->criaVertice(5, "x", 0);
    grafo->criaVertice(6, "w", 0);
    grafo->criaVertice(7, "v", 0);

    grafo->criaArestaById(0, 1, 20);
    grafo->criaArestaById(0, 7, 20);
    grafo->criaArestaById(1, 0, 20);
    grafo->criaArestaById(1, 6, 20);
    grafo->criaArestaById(2, 3, 20);
    grafo->criaArestaById(2, 5, 20);
    grafo->criaArestaById(2, 6, 20);
    grafo->criaArestaById(3, 2, 20);
    grafo->criaArestaById(3, 4, 20);
    grafo->criaArestaById(3, 5, 20);
    grafo->criaArestaById(4, 3, 20);
    grafo->criaArestaById(4, 5, 200);
    grafo->criaArestaById(5, 4, 200);
    grafo->criaArestaById(5, 3, 20);
    grafo->criaArestaById(5, 2, 20);
    grafo->criaArestaById(5, 6, 20);
    grafo->criaArestaById(6, 5, 20);
    grafo->criaArestaById(6, 2, 20);
    grafo->criaArestaById(6, 1, 20);
    grafo->criaArestaById(7, 0, 20);

    grafo->printListaV();
    grafo->printListaE();
    grafo->criaAdjList();

    grafo->Dijkstra(0);
    //cout << "Dijkstra result:" << endl;
    //grafo->printListaV();
    //grafo->printPathBFS(0,4);
}

 /*
   grafo->limpaVertices();

   AdjListGraph *grafo = new AdjListGraph(6,true,false);
   grafo->criaVertice(0, "u", 0);
   grafo->criaVertice(1, "v", 0);
   grafo->criaVertice(2, "w", 0);
   grafo->criaVertice(3, "z", 0);
   grafo->criaVertice(4, "y", 0);
   grafo->criaVertice(5, "x", 0);

   grafo->criaArestaById(0, 1, 1);
   grafo->criaArestaById(0, 5, 5);
   grafo->criaArestaById(1, 4, 14);
   grafo->criaArestaById(2, 4, 24);
   grafo->criaArestaById(2, 3, 23);
   grafo->criaArestaById(3, 3, 33);
   grafo->criaArestaById(4, 5, 45);
   grafo->criaArestaById(5, 1, 51);

   grafo->printListaV();
   grafo->printListaE();

   grafo->criaAdjList();

   grafo->DFS();
   cout << "DFS result:" << endl;
   grafo->printListaV();
   grafo->printListaE();

    AdjListGraph *grafo = new AdjListGraph(9, true, false);
    grafo->criaVertice(0, "a", 0);
    grafo->criaVertice(1, "b", 0);
    grafo->criaVertice(2, "c", 0);
    grafo->criaVertice(3, "d", 0);
    grafo->criaVertice(4, "e", 0);
    grafo->criaVertice(5, "f", 0);
    grafo->criaVertice(6, "g", 0);
    grafo->criaVertice(7, "h", 0);
    grafo->criaVertice(8, "i", 0);

    grafo->criaArestaById(0, 1, 4);
    grafo->criaArestaById(1, 0, 4);

    grafo->criaArestaById(1, 2, 8);
    grafo->criaArestaById(2, 1, 8);

    grafo->criaArestaById(2, 3, 7);
    grafo->criaArestaById(3, 2, 7);

    grafo->criaArestaById(3, 4, 9);
    grafo->criaArestaById(4, 3, 9);

    grafo->criaArestaById(4, 5, 10);
    grafo->criaArestaById(5, 4, 10);

    grafo->criaArestaById(3, 5, 14);
    grafo->criaArestaById(5, 3, 14);

    grafo->criaArestaById(5, 2, 4);
    grafo->criaArestaById(2, 5, 4);

    grafo->criaArestaById(2, 8, 2);
    grafo->criaArestaById(8, 2, 2);

    grafo->criaArestaById(5, 6, 2);
    grafo->criaArestaById(6, 5, 2);

    grafo->criaArestaById(8, 6, 6);
    grafo->criaArestaById(6, 8, 6);

    grafo->criaArestaById(8, 7, 7);
    grafo->criaArestaById(7, 8, 7);

    grafo->criaArestaById(6, 7, 0);
    grafo->criaArestaById(7, 6, 0);

    grafo->criaArestaById(1, 7, 11);
    grafo->criaArestaById(7, 1, 11);

    grafo->criaArestaById(0, 7, 8);
    grafo->criaArestaById(7, 0, 8);

    grafo->printListaV();
    grafo->printListaE();
    grafo->criaAdjList();
    grafo->MSTPrim(0);

    cout << endl << "MSTPrim result:" << endl;
    grafo->printListaV();
    grafo->printListaE();


*/
