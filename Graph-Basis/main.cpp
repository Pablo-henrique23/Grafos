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
        cout << "[1] Fecho transitivo direto de um vertice" << endl; // ok 
        cout << "[2] Fecho transitivo indireto de um vertice" << endl;  // ok
        cout << "[3] Caminho minimo entre dois vertices - Dijkstra" << endl; // ok
        cout << "[4] Caminho minimo entre dois vertices - Floyd" << endl; // ok
        cout << "[5] Arvore Geradora Mínima de subgrafo vertice-induzido - Prim" << endl; // ok
        cout << "[6] Arvore Geradora Mínima de subgrafo vertice-induzido - Kruskal" << endl; // ok 
        cout << "[7] Arvore dada pela ordem do caminhamento em profundidade a partir de um vertice" << endl; // ok
        cout << "[8] Raio, centro, diametro e periferia do grafo" << endl; // ok
        cout << "[9] Conjunto de vertices de articulacao" << endl; // conferir 
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
    cout << "Criando instancia do arquivo\n";
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
                    vector<size_t> retorno;
                    vector<Edge*> arestas;
                    if(cin){
                        retorno = grafo->fecho_tran_direto(id, arestas);
                    }else{
                        cout<<"\nDigite um numero: ";
                    }
                    char salvar = 'w';
                    while (salvar != 's' && salvar != 'n'){
                        cout << "\nSalvar resposta no arquivo de saída especificado? (s/n) ";
                        cin >> salvar;
                    }
                    if (salvar == 's'){
                        cout << "Saída salva.\n";
                        arquivo_saida << "\n====== Fecho Transitivo Direto do nó " << id << " ======\n";
                        if(retorno.size() > 0){
                            arquivo_saida << "O fecho transitivo direto do vértice " << id << " é constituido pelos vértices: ";
                            for (auto i : retorno){
                                arquivo_saida << i << " ";
                            }
                            arquivo_saida << endl;
                        } else {
                            arquivo_saida << "O fecho transitivo direto do nó " << id << " é vazio. \n";
                        }
                        grafo->exportar(arestas, arquivo_saida);
                    } else if (salvar == 'n'){
                        cout <<"\nOk";
                    }
                }
                break;
            }
            case 2:
            {
                if (grafo->getDirected() == false){
                    cout << "Operação inválida, grafo não direcionado.\n";
                } else {
                    cout<<"\nDigite o id do No desejado: ";
                    size_t id;
                    cin>>id;
                    vector<size_t> retorno;
                    vector<Edge*> arestas;
                    if(cin){
                        retorno = grafo->fecho_tran_indireto(id, arestas);
                    }else{
                        cout<<"\nDigite um numero: ";
                    }
                    char salvar = 'w';
                    while (salvar != 's' && salvar != 'n'){
                        cout << "\nSalvar resposta no arquivo de saída especificado? (s/n) ";
                        cin >> salvar;
                    }
                    if (salvar == 's'){
                        cout << "Saída salva.\n";
                        arquivo_saida << "\n====== Fecho Transitivo Inireto do nó " << id << " ======\n";
                        if(retorno.size() > 0){
                            arquivo_saida << "O fecho transitivo indireto do vértice " << id << " é constituido pelos vértices: ";
                            for (auto i : retorno){
                                arquivo_saida << i << " ";
                            }
                            arquivo_saida << endl;
                        } else {
                            arquivo_saida << "O fecho transitivo indireto do nó " << id << " é vazio. \n";
                        }
                        grafo->exportar(arestas, arquivo_saida);
                    } else if (salvar == 'n'){
                        cout <<"\nOk";
                    }
                }
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
                } else if (salvar == 'n'){
                    cout <<"\nOk";
                    break;
                }
            break;
            }
            case 4: // floyd 
            {   
                size_t inicio, destino;
                cout << "Digite o vértice inicial: ";
                cin >> inicio;
                cout << "Digite o vértice de destino: ";
                cin >> destino;
                if(!grafo->taNoGrafo(inicio) || !grafo->taNoGrafo(destino)){
                    cout << "\nUm dos vértices não foi encontrado. Saindo.\n";
                    break;
                }
                cout << endl;
                size_t resultado = grafo->floyd(inicio, destino);
                cout << "Custo para ir de " << inicio << " até " << destino << ": " << resultado;
                cout << endl;
                char salvar = 'w';
                while(salvar != 's' && salvar != 'n'){
                    cout << "\nSalvar resultado? (s/n) ";
                    cin >> salvar;
                }
                if(salvar == 's'){
                    cout << "Resultado salvo.\n";
                    arquivo_saida << "\n====== Caminho Mínimo (Floyd) de " << inicio << " até " << destino << " ======\n";
                    arquivo_saida << "Custo = " << resultado << endl;
                } else if (salvar == 'n'){
                    cout << "Ok\n";
                }
                break;
            }
            case 5:
            { // prim
                if(!grafo->getWeighted_edges()){
                    cout << "Grafo não ponderado. Saindo. \n";
                    break;
                }
                if(grafo->getDirected()){
                    cout << "Prim não se aplica a grafos direcionados. Saindo\n";
                    break;
                }
                vector<size_t> vertices; // vai armazenar os IDs dos vertices pra fazer o subgrafo vertice induzido
                vector<Edge*> arestas;
                vector<Edge*> resultado;
                size_t v; // vai ser usado pra ler o ID do nó
                bool running = true;
                cout << "Digite o indice de cada vértice para gerar o grafo vértice-induzido (0 para parar e 65536 para todos): ";
       
                while (running){ // enquanto 0 nao for digitado, continua lendo 
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
                        
                        resultado = grafo->agmPrim(arestas, vertices.size());    
                        running = false;
                        
                    } else {
                        if (v == 65536){
                            vertices.clear();
                            for(Node* noI = grafo->getFirst(); noI!=nullptr; noI = noI->_next_node){
                                vertices.push_back(noI->_id);
                            }
                            arestas = grafo->gerarVerticeInduzido(vertices);
                            resultado = grafo->agmPrim(arestas, grafo->getNumberOfNodes());
                            running = false;
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
                        }
                        vertices.push_back(v);		
                    }
                }
                char salvar = 'w';
                while (salvar != 's' && salvar != 'n'){
                    cout << "\nDeseja salvar o resultado no arquivo? (s/n) ";
                    cin >> salvar;
                    cout << salvar << endl;
                }
                if(salvar == 's'){
                    // cout << "Salvando.\n";
                    // size_t peso_total = 0;
                    // arquivo_saida << "\n====== Árvore Geradora Mínima (Prim) ======\n";
                    grafo->exportar(resultado, arquivo_saida);
                    // arquivo_saida << endl;
                    // for(Edge* i : resultado){
                    //     arquivo_saida << "(" << i->_source_id << ", " << i->_target_id << ") ";
                    //     peso_total += i->_weight;
                    // }
                    // arquivo_saida << "\nCusto total: " << peso_total << endl;
                } else if(salvar == 'n') {
                    cout << "Ok\n";
                    break;
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
                if(grafo->getDirected()){
                    cout << "Kruskal não se aplica a grafos direcionados. Saindo\n";
                    break;
                }
                vector<size_t> vertices; // vai armazenar os IDs dos vertices pra fazer o subgrafo vertice induzido
                vector<Edge*> arestas;
                vector<Edge*> resultado;
                
                size_t v; // vai ser usado pra ler o ID do nó
                bool running = true;
                cout << "Digite o indice de cada vértice para gerar o grafo vértice-induzido (0 para parar e 65536 para todos): ";
               
                while (running){ // enquanto 0 nao for digitado, continua lendo 
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
                        resultado = grafo->agmKruskal(arestas, vertices.size());
                    	running = false;    
                    } else { // nao inseriu 0
                        if (v == 65536){
                            vertices.clear();
                            for(Node* noI = grafo->getFirst(); noI!=nullptr; noI = noI->_next_node){
                                vertices.push_back(noI->_id);
                            }
                            arestas = grafo->gerarVerticeInduzido(vertices);
                            resultado = grafo->agmKruskal(arestas, vertices.size());
                            running = false;
                        } else {
                            if (grafo->ta_no_vetor(vertices, v)){ // repetido
                                cout << "Vertice repetido detectado, ignorando.\n";
                                continue; // pula a iteração
                            }

                            if (!grafo->taNoGrafo(v)){ // se nao estiver no grafo e nem for 0, entao é realmente inválido (0 nunca vai ser encontrado, por isso a dupla condição)
                                cout << "Nó inválido detectado, ignorando.\n";
                                continue;
                            }
                        }
                        vertices.push_back(v); // insere V no vetor que vai fazer o subgrafo vertice-induzido
                    }
                }
                char salvar = 'w';
                while (salvar != 's' && salvar != 'n'){
                    cout << "\nDeseja salvar o resultado no arquivo? (s/n) ";
                    cin >> salvar;
                }
                if(salvar == 's'){
                    cout << "Salvando.\n";
                    size_t peso_total = 0;
                    arquivo_saida << "\n====== Árvore Geradora Mínima (Kruskal) ======\n";
                    for(Edge* i : resultado){
                        arquivo_saida << "(" << i->_source_id << ", " << i->_target_id << ") ";
                        peso_total += i->_weight;
                    }
                    arquivo_saida << "\nCusto total: " << peso_total << endl;
                } else if(salvar == 'n') {
                    cout << "Ok\n";
                    break;
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
                vector<Edge*> arestas;
                vector<size_t> resultado = grafo->arvore_caminho_profundidade(v, arestas);
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
                grafo->determinar_excentricidades();
                grafo->determinar_diametro();
                grafo->determinar_raio();
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
                grafo->exportar(grafo->allEdges(), arquivo_saida);
                cout << "Salvando lista no arquivo de saída fornecido\n";
                break;
            }
        }
    }
    arquivo_entrada.close();
    arquivo_saida.close();
    grafo->~Graph();
    
    return 0;
}

