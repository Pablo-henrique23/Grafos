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
    string linha;
    
    Node no;
    Node proximoNo;
    Edge aresta;
    int cont = 0; // contador pra determinar o primeiro
    while (getline(instance, linha)){    
        // Deus nos ajude com stringstream
        stringstream ss(linha);
        ss >> no._id;
        ss >> proximoNo._id;
        
        //cout << no._id << "->" << proximoNo._id << endl;
        
        no._next_node = &proximoNo;
        ss >> aresta._weight;
        // Se cont == 0, foi o 1° Nó analisado (a instancia ja foi analisado, o cursor nao está na 1° linha. Lembre de ED2)
        if (cont == 0){
            this->_first = &no;
        }
    }
    

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
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight)
{
}

void Graph::print_graph()
{
}

void Graph::print_graph(std::ofstream& output_file)
{
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    return 0;
}
