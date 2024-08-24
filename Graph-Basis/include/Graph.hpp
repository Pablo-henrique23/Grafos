#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "defines.hpp"
#include <vector>
#include <unordered_map>

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
    void add_edge(size_t node_id_1, size_t node_id_2, float weight = 0, bool gemea = false);
    void print_graph(std::ofstream& output_file);
    int conected(size_t node_id_1, size_t node_id_2);
    void print_graph();


    size_t floyd(size_t inicio, size_t destino);
    void calcularFloydTodo();//size_t inicial, size_t destino);
    pair<size_t,string> dijkstra(size_t orig, size_t dest);
    vector<size_t> fecho_tran_direto(size_t node_id);
    vector<Edge*> agmKruskal(vector<Edge*> arestas, size_t n);
    vector<Edge*> agmPrim(vector<Edge*> arestas, size_t nNos);
    vector<size_t> arvore_caminho_profundidade(size_t noInicial);
    void caminho_profundidade(vector<size_t> &retorno, size_t noInicial);
    vector<Edge*> gerarVerticeInduzido(vector<size_t> vertices);
    void determinar_excentricidades();
    void determinar_raio();
    void determinar_diametro();
    void determinar_centro();
    void determinar_periferia();
    void desvisitar_todos();

    Node* search_for_node(size_t node_id);
    bool taNoGrafo(size_t id);
    bool ta_no_vetor(vector<size_t>& vetor, size_t node_id);
    bool node_no_vetor(vector<Node*>& vetor, Node* node);
    bool aresta_no_vetor(vector<Edge*>& vetor, Edge* aresta);
 
    vector<Edge*> allEdges();
    Edge* getAresta(size_t no1, size_t no2);
    unordered_map<size_t, size_t> getExcentricidades();
    Node* getFirst();
    size_t get_raio();
    size_t get_diametro();
    vector<size_t> getCentro();
    vector<size_t> getPeriferia();
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
    unordered_map<size_t, size_t> excentricidades;
    size_t diametro;
    size_t raio;
    vector<size_t> centro;
    vector<size_t> periferia;
    vector<vector<float>> matrizFloyd;
    Graph inverter_arestas();  
    vector<size_t> fecho_tran_indireto(size_t node_id);  
    
};

#endif  //GRAPH_HPP
