#include "../include/Graph.hpp"
#include "../include/Node.hpp"
#include "../include/Edge.hpp"
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
// PERGUNTAR À PROFESSORA SE PODE ALTERAR OS PARÂMETROS DAS FUNÇÕES!!
Graph::Graph(std::ifstream& instance, bool direcionado, bool weighted_edges, bool weighted_nodes)
{
    // Pega a primeira linha e joga pra tamanhoInstância (a 1° linha é o tamanho da instancia do grafo, check README.txt)
    string temp; // temporario pra ser usado na função getline()
    getline(instance, temp);
    
    // pega o tamanho da instancia em inteiro
    this->_number_of_nodes = stoi(temp); // stoi = string to int
    // adiciona outros parametros
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
        if (direcionado == false){ // Se nao for direcionado, entao é uma via de mão dupla e precisa ter as duas arestas
            add_edge(proximoNo._id, no._id, aresta._weight);
        }
    }
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
}

void Graph::remove_edge(size_t node_position_1, size_t node_position_2)
{
}

void Graph::add_node(size_t node_id, float weight)
{
    if(this->_first==nullptr){
        Node* firstNode = new Node();
        _first = firstNode;
        _first->_id = node_id;
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
        this->_number_of_nodes++;
    }
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight)
{
    Node* No1;
    Node* traversal=this->_first;
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


// REFAZER!!
// vector<size_t> Graph::fecho_tran_direto(size_t node_id){
// // Aqui a intenção é fazer um array com todos os nós alcançáveis a partir de `node_id`
    
//     vector<size_t> contatos;
//     vector<size_t> procurados;
//     vector<size_t> ftd;

//     Node* no = this->search_for_node(node_id);
//     if (no == nullptr){
//         return ftd;
//     }

//     Node* aux = no;
//     Edge* aresta = no->_first_edge;
    
    
//     return ftd;

// }


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
    while(no->_next_node!=nullptr){     
        if (no->_id == node_id){
            return no;
        }
        no = no->_next_node;   
    }
    return nullptr;
}

bool Graph::taNoVetor(vector<size_t>& vetor, size_t node_id){
    auto it = find(vetor.begin(), vetor.end(), node_id);
    return (it != vetor.end());
}

void Graph::teste(){
    Node *no = this->_first;
    while (no->_next_node != nullptr){
        Edge *aresta = no->_first_edge;
        for (size_t i = 0; i < no->_number_of_edges; i++){
            cout << aresta->_source_id << " --> " << aresta->_target_id<<endl;
            aresta = aresta->_next_edge;
        }
        no = no->_next_node;
    }
}