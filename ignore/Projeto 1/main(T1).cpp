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
        
        double clustering_coeficient (int vertex);
    
    private:
        void cliques_maximais ( set<int> clique, set<int> candidatos, set<int> falhas );

};

bool compare_set(set<int> source, set<int> target){
    if( source.size() != target.size() )
        return false;
    size_t result = 0;
    for(int item: source)
        result += target.count(item);
    return result == source.size();
}

set<int> make_set(vector<int> vetor){
    set<int> result;
    for(int i = 0; i < vetor.size() ;i++)
        result.insert(vetor[i]);
    return result;
}

double Graph::clustering_coeficient (int vertex){
    if( grafo.find(vertex) == grafo.end() )
        return -1;

    vector<int> links = grafo[vertex];
    double num_triangles = (links.size()*(links.size()-1)/2);

    if (num_triangles == 0)
        return 0;

    set<vector<int>> universe;

    for(int i = 0; i < links.size(); i++){
        for(int j = 0; j < links.size(); j++){
            for(int k = 0; k < links.size(); k++){
                if(!(i==j && j==k)){
                    int primeiro = links[i], segundo  = links[j], terceiro = links[k];
                    set<int> first = make_set(grafo[primeiro]), second = make_set(grafo[segundo]), third = make_set(grafo[terceiro]);

                    if( ( first.count(segundo) > 0 && first.count(terceiro) > 0 ) &&
                        ( second.count(primeiro) > 0 && second.count(terceiro) > 0 ) &&
                        ( third.count(primeiro) > 0 && first.count(segundo) > 0 ) ){
                            int myints[] = {primeiro,segundo,terceiro};
                            std::vector<int> triple (myints, myints + sizeof(myints) / sizeof(int) );
                            universe.insert(triple);
                    }
                }
            }
        }
    }
    return universe.size() / num_triangles;
}

void print_maximal(set<int> conjunto){
    print("Maximal{%d, ", int(conjunto.size()) );
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
    // int myints[] = {10,20,30,40,50,60};
    // set<int> first(myints,myints+3), second(first), third(myints+3,myints+6);
    // cout << compare_set(first, second) << " " << compare_set(first,third) << endl; return 0;

    Graph graph;
    ifstream file;
    file.open("resources/karate.gml");

    if(file.is_open()){
        create_network(file,graph.grafo);
        file.close();
        // print_graph(graph);
        // Questão 1)
        print("==============================================================================================\n");
        for(auto& key : graph.grafo)
            { print("vertice: %d\tgrau: %d\n", key.first , grau_vertice(key.first,key.second)); } 
        // Questão 2)
        print("==============================================================================================\n");
        graph.cliques_maximais();
        // Questão 3)
        print("==============================================================================================\n");
        double sum = 0; size_t node_amount = 1;
        for(auto& key: graph.grafo){ 
            double result = graph.clustering_coeficient(key.first); 
            print("vertice: %d \tclustering coeficient: %f\n", key.first, result);
            sum += result; node_amount++;
        }
        // Questão 4)
        print("==============================================================================================\n");
        double coef = sum/node_amount;
        print("Coeficiente medio %f\n", coef);

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