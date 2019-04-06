/**
 * @author Thales Menezes @thaleslim
 * @date   06/04/2019
 */

#include "../headers/network.hpp"
#include <bits/stdc++.h>

using namespace std;

#define print printf

//--------------------------------------------------------------------------------
bool    file_find       (ifstream& file, string target, bool stop_before){
    /**
     * Searches for a string in a file.
     * @arg stop_before Tries to move back the cursor before the target
     * @return Search verdict
     * @note Cursor position in input sequence will be modified.
     */
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
// End file_find()

//--------------------------------------------------------------------------------
int     print_graph     (map<int,vector<int>> & graph){
    /**
     * Prints a map<int,vector<int>>
     * @return number of nodes (map keys)
     */
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

//--------------------------------------------------------------------------------
bool    create_network  (ifstream& file, map<int,vector<int>>& graph){
    /**
     * Graph abstraction using a file.gml and map<int,vector<int>>
     * @return true if procedure completed sucessfully.
     */
    if(!file.is_open() || !file_find(file,"graph"))
        return false;
    
    string line;
    while ( getline (file,line) ){
        if (line[0] == ']')
            break;
        if (line.find("node") != string::npos){
            graph[stoi(file_read(file,"id "))]; // gets id as string and converts to int
        }
        else if (line.find("edge") != string::npos)
            fget_edge(file,graph);
    }
    return true;}
// End create_network()

//--------------------------------------------------------------------------------
bool    fget_edge       (ifstream& file, map<int,vector<int>>& graph){
    /**
     * Creates a edge from file
     * @return true if edge was read sucessfully.
     */
    if(!file.is_open())
        return false;

    string check = file_read(file,"source ");
    
    int source = -1, target = -1;
    if(!check.empty())
        source = stoi(check);

    check = file_read(file,"target ");
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
// End fget_edge()

//--------------------------------------------------------------------------------
string  file_read       (ifstream& file, string begin, string end){
    /**
     * Read data block from ]begin,end[
     * @return empty string if search fails.
     */
    string result;
    if(!file.is_open() || !file_find(file,begin))
        return result;
    string candidate;
    string::iterator focus = end.begin();
    char c;
    bool candidate_is_on = false;
    while ( file.get(c) ){
        if( c == *focus ){
            if( !candidate_is_on )
                candidate_is_on = true;
            candidate += c;
            ++focus;
        }
        else if(focus != end.end()) {
            if(candidate_is_on){
                focus = end.begin();
                candidate_is_on = false;
                result += candidate;
            }
            result += c;
        }
        else break;
    }
    return result;}
// End file_find()
