#include "include/Graph.hpp"
#include <iostream>
#include <string>

using namespace std;
int main(int argc, char* argv[])
{
    if (argc != 6){ // Argc == 4 significa que a linha de comando dada foi ./<executavel> <arquivo-entrada> <arquivo-saida> <direcionado (0-1)> <ponderado (0-1)> <peso-nos-vertices (0-1)>
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
    
    return 0;
}
