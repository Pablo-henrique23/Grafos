#include "include/Graph.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int menu() {
    int selecao;
    bool again;
    do{
        again = false;
    cout << endl;
    cout << "   ------  MENU ------" << endl;
    cout << "[1] Fecho transitivo direto de um vertice" << endl; // conjunto de vertices alcançaveis a partir de X
    cout << "[2] Fecho transitivo indireto de um vertice" << endl;
    cout << "[3] Caminho mínimo entre dois vértices - Dijkstra" << endl;
    cout << "[4] Caminho mínimo entre dois vértices - Floyd" << endl;
    cout << "[5] Árvore Geradora Mínima de subgrafo vértice-induzido - Prim" << endl;
    cout << "[6] Árvore Geradora Mínima de subgrafo vértice-induzido - Kruskal" << endl;
    cout << "[7] Árvore dada pela ordem do caminhamento em profundidade a partir de um vértice" << endl;
    cout << "[8] Raio, centro, diâmetro e periferia do grafo" << endl;
    cout << "[9] Conjunto de vértices de articulação" << endl;
    cout << "[0] Sair" << endl;
    cout << "Escolha: ";
    cin >> selecao;
    if(!cin){
        again = true;
        cin.clear();
        cin.ignore();
    }
}while(again);
    return selecao;
}


int main(int argc, char* argv[])
{
    if (argc != 6){ // Argc == 6 significa que a linha de comando dada foi ./<executavel> <arquivo-entrada> <arquivo-saida> <direcionado (0-1)> <ponderado (0-1)> <peso-nos-vertices (0-1)>
        cout << "Argumentos insuficientes. O comando deve ser './<executavel> <arquivo-entrada> <arquivo-saida> <direcionado (0-1)> <ponderado (0-1)> <peso-nos-vertices (0-1)>'.\n";
        return 0;
    }
    // Lê o arquivo.
    string nomeArquivoEntrada = argv[1];
    ifstream arquivo_entrada(nomeArquivoEntrada);
    // Confere se o arquivo existe
    if (!arquivo_entrada){ 
        cout << "Arquivo não encontrado.\n" ;
        return 0;
    }
    // pega as outras informações e transforma em booleanos

    bool direcionado = false;
    string dir = argv[3];
    if (dir == "1"){
        direcionado = true;
    }

    bool ponderado = false;
    string pond = argv[4];
    if (pond == "1"){
        ponderado = true;
    }

    bool peso_vertices = false;
    string pv = argv[5];
    if (pv == "1"){
        peso_vertices = true;
    }

    Graph *grafo = new Graph(arquivo_entrada, direcionado, ponderado, peso_vertices);
    bool exit=false;
    while(!exit){
        int selecao = menu();
        switch (selecao){
            case 0:
                exit = true;
                break;
            case 1:
                if (grafo->getDirected() == false){
                    cout << "Operação inválida, grafo não direcionado.\n";
                } else {
                    cout<<"\nDigite o id do No desejado: ";
                    size_t id;
                    cin>>id;
                    if(cin){
                        grafo->fecho_tran_direto(id);
                    }else{
                        cout<<"\nDigite um numero: ";
                    }
                    //  grafo->print_graph();
                }
                break;
            case 2:
                break;

            // uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal;
            case 6:
                if(!grafo->getWeighted_edges()){
                    cout << "Grafo não ponderado. Saindo. \n";
                    return 0;
                }
                vector<size_t> vertices; // vai armazenar os IDs dos vertices pra fazer o subgrafo vertice induzido
                size_t v; // vai ser usado pra ler o ID do nó
                cout << "Digite o indice de cada vértice para gerar o grafo vértice-induzido (0 para parar): ";
                while (true){ // enquanto 0 nao for digitado, continua lendo 
                    cin >> v; // le o id do nó

                    if (v == 0){
                        // terminou de digitar os vertices
                        vector<Edge*> arestas = grafo->gerarVerticeInduzido(vertices);
                        if (arestas.size() == 0){
                            cout << "As arestas que ligam os vértices fornecidos não foram encontradas. Saindo.\n";
                            return 0;
                        }
                        
                        grafo->agmKruskal(arestas);
                        
                        return 0;
                    } else {
                        if (grafo->ta_no_vetor(vertices, v)){ // autoexplicativo
                            cout << "Vertice repetido detectado, ignorando.\n";
                            continue; // pula a iteração
                        }

                        if (!(grafo->taNoGrafo(v))){ // se nao estiver no grafo e nem for 0, entao é realmente inválido (0 nunca vai ser encontrado, por isso a dupla condição)
                            cout << "\n Nó inválido detectado, ignorando.\n";
                            continue;
                        }
                        vertices.push_back(v); // insere V no vetor que vai fazer o subgrafo vertice-induzido
                    }

                }
        }}

    return 0;
}

