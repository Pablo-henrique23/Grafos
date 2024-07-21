#include "../include/Graph.hpp"
#include "../include/Node.hpp"
#include "../include/Edge.hpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
// PERGUNTAR À PROFESSORA SE PODE ALTERAR OS PARÂMETROS DAS FUNÇÕES!!
Graph::Graph(std::ifstream& instance, bool direcionado, bool weighted_edges, bool weighted_nodes)
{
    // Pega a primeira linha e joga pra tamanhoInstância (a 1° linha é o tamanho da instancia do grafo, check README.txt)
    string temp; // temporario pra ser usado na função getline()
    getline(instance, temp);
    
    // pega o tamanho da instancia em inteiro
    this->_number_of_nodes = stoi(temp);
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
    this->_number_of_edges =0;
    this->_number_of_nodes = 0;
    while (getline(instance, linha)){    
        // Deus nos ajude com stringstream
        stringstream ss(linha);
        ss >> no._id;
        ss >> proximoNo._id;
        ss >> aresta._weight;
        add_node(no._id);
        add_node(proximoNo._id);
        add_edge(no._id,proximoNo._id,aresta._weight);
        add_edge(proximoNo._id,no._id,aresta._weight);
            }
    print_graph();
   

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
    while(aux->_next_node!=NULL){     
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
    while(traversal!=NULL){
        if(node_id_1==traversal->_id){
            No1 = traversal;
            break;
        }else{
        traversal=traversal->_next_node;
        }
    }
    if(No1->_first_edge==NULL){
    No1->_first_edge = new Edge();
    No1->_first_edge->_target_id = node_id_2;
    this->_number_of_edges++;
    //    cout<<"Criando primeira aresta do no"<<No1->_id<<endl;
    }else{
        Edge* edgeTraversal=traversal->_first_edge;
    while(edgeTraversal->_next_edge!=NULL){
      //  cout<<"Contem aresta:"<<edgeTraversal->_target_id<<endl;
        edgeTraversal=edgeTraversal->_next_edge;
    }
    edgeTraversal->_next_edge = new Edge();
    edgeTraversal->_next_edge->_target_id = node_id_2;
    this->_number_of_edges++;
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
    while(traversal!=NULL){
        cout<<"Contem no:"<<traversal->_id<<endl;
        edgeTraversal = traversal->_first_edge;
        while(edgeTraversal!=NULL){
            cout<<"     Contem aresta:"<<traversal->_id<<"-"<<edgeTraversal->_target_id<<endl;
           edgeTraversal=edgeTraversal->_next_edge;
        }
        traversal=traversal->_next_node;
    }
    cout<<"Ultimo no:"<<this->_last->_id<<endl;
    cout<<"Numero de Vertices:"<<this->_number_of_nodes<<endl;
    cout<<"Numero de Arestas:"<<this->_number_of_edges<<endl;
}

void Graph::print_graph(std::ofstream& output_file)
{
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    return 0;
}
