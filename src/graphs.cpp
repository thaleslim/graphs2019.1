#include <bits/stdc++.h>

using namespace std;

#define print printf

bool   fread_until     (ifstream& file, string target, bool stop_before = false);
string fread_after     (ifstream& file, string pre, string delimiter = "\n");
int    print_graph     (map<int,vector<int>> & graph);
bool   create_network  (ifstream& file, map<int,vector<int>>& graph);
bool   fread_edge      (ifstream& file, map<int,vector<int>>& graph);

int main(){
    map<int,vector<int>> graph;
    ifstream file;
    file.open("resources/karate.gml");

    if(file.is_open()){
        create_network(file,graph);
        file.close();
        print_graph(graph);
    }else
        print("ERROR: file could not be openned");

    return 0;
}

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

bool create_network(ifstream& file, map<int,vector<int>>& graph){
    if(!file.is_open() || !fread_until(file,"graph"))
        return false;
    
    string line;
    while ( getline (file,line) ){
        if (line[0] == ']')
            break;
        if (line.find("node") != string::npos){
            /* fread_until(file,"id ");
            getline (file,line);
            graph[stoi(line)]; // gets id as string and converts to int*/
            graph[stoi(fread_after(file,"id "))]; // gets id as string and converts to int
        }
        else if (line.find("edge") != string::npos)
            fread_edge(file,graph);
    }
    return true;
}
// End create_network()

bool fread_edge      (ifstream& file, map<int,vector<int>>& graph){
    if(!file.is_open() || !fread_until(file,"source "))
        return false;

    string new_line;
    getline(file,new_line);
    int source = stoi(new_line);

    if(!fread_until(file,"target "))
        return false;

    getline(file,new_line);
    int target = stoi(new_line);

    map<int,vector<int>>::iterator it = graph.find(source);
    
    if (it != graph.end())
        graph[target].push_back(source);
    else
        return false;

    it = graph.find(target);
    if (it != graph.end())
        graph[source].push_back(target);
    else
        return false;

    return true;}
// End fread_edge()

string fread_after     (ifstream& file, string pre, string delimiter){
    if(!file.is_open() || !fread_until(file,pre))
        return nullptr;
    string result, candidate;
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
