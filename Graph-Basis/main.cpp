#include "include/Graph.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int menu() {
    int selecao;
    cout << endl;
    cout << "   ------  MENU ------" << endl;
    cout << "[1] Fecho transitivo direto de um vertice" << endl; // conjunto de vertices alcançaveis a partir de X
    cout << "[2] Fecho transitivo indireto de um vertice" << endl;
    cout << "[3] Coeficiente de agrupamento local de um vertice" << endl;
    cout << "[4] Coeficiente de agrupamento medio do grafo" << endl;
    cout << "[5] Caminho Minimo entre dois vertices - Dijkstra " << endl;
    cout << "[6] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[7] Arvore Geradora Minima - Prim" << endl;
    cout << "[8] Arvore Geradora Minima - Kruskal " << endl;
    cout << "[9] Caminhamento em profundidade " << endl;
    cout << "[0] Sair" << endl;
    cout << "Escolha: ";
    cin >> selecao;

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
    
    int selecao = menu();
    switch (selecao){
        // case 1: // fecho transitivo direto de um vertice
        //     size_t n;
        //     cout << "Digite o ID do vértice: ";
        //     cin >> n;
        //     size_t* ftd = grafo->fecho_tran_direto(n);
        //     for (size_t i = 0; i < sizeof(ftd); i++){
        //         cout << ftd[i] << " ";
        //     }
        //     cout << endl;
        //     break;
        case 1:
            grafo->fecho_tran_direto(1);
            break;
    }

    return 0;
}

