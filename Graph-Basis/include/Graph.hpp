#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "defines.hpp"
#include <vector>

using namespace std;
class Graph
{
public:
    /*Assinatura dos métodos básicos para o funcionamento da classe*/

    Graph(ifstream& instance, bool direcionado, bool weighted_edges, bool weighted_nodes);
    Graph();
    ~Graph();

    void remove_node(size_t node_id);
    void remove_edge(size_t node_id_1, size_t node_id_2);
    void add_node(size_t node_id, float weight = 0);
    void add_edge(size_t node_id_1, size_t node_id_2, float weight = 0);
    void print_graph(std::ofstream& output_file);
    int conected(size_t node_id_1, size_t node_id_2);
    void print_graph();


    size_t dijkstra(size_t orig, size_t dest);
    vector<size_t> fecho_tran_direto(size_t node_id);
    vector<Edge*> agmKruskal(vector<Edge*> arestas);
    vector<Edge*> agmPrim(vector<Edge*> arestas, size_t nNos);

    vector<size_t> arvore_caminho_profundidade(size_t noInicial);
    void caminho_profundidade(vector<size_t> &retorno, size_t noInicial);
    vector<Edge*> gerarVerticeInduzido(vector<size_t> vertices);
    Node* gerarArvoreIsolada(Node* no); // fazer ainda (se precisar) -> ajuda pra recursividade
    Node* search_for_node(size_t node_id);
    bool taNoGrafo(size_t id);
    bool ta_no_vetor(vector<size_t>& vetor, size_t node_id);
    bool node_no_vetor(vector<Node*>& vetor, Node* node);
    bool aresta_no_vetor(vector<Edge*>& vetor, Edge* aresta);
 

    bool getDirected();
    size_t getNumberOfNodes();
    bool getWeighted_edges();
    bool getWeighted_nodes();
    

    void lista_adjacencia(ofstream& arquivo_saida);
    void printa_matriz_adj();
    

private:
    size_t _number_of_nodes;
    size_t _number_of_edges; 
    bool   _directed; 
    bool   _weighted_edges;
    bool   _weighted_nodes;
    Node  *_first;
    Node  *_last;
    size_t** matriz_adj;
    vector<vector<pair<int, int>>> adj;
};

#endif  //GRAPH_HPP
