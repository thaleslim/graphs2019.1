/**
 * @author Thales Menezes @thaleslim
 * @date   06/04/2019
 */

#include <bits/stdc++.h>
#include "../headers/network.hpp"

using namespace std;

#define print printf

int             grau_vertice        (int vertice, vector<int> elos);
vector<int>     map_keys            (map<int,vector<int>>& mapa);

class Graph{
    public:
        map<int,vector<int>> grafo;

        void cliques_maximais(){
            set<int> clique, candidatos, falhas;
            for(auto & key : map_keys(grafo))
                candidatos.insert(key);
            cliques_maximais(clique,candidatos,falhas);
            return;}
    
    private:
        void cliques_maximais ( set<int> clique, set<int> candidatos, set<int> falhas );

};

void print_maximal(set<int> conjunto){
    print("Maximal{");
    for(int elem : conjunto)
	    print(" [%d] ", elem);
    print("}\n");
}

/* 
    R = clique
    P = candidatos
    X = falhos
*/
void  Graph::cliques_maximais ( set<int> clique, set<int> candidatos, set<int> falhos ){

    if( falhos.empty() && candidatos.empty() )
        print_maximal(clique);
    else if (candidatos.empty()) return;

    set<int> new_clique, new_candidatos, new_falhos;
    set<int>::iterator it_candidatos;
    
    for(it_candidatos = candidatos.begin();it_candidatos != candidatos.end(); it_candidatos = candidatos.begin()){
        new_clique = clique;
        new_clique.insert(*it_candidatos);       // R união {v}

        for(auto & item : grafo[*it_candidatos])
            if(candidatos.count(item) > 0)
                new_candidatos.insert(item);     // P interseção Vizinhos(v)

        for(auto & item : grafo[*it_candidatos])
            if(falhos.count(item) > 0 )
                new_falhos.insert(item);         // X interseção Vizinhos(v)

        cliques_maximais(new_clique,new_candidatos,new_falhos);
        
        new_clique.clear();
        new_candidatos.clear();
        new_falhos.clear();

        candidatos.erase((*it_candidatos));
        falhos.insert((*it_candidatos));
    }
}

int main(){
    Graph graph;
    ifstream file;
    file.open("resources/karate.gml");

    if(file.is_open()){
        create_network(file,graph.grafo);
        file.close();
        // print_graph(graph);
        /* // Questão 1) Solved 
        for(auto& key : graph)
            { print("vertice: %d grau: %d\n", key.first , grau_vertice(key.first,key.second)); } */
        // Questão 2)
    
        graph.cliques_maximais();


    }else
        print("ERROR: file could not be openned");

    return 0;
}

int    grau_vertice    (int vertice, vector<int> elos){
    /**
     * @note if vertice == link : laço -> +2
     */
    size_t length = elos.size();
    for(auto & link : elos)
        if( vertice == link )
            length++;
    return length;
}

vector<int>    map_keys    (map<int,vector<int>>& mapa){
    vector<int> keys;
    for(auto & key : mapa)
        keys.push_back(key.first);
    return keys;}