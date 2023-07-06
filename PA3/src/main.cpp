#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include "dsu.h"
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    Edge() : from(0), to(0), weight(0) {}
    Edge(int f, int t, int w) : from(f), to(t), weight(w){}
};

bool DFS_Visit(vector<vector<int> >& graph, vector<char>& colors, int u) {
    colors[u] = 'g';
    for (int v = 0; v < graph[u].size(); v++) {
        if (colors[graph[u][v]] == 'g')
            return true;
        if (colors[graph[u][v]] == 'w' && DFS_Visit(graph, colors, graph[u][v]))
            return true;
    }
    colors[u] = 'b';
    return false;
}

bool DFS(vector<vector<int> >& graph) {
    vector<char> colors(graph.size(), 'w');
    for (int i = 0; i < graph.size(); i++) {
        if (colors[i] == 'w') {
            if (DFS_Visit(graph, colors, i))
                return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]){
    char mode;
    int V, E;
    vector<Edge> Edges;
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    infile >> mode >> V >> E;

    vector<vector<int> > Graph;
    Graph.resize(V);

    while(true){
        int start, end, weight;
        infile >> start >> end >> weight;
        if(infile.eof())
            break;
        Edges.push_back(Edge(start, end, weight));
    }

    DisjointSet ds(V);
    queue<Edge> remove;
    int totalWeight = 0;
    
    std::sort(Edges.begin(), Edges.end(), [](const Edge &a, const Edge &b) -> bool{ return a.weight > b.weight; });
    for(int i = 0; i < Edges.size(); i++){
        if(ds.FindSet(Edges[i].from) != ds.FindSet(Edges[i].to)){
            ds.Union(Edges[i].from,Edges[i].to);
            int g = Edges[i].from;
            Graph[Edges[i].from].push_back(Edges[i].to);
        }
        else{
            remove.push(Edges[i]);
            totalWeight += Edges[i].weight;
        }
    }
  
    if(mode == 'u'){
        outfile << totalWeight << endl;
        while(!remove.empty()){
            Edge e = remove.front();
            outfile << e.from << " " <<  e.to << " " << e.weight << endl;  
            remove.pop();
        }
    }
    else if(mode == 'd'){
        vector<Edge> output;
        while(!remove.empty()){
            Edge e = remove.front();
            remove.pop();
            if(e.weight < 0){
                output.push_back(e);
                continue;
            }
            Graph[e.from].push_back(e.to);
            
            if(DFS(Graph)){
                output.push_back(e);
                Graph[e.from].pop_back();
            }
            else
                totalWeight -= e.weight;
        }

        outfile << totalWeight << endl;
        for(const auto &i: output)
            outfile << i.from << " " <<  i.to << " " << i.weight << endl;  
    }

    infile.close();
    outfile.close();
    return 0;
}