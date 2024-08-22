#define infinito 99999//65535
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
        cout << "[1] Fecho transitivo direto de um vertice" << endl; // ok -> falta salvar
        cout << "[2] Fecho transitivo indireto de um vertice" << endl;  
        cout << "[3] Caminho minimo entre dois vertices - Dijkstra" << endl; // completo
        cout << "[4] Caminho minimo entre dois vertices - Floyd" << endl;
        cout << "[5] Arvore Geradora Mínima de subgrafo vertice-induzido - Prim" << endl; // feito (conferir erros) -> falta salvar
        cout << "[6] Arvore Geradora Mínima de subgrafo vertice-induzido - Kruskal" << endl; // feito (conferir erros) -> falta salvar
        cout << "[7] Arvore dada pela ordem do caminhamento em profundidade a partir de um vertice" << endl; // completo
        cout << "[8] Raio, centro, diametro e periferia do grafo" << endl; // completo
        cout << "[9] Conjunto de vertices de articulacao" << endl;
        cout << "[0] Sair" << endl;
        cout << "Escolha: ";
        cin >> selecao;
    }while(again);
        if(!cin){
            again = true;
            cin.clear();
            cin.ignore();
        }
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
    // abrir assim faz com que o conteudo do arquivo nao seja sobrescrito
    

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
                cout<<"Digite o nó de origem: ";
                cin>>origem;
                cout<<"Digite o nó destino: ";
                cin>>destino;
                pair<size_t,string> resposta;
                resposta= grafo->dijkstra(origem,destino);
                if(resposta.first==0){
                    cout<<"\nUm dos vertices digitados nao existe.";
                } else if (resposta.first==infinito){
                    cout<<"\nNao foi encontrado caminho";
                } else if(resposta.first>0){
                    cout<<"\nDijkstra: "<<resposta.second<<endl;
                    cout<<"Custo: "<<resposta.first<<endl;
                }
                char salvar = 'w';
                while (salvar != 's' && salvar != 'n'){
                    cout << "\nSalvar resposta no arquivo de saída especificado? (s/n) ";
                    cin >> salvar;
                }
                if (salvar == 's'){
                    cout << "Saída salva.\n";
                    arquivo_saida << "\n====== Caminho Mínimo (Algoritmo de Dijkstra) do nó " << origem << " até o nó " << destino << " ======\n";
                    arquivo_saida << "Dijkstra: "<<resposta.second<<endl;
                    arquivo_saida << "Custo: "<<resposta.first<<endl;
                } else {
                    cout <<"\nOk";
                    break;
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
                vector<Edge*> arestas;
                size_t v; // vai ser usado pra ler o ID do nó
                cout << "Digite o indice de cada vértice para gerar o grafo vértice-induzido (0 para parar e 65536 para todos): ";
       
                while (true){ // enquanto 0 nao for digitado, continua lendo 
                    cin >> v; // le o id do nó
		        
                    if (v == 0){ // fazer as validações, vai ficar quase igual ao 6
                        if (vertices.empty()){
                            cout << "Conjunto de vértices vazio. Saindo.\n";
                            break;
                        }
                        if(vertices.size() == 1){
                            cout << "Apenas um vértice detectado.\nCusto total = 0" << endl;
                            break;
                        }
                        arestas = grafo->gerarVerticeInduzido(vertices);
                        if (arestas.empty()){
                            cout << "Não foi possível gerar subgrafo vertice induzido. Saindo.\n";
                            break;
                        }
                        
                        grafo->agmPrim(arestas, vertices.size());    
                        break;
                        
                    } else {
                        if (v == 65536){
                            vertices.clear();
                            for(Node* noI = grafo->getFirst(); noI!=nullptr; noI = noI->_next_node){
                                vertices.push_back(noI->_id);
                            }
                            arestas = grafo->gerarVerticeInduzido(vertices);
                            grafo->agmPrim(arestas, vertices.size());
                            break;
                        }
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
                arestas.clear();
                vertices.clear();
                break;
            }
            // uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal;
            case 6: // EVENTUALMENTE da seg fault, mas não consegui achar o motivo
            {
                if(!grafo->getWeighted_edges()){
                    cout << "Grafo não ponderado. Saindo. \n";
                    break;
                }
                vector<size_t> vertices; // vai armazenar os IDs dos vertices pra fazer o subgrafo vertice induzido
                vector<Edge*> arestas;
                size_t v; // vai ser usado pra ler o ID do nó
                cout << "Digite o indice de cada vértice para gerar o grafo vértice-induzido (0 para parar e 65536 para todos): ";
               
                while (true){ // enquanto 0 nao for digitado, continua lendo 
                    cin >> v; // le o id do nó

                    if (v == 0){
                        // terminou de digitar os vertices
                        if(vertices.empty()){
                            cout << "Nenhum vértice inserido, saindo.\n";
                            break;
                        }
                        if(vertices.size() == 1){
                            cout << "Apenas um vértice detectado.\nCusto total = 0" << endl;
                            break;
                        }
                        // validação
                        arestas = grafo->gerarVerticeInduzido(vertices);
                        if (arestas.empty()){
                            cout << "Não foi possível gerar subgrafo vertice induzido. Saindo.\n";
                            break;
                        }
                        grafo->agmKruskal(arestas, vertices.size());
                    	break;    
                    } else { // nao inseriu 0
                        if (v == 65536){
                            vertices.clear();
                            for(Node* noI = grafo->getFirst(); noI!=nullptr; noI = noI->_next_node){
                                vertices.push_back(noI->_id);
                            }
                            arestas = grafo->gerarVerticeInduzido(vertices);
                            cout << "CHAMADA\n";
                            grafo->agmKruskal(arestas, vertices.size());
                            break;
                        }
                        if (grafo->ta_no_vetor(vertices, v)){ // repetido
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
                arestas.clear();
                vertices.clear();
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
                size_t raio = grafo->get_raio();
                size_t diametro = grafo->get_diametro();
                grafo->determinar_centro();
                vector<size_t> centro = grafo->getCentro();
                grafo->determinar_periferia();
                vector<size_t> periferia = grafo->getPeriferia();
                
                cout << "Raio = " << raio << "\nDiâmetro = " << diametro << endl;
                cout << "ID dos nós periféricos: ";
                for(size_t i : periferia){
                    if(i != periferia.back()){
                        cout << i << ", ";
                    } else {
                        cout << i;
                    }
                }

                cout << "\nID dos nós centrais: ";
                for(size_t i : centro){
                    if(i != centro.back()){
                        cout << i << ", ";
                    } else {
                        cout << i;
                    }
                }
                char salvar = 'w';
                while (salvar != 's' && salvar != 'n'){
                    cout << "\n\nSalvar resposta no arquivo de saída especificado? (s/n) ";
                    cin >> salvar;
                }
                if (salvar == 's'){
                    cout << "Saída salva.\n";
                    arquivo_saida << "\n====== Raio, centro, diâmetro e periferia do grafo" << " ======\n";
                    arquivo_saida << "Raio = " << raio << "\nDiâmetro = " << diametro << endl;
                    arquivo_saida << "ID dos nós periféricos: ";
                    for(size_t i : periferia){
                        if(i != periferia.back()){
                            arquivo_saida << i << ", ";
                        } else {
                            arquivo_saida << i;
                        }
                    }

                    arquivo_saida << "\nID dos nós centrais: ";
                    for(size_t i : centro){
                        if(i != centro.back()){
                            arquivo_saida << i << ", ";
                        } else {
                            arquivo_saida << i << endl;
                        }
                    }

                } else {
                    cout <<"\nOk";
                    break;
                }
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

