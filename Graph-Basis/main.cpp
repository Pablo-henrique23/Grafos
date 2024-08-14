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
        cout << "[1] Fecho transitivo direto de um vertice" << endl; // ok
        cout << "[2] Fecho transitivo indireto de um vertice" << endl;  
        cout << "[3] Caminho minimo entre dois vertices - Dijkstra" << endl; // ok
        cout << "[4] Caminho minimo entre dois vertices - Floyd" << endl;
        cout << "[5] Arvore Geradora Mínima de subgrafo vertice-induzido - Prim" << endl; // feito (conferir erros)
        cout << "[6] Arvore Geradora Mínima de subgrafo vertice-induzido - Kruskal" << endl; // feito (conferir erros)
        cout << "[7] Arvore dada pela ordem do caminhamento em profundidade a partir de um vertice" << endl; // implementar arvore -> recursividade
        cout << "[8] Raio, centro, diametro e periferia do grafo" << endl; 
        cout << "[9] Conjunto de vertices de articulacao" << endl;
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


int main(int argc, char* argv[]){
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

    string nomeArquivoSaida = argv[2];
    ofstream arquivo_saida(nomeArquivoSaida, ios::app);

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
        cout << "\n";
        switch (selecao){
            case 0:
            {
                exit = true;
                break;
            }
            case 1: // ATENÇÃO! Os {} nos cases foram adicionados pra evitar erro, mantenha-os por favor
            {
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
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                size_t origem;
                size_t destino;
                cout<<"Digite a origem:";
                cin>>origem;
                cout<<"Digite o destino:";
                cin>>destino;
                size_t resposta;
                resposta= grafo->dijkstra(origem,destino);
                if(resposta==0){
                    cout<<"Um dos vertices digitados nao existe.";
                } else if (resposta==999999999){
                    cout<<"Nao foi encontrado caminho";
                } else if(resposta>0){
                    cout<<"dijkstra:"<<resposta;
                }
            break;
            }
            case 4:
            {
                break;
            }
            case 5:
            { // prim
                if(!grafo->getWeighted_edges()){
                    cout << "Grafo não ponderado. Saindo. \n";
                    break;
                }
                vector<size_t> vertices; // vai armazenar os IDs dos vertices pra fazer o subgrafo vertice induzido
                size_t v; // vai ser usado pra ler o ID do nó
                cout << "Digite o indice de cada vértice para gerar o grafo vértice-induzido (0 para parar): ";
       
                while (true){ // enquanto 0 nao for digitado, continua lendo 
                    cin >> v; // le o id do nó
		        
                    if (v == 0){ // fazer as validações, vai ficar quase igual ao 6
                        if (vertices.empty()){
                            cout << "Conjunto de vértices vazio. Saindo.\n";
                            break;
                        }
                        vector<Edge*> arestas = grafo->gerarVerticeInduzido(vertices);
                        if (arestas.empty()){
                            cout << "Não foi possível gerar subgrafo vertice induzido. Saindo.\n";
                            break;
                        }
                        
                        grafo->agmPrim(arestas, (size_t)vertices.size());    
                        break;
                        
                    } else {
                        if(grafo->ta_no_vetor(vertices,v)){
                            cout << "Vértice repetido detectado, ignorando.\n" ;
                            continue;
                        }
                        // se nao estiver no grafo e nem for 0, entao é realmente inválido (0 nunca vai ser encontrado, por isso a dupla condição)
                        if (!grafo->taNoGrafo(v)){
                            cout << "Nó inválido detectado, ignorando.\n";
                            continue;
                        }
                        vertices.push_back(v);		
                    }
                }
                break;
            }
            // uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal;
            case 6:
            {
                if(!grafo->getWeighted_edges()){
                    cout << "Grafo não ponderado. Saindo. \n";
                    break;
                }
                vector<size_t> vertices; // vai armazenar os IDs dos vertices pra fazer o subgrafo vertice induzido
                size_t v; // vai ser usado pra ler o ID do nó
                cout << "Digite o indice de cada vértice para gerar o grafo vértice-induzido (0 para parar): ";
                while (true){ // enquanto 0 nao for digitado, continua lendo 
                    cin >> v; // le o id do nó

                    if (v == 0){
                        // terminou de digitar os vertices
                        if(vertices.empty()){
                            cout << "Nenhum vértice inserido, saindo.\n";
                            break;
                        }
                        // validação
                        vector<Edge*> arestas = grafo->gerarVerticeInduzido(vertices);
                        if (arestas.empty()){
                            cout << "Não foi possível gerar subgrafo vertice induzido. Saindo.\n";
                            break;
                        }
                      
                        grafo->agmKruskal(arestas);
                    	break;    
                    } else { // nao inseriu 0
                        if (grafo->ta_no_vetor(vertices, v)){ // autoexplicativo
                            cout << "Vertice repetido detectado, ignorando.\n";
                            continue; // pula a iteração
                        }

                        if (!grafo->taNoGrafo(v)){ // se nao estiver no grafo e nem for 0, entao é realmente inválido (0 nunca vai ser encontrado, por isso a dupla condição)
                            cout << "Nó inválido detectado, ignorando.\n";
                            continue;
                        }
                        vertices.push_back(v); // insere V no vetor que vai fazer o subgrafo vertice-induzido
                    }
                }
                break;
            }
            case 7: // caminhamento em profundidade a partir do vertice V
            {
                size_t v = 0;
                while(true){
                    cout << "Digite o ID do vértice: ";
                    cin >> v;
                    cout << endl;
                    if (!grafo->taNoGrafo(v)){
                        cout << "Vertice inválido.\n";
                    } else {
                        break;
                    }
                }
                vector<size_t> resultado = grafo->arvore_caminho_profundidade(v);
                size_t ultimo = resultado.back();
                for (size_t t : resultado){
                    if(t != ultimo){
                        cout << t << " -> ";
                    } else {
                        cout << t;
                    }
                }
                char salvar = 'w';
                while (salvar != 's' || salvar != 'n'){
                    cout << "\nSalvar no arquivo de saida (s/n)? ";
                    cin >> salvar;
                    if(salvar == 's'){
                        cout << "\nResultado salvo\n";
                        // salvar resultado no arquivo
                        arquivo_saida << "\n====== Caminhamento em Profundidade a partir do nó " << v << " ======\n";
                        for (size_t t : resultado){
                            if(t != ultimo){
                                arquivo_saida << t << " -> ";
                            } else {
                                arquivo_saida << t << "\n" ;
                            }
                        }
                        break;
                    } else if (salvar == 'n'){
                        cout << "\nOk.";
                        break;
                    }
                }
                break;
            }
            case 8:
            {
                break;
            }
            case 9:
            {
                break;
            }
            case 99:
            {
                grafo->lista_adjacencia(arquivo_saida);
                cout << "Salvando lista no arquivo de saída fornecido\n";
                break;
            }
            case 100:
            {
                grafo->printa_matriz_adj();
                break;
            }
        }
    }
    arquivo_entrada.close();
    arquivo_saida.close();
    return 0;
}

