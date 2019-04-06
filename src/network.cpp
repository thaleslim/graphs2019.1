/**
 * @author Thales Menezes @thaleslim
 * @date   06/04/2019
 */

#include "../headers/network.hpp"
#include <bits/stdc++.h>

using namespace std;

#define print printf

//-------------------------------------------------------------------
bool fread_until(ifstream& file, string target, bool stop_before){
    if(!file.is_open())
        return false;

    string::iterator focus = target.begin();
    size_t current_position = file.tellg();
    bool found = false;
    char c;
    
    while ( !found && file.get(c) ){
        if( c == *focus ) ++focus;
        if( focus == target.end() ) found = true;
    }
    
    if (found && stop_before)
        file.seekg(-target.length(),ios_base::cur);
    else if (file.peek() == EOF)
        file.seekg(current_position,ios_base::beg);
    
    return found;}
// End fread_until()

//-------------------------------------------------------------------
int print_graph(map<int,vector<int>> & graph){
    // print graph ( map<int,vector<int>> )
    size_t node_quantity = 0;
    for(auto& item: graph){
        print("%d\n", item.first);
        for (vector<int>::iterator it = item.second.begin(); it != item.second.end(); ++it)
            print(" %d", *it);
        print("\n");
        node_quantity++;
    }
    return node_quantity;}
// End print_graph()

//-------------------------------------------------------------------
bool create_network(ifstream& file, map<int,vector<int>>& graph){
    if(!file.is_open() || !fread_until(file,"graph"))
        return false;
    
    string line;
    while ( getline (file,line) ){
        if (line[0] == ']')
            break;
        if (line.find("node") != string::npos){
            graph[stoi(fread_after(file,"id "))]; // gets id as string and converts to int
        }
        else if (line.find("edge") != string::npos)
            fread_edge(file,graph);
    }
    return true;}
// End create_network()

//-------------------------------------------------------------------
bool fread_edge      (ifstream& file, map<int,vector<int>>& graph){
    if(!file.is_open())
        return false;

    string check = fread_after(file,"source ");
    
    int source = -1, target = -1;
    if(!check.empty())
        source = stoi(check);

    check = fread_after(file,"target ");
    if(!check.empty())
        target = stoi(check);

    if( source < 0 || target < 0)
        return false;
    
    map<int,vector<int>>::iterator it = graph.find(source);
    
    if (it != graph.end())
        graph[target].push_back(source);
    it = graph.find(target);
    if (it != graph.end())
        graph[source].push_back(target);

    return true;}
// End fread_edge()

//-------------------------------------------------------------------
string fread_after     (ifstream& file, string pre, string delimiter){
    string result;
    if(!file.is_open() || !fread_until(file,pre))
        return result;
    string candidate;
    string::iterator focus = delimiter.begin();
    char c;
    bool candidate_is_on = false;
    while ( file.get(c) ){
        if( c == *focus ){
            if( !candidate_is_on )
                candidate_is_on = true;
            candidate += c;
            ++focus;
        }
        else if(focus != delimiter.end()) {
            if(candidate_is_on){
                focus = delimiter.begin();
                candidate_is_on = false;
                result += candidate;
            }
            result += c;
        }
        else break;
    }
    return result;}
// End fread_after()
