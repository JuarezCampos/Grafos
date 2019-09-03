#include <random>
#include "Classes/MenuPrincipal.h"
#include "Classes/Grafo.h"
#include "Classes/Aresta.h"
#include "Classes/No.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>

using namespace std;

/**
 * Metodo para leitura dos dados do arquivo e criacao do grafo de acordo com sua definicao.
 * @param arqEntrada caminho do arquivo de entrada.
 * @param direcionado 0 para grafo nao direcionado e 1 para grafo direcionado.
 * @param ponderadoAresta 0 para grafo nao ponderado nas arestas e 1 para grafo ponderado nas arestas.
 * @param ponderadoNo 0 para grafo nao ponderado nos vertices e 1 para grafo ponderado nos vertices.
 * @return retorna o grafo criado.
 */
Grafo* leituraDados(char *arqEntrada, int direcionado, int ponderadoAresta, int ponderadoNo){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoOrigem;
    int idNoDestino;
    int ordem;
    ifstream file;
    file.open(arqEntrada);

    //Pegando a ordem do grafo
    file >> ordem;

    //Criando objeto grafo
    Grafo* graf = new Grafo(ordem, direcionado, ponderadoAresta, ponderadoNo);

    //Leitura de arquivo
    if(!graf->ehPonderadoAresta() && !graf->ehPonderadoVertice())
        while(file >> idNoOrigem >> idNoDestino)
            graf->addAresta(idNoOrigem, idNoDestino, 0);

    else if(graf->ehPonderadoAresta() && !graf->ehPonderadoVertice() ){
        float pesoAresta;
        while(file >> idNoOrigem >> idNoDestino >> pesoAresta)
            graf->addAresta(idNoOrigem, idNoDestino, pesoAresta);
    }

    else if(graf->ehPonderadoVertice() && !graf->ehPonderadoAresta()){
        float pesoNoOrigem, pesoNoDestino;
        while(file >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino) {
            graf->addAresta(idNoOrigem, idNoDestino, 0);
            graf->buscaNo(idNoOrigem)->setPeso(pesoNoOrigem);
            graf->buscaNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }

    else if(graf->ehPonderadoVertice() && graf->ehPonderadoAresta()){
        float pesoNoOrigem, pesoNoDestino, pesoAresta;
        while(file >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino >> pesoAresta) {
            graf->addAresta(idNoOrigem, idNoDestino, pesoAresta);
            graf->buscaNo(idNoOrigem)->setPeso(pesoNoOrigem);
            graf->buscaNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }

    file.close();
    return graf;
}

int main(int argc, char* argv[]) {
    if(argc != 5) {
        cout << "Argumentos insuficientes" << endl;
        return 1;
    }
    Grafo* x;
    x = leituraDados(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));


    // DEBUGAR
    /*
    x = leituraDados("Entrada.txt", 0, 1, 1);
     */

    x->imprimirArestas();

    delete x;
}