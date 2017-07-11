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
#include <algorithm>
#include <iomanip>

#define branco "BRANCO"


using namespace std;


class V {

private:

    string cor;
    string nome;
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
        this->d = std::numeric_limits<float_t>::max();
        this->f = 0;
        this->chave = 0;
        this->visitado = false;
        this->paiPtr = 0;
        this->X = 0;
        this->Y = 0;
    }

public:

    float_t d;
    unsigned int id;

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

    unsigned int getId() const {
        return id;
    }

    const string &getNome() const {
        return nome;
    }
};

class vertice{
public:
    float_t* dist;
    unsigned *id = 0;

    explicit vertice(float_t* d, unsigned int* i) : dist(d), id(i){}
};

class AdjListGraph {

private:
    unsigned int N; //numero de vertices
    std::vector<std::map<unsigned int, V *>> adjList; //lista de adjacencias
    std::map<unsigned int, V*> listaVmap; //lista de vertices onde um inteiro e a chave unica

    bool isDirecionado = true; //true -> direcionado
    bool isPonderado = true;   //true -> ponderado

public:

    AdjListGraph(unsigned int N, bool isDirecionado, bool isPonderado) :
            N(N), isDirecionado(isDirecionado),
            isPonderado(isPonderado) {
    }

    //Min priority queue
    template<class T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
    min_heap<float_t > Qpriority;

    struct distancias{
        int cidade1;
        int cidade2;
        float_t distancia;

        bool operator() (distancias i, distancias j) { return  (i.distancia < j.distancia);}
    } D;

    vector<vector<distancias>> Md; //linha 0 distancia entre cidade0 e cidade1
    distancias dTemp;
    vector<distancias> linhaDaMatriz;

    unsigned int getListaVmapSize(){
        return listaVmap.size();
    }


    void criaVertice(unsigned int id, string nome, int chave, int x, int y) {
        V *novoPtr = new V(id, nome, chave, x, y);

        listaVmap.insert(make_pair(id, novoPtr));

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

    float_t methodAMC(unsigned int numeroDistancias){
        unsigned int tamanho = Md.front().size();
        vector<float_t> soma(tamanho); //resultado das somas

        struct menorQueDist{
            bool operator()(float_t v1,float_t v2 ) const {
                return v1 > v2;
            }
        };

        vector<vector<distancias>>::iterator it = Md.begin();
        vector<distancias> rootTree;
        rootTree.assign(Md[0].begin(), Md[0].end());

        for(int i = 0; i < rootTree.size(); ++i){

            unsigned int di = 0;
            unsigned int k = 0;

            dTemp = rootTree.at(i);

            for (di = 1; di < numeroDistancias; ++di) {  //percorre linha a linha
                unsigned int tamanho = Md[di].size();

                for (int j = 0; j < tamanho; j++) {
                    if ((dTemp.cidade1 == Md[di][j].cidade1) ||
                        (dTemp.cidade1 == Md[di][j].cidade2) ||
                        (dTemp.cidade2 == Md[di][j].cidade1) ||
                        (dTemp.cidade2 == Md[di][j].cidade2)) {
                        soma[i] += (dTemp.distancia + Md[di][j].distancia);
                        dTemp = Md[di][j];
                        break;
                    }
                }
            }
        }
        std::make_heap(soma.begin(), soma.end(),menorQueDist() );
        return soma.front();
    }

};

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
    float_t distancia = 0.0;
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

            grafo->linhaDaMatriz.clear();
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
                    vTemp = grafo->findVerticeByName(origem+":"+std::to_string(x1)+":"+std::to_string(y1));
                    o = vTemp->getId();
                    vTemp = grafo->findVerticeByName(destino+":"+std::to_string(x2)+":"+std::to_string(y2));
                    d = vTemp->getId();
                    grafo->dTemp.cidade1 = o;
                    grafo->dTemp.cidade2 = d;
                    grafo->dTemp.distancia = distancia;
                    grafo->linhaDaMatriz.emplace_back(grafo->dTemp);
                }
            }
            std::sort(grafo->linhaDaMatriz.begin(), grafo->linhaDaMatriz.end(), grafo->D );
            grafo->Md.emplace_back(grafo->linhaDaMatriz);
        }
        grafo->linhaDaMatriz.clear();
        cout << std::fixed << std::setprecision(1) << grafo->methodAMC(N-1) << endl;

    }
    return 0;
}