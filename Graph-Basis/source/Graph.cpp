#define infinito 99999//65535
#include "../include/Graph.hpp"
#include "../include/Node.hpp"
#include "../include/Edge.hpp"
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
Graph::Graph(ifstream& instance, bool direcionado, bool weighted_edges, bool weighted_nodes)
{
    // Pega a primeira linha e joga pra tamanhoInstância (a 1° linha é o tamanho da instancia do grafo, check README.txt)
    string temp; // temporario pra ser usado na função getline()
    getline(instance, temp);
    // pega o tamanho da instancia em inteiro
    this->_number_of_nodes = stoi(temp); // stoi = string to int
    
    // cria e inicializa matriz de adjacencia 
    this->matriz_adj = new size_t*[this->_number_of_nodes+1];
    for (size_t i = 1; i < this->_number_of_nodes+1; i++){
        this->matriz_adj[i] = new size_t[this->_number_of_nodes+1];
    }
    for (size_t i = 1; i < this->_number_of_nodes+1; i++){
        for(size_t j = 1; j < this->_number_of_nodes+1; j++){
            if(i != j){
                this->matriz_adj[i][j] = infinito;
            } else {
                this->matriz_adj[i][j] = 0;
            }
            
        }
    }
    // -----------

    // adiciona outros parametros
    adj.resize(this->_number_of_nodes);
    this->_directed = direcionado;
    this->_weighted_edges = weighted_edges;
    this->_weighted_nodes = weighted_nodes;

    // ANALISE DE ARQUIVO DE ENTRADA
    _first=nullptr;
    string linha;
    Node no;
    Node proximoNo;
    Edge aresta;
    this->_number_of_edges = 0;
    this->_number_of_nodes = 0;

    while (getline(instance, linha)){    
        // Deus nos ajude com stringstream
        stringstream ss(linha);
        ss >> no._id;
        aresta._source_id = no._id;
        ss >> proximoNo._id;
        aresta._target_id = proximoNo._id;
        ss >> aresta._weight;
        add_node(no._id);
        add_node(proximoNo._id);
        add_edge(no._id, proximoNo._id, aresta._weight);

        this->matriz_adj[no._id][proximoNo._id] = aresta._weight;
        if (direcionado == false){ // Se nao for direcionado, entao é uma via de mão dupla e precisa ter as duas arestas
            cout << aresta._weight << endl;
            this->matriz_adj[proximoNo._id][no._id] = aresta._weight;
            add_edge(proximoNo._id, no._id, aresta._weight); // DANDO SEG FAULT

        }
    }
    // fazer matriz de incidencia aqui para facilitar possiveis contas
    // print_graph();
}

Graph::Graph()
{
}

Graph::~Graph()
{
}
void Graph::remove_node(size_t node_position)
{
    Node* nodeToRemove = search_for_node(node_position);
    if (nodeToRemove == nullptr) {
        cout << "Nó não encontrado no grafo!" << endl;
        return;
    }

    // Remover todas as arestas conectadas ao nó
    while (nodeToRemove->_first_edge != nullptr) {
        remove_edge(node_position, nodeToRemove->_first_edge->_target_id);
    }

    // Remover o nó da lista de nós
    if (nodeToRemove == this->_first) {
        this->_first = nodeToRemove->_next_node;
        if (this->_first != nullptr) {
            this->_first->_previous_node = nullptr;
        }
    } else if (nodeToRemove == this->_last) {
        this->_last = nodeToRemove->_previous_node;
        if (this->_last != nullptr) {
            this->_last->_next_node = nullptr;
        }
    } else {
        nodeToRemove->_previous_node->_next_node = nodeToRemove->_next_node;
        if (nodeToRemove->_next_node != nullptr) {
            nodeToRemove->_next_node->_previous_node = nodeToRemove->_previous_node;
        }
    }

    delete nodeToRemove;
    this->_number_of_nodes--;
    cout << "Nó removido com sucesso!" << endl;
}
void Graph::remove_edge(size_t node_position_1, size_t node_position_2)
{
    Node* No1 = search_for_node(node_position_1);
    if (No1 == nullptr) {
        cout << "Nó de origem não encontrado no grafo!" << endl;
        return;
    }

    Node* No2 = search_for_node(node_position_2);
    if (No2 == nullptr) {
        cout << "Nó de destino não encontrado no grafo!" << endl;
        return;
    }

    // Remover a aresta do nó de origem
    Edge* prevEdge = nullptr;
    Edge* edgeTraversal = No1->_first_edge;

    while (edgeTraversal != nullptr) {
        if (edgeTraversal->_target_id == node_position_2) {
            if (prevEdge == nullptr) {
                No1->_first_edge = edgeTraversal->_next_edge;
            } else {
                prevEdge->_next_edge = edgeTraversal->_next_edge;
            }
            delete edgeTraversal;
            No1->_number_of_edges--;
            this->_number_of_edges--;
            cout << "Aresta removida do nó de origem com sucesso!" << endl;
            break;
        }
        prevEdge = edgeTraversal;
        edgeTraversal = edgeTraversal->_next_edge;
    }

    // Remover a aresta do nó de destino (apenas para grafos não direcionados)
    if (!this->_directed) {
        prevEdge = nullptr;
        edgeTraversal = No2->_first_edge;

        while (edgeTraversal != nullptr) {
            if (edgeTraversal->_target_id == node_position_1) {
                if (prevEdge == nullptr) {
                    No2->_first_edge = edgeTraversal->_next_edge;
                } else {
                    prevEdge->_next_edge = edgeTraversal->_next_edge;
                }
                delete edgeTraversal;
                No2->_number_of_edges--;
                cout << "Aresta removida do nó de destino com sucesso!" << endl;
                break;
            }
            prevEdge = edgeTraversal;
            edgeTraversal = edgeTraversal->_next_edge;
        }
    }
}


void Graph::add_node(size_t node_id, float weight)
{
    if(this->_first==nullptr){
        Node* firstNode = new Node();
        _first = firstNode;
        _first->_id = node_id;
        firstNode->_visitado = false;
        this->_number_of_nodes++;
    }else{
        Node* aux=_first;
        bool jaExiste=false;
        if(aux->_id==node_id){
            jaExiste=true;
        }
        while(aux->_next_node!=nullptr){     
            aux = aux->_next_node;
            if(aux->_id==node_id){
                jaExiste=true;
                break;
            }
        }
        if(jaExiste){
            return;
        }
        aux->_next_node = new Node();
        aux->_next_node->_id = node_id;
        this->_last = aux->_next_node;
        aux->_next_node->_visitado = false;
        this->_number_of_nodes++;
    }
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight) // DANDO SEG FAULT
{  
    Node* No1;
    Node* traversal=this->_first;
    adj[node_id_1].push_back(make_pair(node_id_2, weight));
    // cout<<"Criando Edge"<<endl;
    while(traversal!=nullptr){
        if(node_id_1==traversal->_id){
            No1 = traversal;
            break;
        }else{
            traversal=traversal->_next_node;
        }
    }
    if(No1->_first_edge==nullptr){
        No1->_first_edge = new Edge();

        No1->_first_edge->_source_id = No1->_id; // check me pablo!
        No1->_first_edge->_weight = weight;
        No1->_first_edge->_target_id = node_id_2;
        No1->_number_of_edges++; // check me
        this->_number_of_edges++;
        //    cout<<"Criando primeira aresta do no"<<No1->_id<<endl;
    }else{
        Edge* edgeTraversal=traversal->_first_edge;
        while(edgeTraversal->_next_edge!=nullptr){
            //  cout<<"Contem aresta:"<<edgeTraversal->_target_id<<endl;
            edgeTraversal=edgeTraversal->_next_edge;
        }
        edgeTraversal->_next_edge = new Edge();

        edgeTraversal->_next_edge->_source_id = node_id_1;
        edgeTraversal->_next_edge->_weight = weight;
        edgeTraversal->_next_edge->_target_id = node_id_2;
        this->_number_of_edges++;
        No1->_number_of_edges++; // check me

        //   cout<<"Criando aresta do no"<<No1->_id<<endl;
    }
  //  cout<<"aresta Criado"<<endl;
}

void Graph::print_graph()
{
    cout<<"Imprimindo...";
    cout<<"Primeiro no:"<<this->_first->_id<<endl;
    Node* traversal=this->_first;
    Edge* edgeTraversal = traversal->_first_edge;
    while(traversal!=nullptr){
        cout<<"Contem no:"<<traversal->_id<<endl;
        edgeTraversal = traversal->_first_edge;
        while(edgeTraversal!=nullptr){
            cout<<"     Contem aresta:"<<traversal->_id<<"-"<<edgeTraversal->_target_id<<endl;
           edgeTraversal=edgeTraversal->_next_edge;
        }
        traversal=traversal->_next_node;
    }
    cout<<"Ultimo no:" << this->_last->_id<<endl;
    cout<<"Numero de Vertices:" << this->_number_of_nodes << endl;
    cout<<"Numero de Arestas:" << this->_number_of_edges << endl;
}

size_t Graph::dijkstra(size_t origem, size_t destino){
    if(search_for_node(origem)==nullptr||search_for_node(destino)==nullptr)
    {
        return infinito;
    }  
    size_t distancias[this->_number_of_nodes];
    size_t visitados[this->_number_of_nodes];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    
    for(size_t i = 0; i < this->_number_of_nodes; i++)
		{
			distancias[i] = infinito;
			visitados[i] = false;//mudar para 0 ou 1
		}
    distancias[origem] = 0;
    fila.push(make_pair(distancias[origem], origem));
    while(!fila.empty())
	{
		pair<int, int> p = fila.top(); 
		int vertice = p.second;
		fila.pop(); 

		if(visitados[vertice] == false)
		{
		visitados[vertice] = true;
	        for (size_t i = 0; i < adj[vertice].size(); i++) {
            size_t v = adj[vertice][i].first;
            size_t custo_da_aresta = adj[vertice][i].second;
            if (distancias[v] > (distancias[vertice] + custo_da_aresta)) 
            {
            distancias[v] = distancias[vertice] + custo_da_aresta;
            fila.push(make_pair(distancias[v], v));
            }
            }
		}
	}
		return distancias[destino];
	
}
void Graph::print_graph(std::ofstream& output_file)
{
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    // passar de nó em nó, conferir se tem mais de 1 aresta e passar de aresta em aresta ate achar o alvo
    // retorna 1 pra sim e 0 pra não. apenas pra nao trocar o retorno da função
    // NOTA: **Aparentemente** funciona pra grafos direcionados também
    if (this->_first == nullptr){ // aqui nao tem nem o primeiro nó, então ja para
        return 0;
    }
    Node *no;
    Edge *aresta;
    Node *traversal = this->_first;
    while (traversal != nullptr){
        if (traversal->_id == node_id_1){
            no = traversal;
            aresta = no->_first_edge;
            for (size_t i = 0; i < no->_number_of_edges; i++){
                if (aresta->_target_id == node_id_2){
                    return 1;
                }
                aresta = aresta->_next_edge;
            }
        }
        traversal = traversal->_next_node;
    }
    return 0;
}


vector<size_t> Graph::fecho_tran_direto(size_t node_id){
    
    vector<size_t> noContatos;
    vector<size_t> noProcurados;
    vector<size_t> final;
    if(search_for_node(node_id)==nullptr){
    cout<<"digite um No valido";
    return final;
    }
    noContatos.push_back(node_id);
    size_t no_id_inicial=node_id;
    Node* no;
    Edge* aresta;
    while(!noContatos.empty()){
        bool taNoVetor = ta_no_vetor(noProcurados,node_id);     
        if (taNoVetor){
            noContatos.pop_back();
            continue;
        }           
        no = search_for_node(noContatos.back());
        aresta = no->_first_edge;
        node_id = no->_id;
        if(no_id_inicial!=noContatos.back()){

        final.push_back(noContatos.back());
        }
        noContatos.pop_back();
        for (size_t i = 0; i < no->_number_of_edges; i++)
        {  
            noContatos.push_back(aresta->_target_id);
            aresta=aresta->_next_edge;
        }

        noProcurados.push_back(noContatos.front());
    }
    if(final.size()==0){
        cout<<"No "<< no_id_inicial<<" nao possui contato com ninguem"<<endl;
    }else{

    
    for (size_t i = 0; i < final.size(); i++)
    {
        cout<<"Nos em contato com o No "<<no_id_inicial<<":"<<final[i]<<endl;
    }
    }
    
    // O processo para grafo direcionado e nao direcionado é diferente
    

    return final;
}


// Sempre que usar isso, confira se o retorno foi nullptr! Se nao for e voce tentar usar algum atributo,
// vai dar core dumped
// ex:
// Node* busca = grafo->search_for_node(6);
// if(busca != nullptr){
//     cout << busca->_id << endl;
// }
Node* Graph::search_for_node(size_t node_id){ //busca um nó no grafo, se achar retorna o endereço dele
    Node* no = new Node();
    no = this->_first;
    while(no!=nullptr){     
        if (no->_id == node_id){
            return no;
        }
        no = no->_next_node;   
    }
    return nullptr;
}

bool Graph::ta_no_vetor(vector<size_t>& vetor, size_t node_id){
    for (size_t i = 0; i < vetor.size(); i++){   
        if(vetor[i]==node_id){
            return true;
        }
    }
    return false;
}

bool Graph::node_no_vetor(vector<Node*>& vetor, Node* node){
    for (size_t i = 0; i < vetor.size(); i++){
        if(vetor[i]==node){
            return true;
        }
    }
    return false;
}
bool Graph::aresta_no_vetor(vector<Edge*>& vetor, Edge* aresta){
    for (size_t i = 0; i < vetor.size(); i++){
        if(vetor[i]==aresta){
            return true;
        }
    }
    return false;
}

bool Graph::getDirected(){
    return this->_directed;
}
bool Graph::getWeighted_edges(){
    return this->_weighted_edges;
}
bool Graph::getWeighted_nodes(){
    return this->_weighted_nodes;
}

size_t Graph::getNumberOfNodes(){
    return this->_number_of_nodes;
}

bool Graph::taNoGrafo(size_t no){
    if (this->search_for_node(no) == nullptr){
        return false;
    }
    return true;
}

vector<Edge*> Graph::gerarVerticeInduzido(vector<size_t> vertices){
    // faz um fuzuê entre arrays e retorna as edges que geram um sub Vert induzido
    // com os IDs fornecidos.
    // supoe-se que ja foi feita a validação quanto a repetição dos vertices e quanto a existencia deles no grafo
    vector<Edge*> retorno;
    vector<Node*> nos;
    for (size_t i : vertices){ // gera um vetor de nos
        Node* no = this->search_for_node(i);
        nos.push_back(no);
    }
    for(Node* i : nos){
        Edge* aresta = i->_first_edge;
        while(aresta!=nullptr){
            if (this->ta_no_vetor(vertices, aresta->_target_id)){
                retorno.push_back(aresta);
            }
            aresta = aresta->_next_edge;
        }
    }
    // cout << retorno.size() << endl;
    return retorno;

}

vector<Edge*> Graph::agmPrim(vector<Edge*> arestas, size_t nNos){
    vector<Edge*> retorno;
    vector<size_t> envolvidos;
    sort(arestas.begin(), arestas.end(), [](Edge *aresta1, Edge *aresta2){return aresta1->_weight < aresta2->_weight;});
    int i = 0;
    size_t peso_total = 0;
    while (retorno.size() != nNos - 1){
        for(Edge* aresta : arestas){
            if (i == 0){
                envolvidos.push_back(aresta->_source_id);
                i++;
            }
            if(aresta->_source_id != aresta->_target_id){
                if(ta_no_vetor(envolvidos, aresta->_source_id) && !ta_no_vetor(envolvidos, aresta->_target_id)){
                    envolvidos.push_back(aresta->_target_id);
                    retorno.push_back(aresta);
                    peso_total += aresta->_weight;
                    continue;
                }
                if(!ta_no_vetor(envolvidos, aresta->_source_id) && ta_no_vetor(envolvidos, aresta->_target_id)){
                    envolvidos.push_back(aresta->_source_id);
                    retorno.push_back(aresta);
                    peso_total += aresta->_weight;
                    continue;
                }
            }
	    }
    }
    cout << endl;
    sort(retorno.begin(), retorno.end(), [](Edge *aresta1, Edge *aresta2){return aresta1->_source_id < aresta2->_source_id;});
    cout << "Árvore Geradora Mínima composta pelas arestas\n";
    for(Edge* i : retorno){
        cout << "(" << i->_source_id << ", " << i->_target_id << ") ";
    }
    cout << endl;
    cout << "Custo total: " << peso_total << endl;
    return retorno;
}


vector<Edge*> Graph::agmKruskal(vector<Edge*> arestas){

    // bota em ordem por peso
    sort(arestas.begin(), arestas.end(), [](Edge *aresta1, Edge *aresta2){return aresta1->_weight < aresta2->_weight;}); 
    vector<Edge*> retorno; // arestas que serão retornadas
    vector<size_t> envolvidos; // ids de nós envolvidos
    size_t peso_total = 0;
    // para cada aresta
    for(Edge* aresta : arestas){
        // se a aresta nao ta no retorno e o source dela nao ta nos envolvidos
        if(aresta->_source_id != aresta->_target_id){
            if(!aresta_no_vetor(retorno, aresta) && (!ta_no_vetor(envolvidos, aresta->_source_id))){
                retorno.push_back(aresta); // coloca a aresta no retorno
                envolvidos.push_back(aresta->_source_id); // coloca a source nos envolvidos
                peso_total += aresta->_weight; // atualiza o peso
            }
        }
    }
    // mostra o retorno, pode tirar se quiser (ai tem que colocar pra mostrar na main)
    cout << endl;

    // coloca em ordem
    sort(retorno.begin(), retorno.end(), [](Edge *aresta1, Edge *aresta2){return aresta1->_source_id < aresta2->_source_id;});
    cout << "Árvore Geradora Mínima composta pelas arestas\n";
    for (Edge* i : retorno){
        cout << "(" << i->_source_id << ", " << i->_target_id << ") ";
    }
    cout << "\nCusto total: " << peso_total << endl;
    return retorno;
}

vector<size_t> Graph::arvore_caminho_profundidade(size_t noInicial){
    // inicializa tudo em falso por garantia --> se so o construtor fizer isso, a segunda vez que for usar o [7] vai dar errado
    for(Node* no = this->_first; no!=nullptr; no = no->_next_node){
        no->_visitado = false;
    }
    vector<size_t> retorno;
    this->caminho_profundidade(retorno, noInicial);
    return retorno;
}

void Graph::caminho_profundidade(vector<size_t> &retorno, size_t noInicial){
    Node* no = search_for_node(noInicial);
    no->_visitado = true;
    retorno.push_back(no->_id);
    for(Edge* aresta = no->_first_edge; aresta != nullptr; aresta=aresta->_next_edge){
        Node* aux = search_for_node(aresta->_target_id);
        if (!aux->_visitado){
            caminho_profundidade(retorno, aux->_id);
        }
    }
}

vector<size_t> Graph::raio_e_diametro(size_t** matriz){ // CONSERTAR! CONCEITO TA ERRADO
    vector<size_t> retorno;
    // vector<size_t> centro;
    // vector<size_t> periferia;
    size_t raio = infinito, diametro = 0;
    
    for(size_t i = 1 ; i <= this->_number_of_nodes; i++){
        for(size_t j = 1; j <= this->_number_of_nodes; j++){
            if(matriz[i][j] == infinito){
                continue;
            }
            if(i != j){
                if (matriz[i][j] > diametro){
                    diametro = matriz[i][j];
                }
                if (matriz[i][j] < raio){
                    raio = matriz[i][j];
                }
            }
        }
    }
    
    retorno.push_back(raio);
    retorno.push_back(diametro);
    return retorno;
    
}

vector<vector<size_t>> Graph::determinar_centro_e_periferia(size_t** matriz, size_t raio, size_t diametro){
    vector<vector<size_t>> retorno;
    vector<size_t> periferia; // == diametro
    vector<size_t> centro; // == raio
    for (size_t i = 1; i <= this->_number_of_nodes; i++){
        for(size_t j = 1; j <= this->_number_of_nodes; j++){
            if(matriz[i][j] == diametro){
                periferia.push_back(i);
            }
            if(matriz[i][j] == raio){
                centro.push_back(i);
            }
        }
    }
    retorno.push_back(centro);
    retorno.push_back(periferia);
    return retorno;
}

void Graph::lista_adjacencia(ofstream& arquivo_saida){ // printa a lista de adj do grafo e salva ele no arquivo de saida (txt) fornecido
    for(Node* no = this->_first; no != nullptr; no = no->_next_node){
        if(no->_next_node != nullptr){
            cout << no->_id << " -> ";
            arquivo_saida << no->_id << " -> ";
        } else {
            cout << no->_id << " -> X\n";
            arquivo_saida << no->_id << " -> X\n";
        }
        for(Edge* aresta = no->_first_edge; aresta != nullptr; aresta = aresta->_next_edge){
            if(aresta->_next_edge == nullptr){
                cout << aresta->_target_id << " -> X ";
                arquivo_saida << aresta->_target_id << " -> X \n";
            } else {
                cout << aresta->_target_id << " -> ";
                arquivo_saida << aresta->_target_id << " -> ";
            }
        }
        cout << endl;
    }
}

void Graph::printa_matriz_adj(){
    for (size_t i = 1; i <= this->_number_of_nodes; i++){
        cout << "\t" << i;
    }
    cout << endl;
    for (size_t i = 1; i <= this->_number_of_nodes; i++){
        cout << "\n" << i;
        for (size_t j = 1; j <= this->_number_of_nodes; j++){
            cout << "\t" << this->matriz_adj[i][j];
        }
    }
}