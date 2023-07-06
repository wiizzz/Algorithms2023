#include "dsu.h"

DisjointSet::DisjointSet(int V){
    for(int i = 0; i < V; i++){
        parent.push_back(i);
        rank.push_back(0);
    }
}

int DisjointSet::FindSet(int x) {
   if(x == parent[x])
        return x;
    return parent[x] = FindSet(parent[x]);
}

void DisjointSet::Union(int x, int y){
    int xp = FindSet(x);
    int yp = FindSet(y);
    if(xp == yp)
        return;
    if(rank[xp] > rank[yp])
        parent[yp] = xp;
    else{
        parent[xp] = yp;
        if(rank[xp] == rank[yp])
            rank[yp] = rank[yp] + 1;
    }
}